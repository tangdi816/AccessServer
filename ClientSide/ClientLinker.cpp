#include "ClientLinker.h"
#include "TQManager.h"
#include "Utility.h"
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include "rapidjson.h"
#include "document.h"
#include "stringbuffer.h"
#include "EncodeAndDecode.h"
#include "writer.h"

using namespace boost;
using namespace std;
using namespace RAPIDJSON_NAMESPACE;


//通信任务队列管理
extern CTQManager g_oTaskQueue;

CClientLinker::CClientLinker()
{
  //创建客户侧监听线程
  boost::thread oCListener(bind(&CClientLinker::StartServerRun, this));
  //剥离线程
  oCListener.detach();

  //从配置文件获取key串
  m_strKey=CUtility::GetConfigValue<string>("conf.code_key");
}


CClientLinker::~CClientLinker()
{
}

//客户端连接回调函数
void CClientLinker::OnOpen(WSServer* pServer, CHDL pHdl)
{
  //拼装客户端连接任务
  SPtrCTask spTask(new CCommTask(TaskType::CLIENTLINK, pHdl));
  //将任务放入任务队列
  g_oTaskQueue.WriteTaskQueue(spTask);
}

//客户端断开回调函数
void CClientLinker::OnClose(WSServer* pServer, CHDL pHdl)
{
  //拼装客户端断开任务
  SPtrCTask spTask(new CCommTask(TaskType::CLIENTCLOSE, pHdl));
  //将任务放入任务队列
  g_oTaskQueue.WriteTaskQueue(spTask);
}

//收到客户端数据
void CClientLinker::OnMessage(WSServer* pServer, CHDL pHdl, MsgPtr pMsg)
{
  string strMsg=pMsg->get_payload();
  //拼装客户端断开任务
  SPtrCTask spTask(new CCommTask(TaskType::CLIENTCLOSE, pHdl, strMsg));
  //将任务放入任务队列
  g_oTaskQueue.WriteTaskQueue(spTask);
}

//开始运行客户侧连接服务
void CClientLinker::StartServerRun()
{
  //设置日志输出
  m_oWServer.set_access_channels(ALogLvl::all);
  m_oWServer.clear_access_channels(ALogLvl::frame_payload);

  //初始化ASIO库
  m_oWServer.init_asio();

  // - - - - - - 绑定回调函数 - - - - - -
  //绑定连接建立回调
  m_oWServer.set_open_handler(bind(&CClientLinker::OnOpen, this, &m_oWServer, _1));

  //绑定连接关闭回调
  m_oWServer.set_close_handler(bind(&CClientLinker::OnClose, this, &m_oWServer, _1));

  //绑定接收消息回调
  m_oWServer.set_message_handler(bind(&CClientLinker::OnMessage, this, &m_oWServer, _1, _2));

  //提取客户侧监听端口
  uint16_t iPort=CUtility::GetConfigValue<int>("conf.client_port");
  //监听端口
  m_oWServer.listen(iPort);

  //开启accept循环
  m_oWServer.start_accept();

  //启动ASIO::io_service::run循环
  m_oWServer.run();
  return;
}

//向客户端发送消息
//参数1：客户端连接句柄
//参数2：消息
//参数3：消息编码类型，默认字符串编码
void CClientLinker::SendMsgToClient(CHDL pHdl, const std::string& strMsg, CodeType eCodeType)
{
  m_oWServer.send(pHdl, strMsg, eCodeType);
  return;
}

//向客户端发送UUID
//参数1：客户端连接句柄
//参数2：UUID串
void CClientLinker::SendUUID(CHDL pHdl, const std::string& strUUID)
{
  // - - - - 拼装命令 - - - - -
  Document oDoc;
  oDoc.SetObject();

  Value oUUID;
  oUUID.SetString(strUUID.c_str(), strUUID.length(), oDoc.GetAllocator());
  oDoc.AddMember("command", Value(230001), oDoc.GetAllocator());
  oDoc.AddMember("uid", oUUID, oDoc.GetAllocator());

//   oDoc.AddMember("command", Value(230000), oDoc.GetAllocator());
//   Value oArray(kArrayType);
//   Value oAdd1;
//   oAdd1="ws://192.168.1.222:30012";
//   Value oAdd2;
//   oAdd2="ws://127.0.0.1:30012";
//   oArray.PushBack(oAdd1, oDoc.GetAllocator());
//   oArray.PushBack(oAdd2, oDoc.GetAllocator());
//   oDoc.AddMember("addres", oArray, oDoc.GetAllocator());

  StringBuffer buffer;
  buffer.Clear();
  Writer<StringBuffer> oWriter(buffer);
  oDoc.Accept(oWriter);

  string strMsg=buffer.GetString();

  //使用源key串加密命令
  string strCoded=CEncodeAndDecode::CodingByString(strMsg, m_strKey);

  //发送命令
  SendMsgToClient(pHdl, strCoded);
}