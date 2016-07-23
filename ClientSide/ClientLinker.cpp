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


//ͨ��������й���
extern CTQManager g_oTaskQueue;

CClientLinker::CClientLinker()
{
  //�����ͻ�������߳�
  boost::thread oCListener(bind(&CClientLinker::StartServerRun, this));
  //�����߳�
  oCListener.detach();

  //�������ļ���ȡkey��
  m_strKey=CUtility::GetConfigValue<string>("conf.code_key");
}


CClientLinker::~CClientLinker()
{
}

//�ͻ������ӻص�����
void CClientLinker::OnOpen(WSServer* pServer, CHDL pHdl)
{
  //ƴװ�ͻ�����������
  SPtrCTask spTask(new CCommTask(TaskType::CLIENTLINK, pHdl));
  //����������������
  g_oTaskQueue.WriteTaskQueue(spTask);
}

//�ͻ��˶Ͽ��ص�����
void CClientLinker::OnClose(WSServer* pServer, CHDL pHdl)
{
  //ƴװ�ͻ��˶Ͽ�����
  SPtrCTask spTask(new CCommTask(TaskType::CLIENTCLOSE, pHdl));
  //����������������
  g_oTaskQueue.WriteTaskQueue(spTask);
}

//�յ��ͻ�������
void CClientLinker::OnMessage(WSServer* pServer, CHDL pHdl, MsgPtr pMsg)
{
  string strMsg=pMsg->get_payload();
  //ƴװ�ͻ��˶Ͽ�����
  SPtrCTask spTask(new CCommTask(TaskType::CLIENTCLOSE, pHdl, strMsg));
  //����������������
  g_oTaskQueue.WriteTaskQueue(spTask);
}

//��ʼ���пͻ������ӷ���
void CClientLinker::StartServerRun()
{
  //������־���
  m_oWServer.set_access_channels(ALogLvl::all);
  m_oWServer.clear_access_channels(ALogLvl::frame_payload);

  //��ʼ��ASIO��
  m_oWServer.init_asio();

  // - - - - - - �󶨻ص����� - - - - - -
  //�����ӽ����ص�
  m_oWServer.set_open_handler(bind(&CClientLinker::OnOpen, this, &m_oWServer, _1));

  //�����ӹرջص�
  m_oWServer.set_close_handler(bind(&CClientLinker::OnClose, this, &m_oWServer, _1));

  //�󶨽�����Ϣ�ص�
  m_oWServer.set_message_handler(bind(&CClientLinker::OnMessage, this, &m_oWServer, _1, _2));

  //��ȡ�ͻ�������˿�
  uint16_t iPort=CUtility::GetConfigValue<int>("conf.client_port");
  //�����˿�
  m_oWServer.listen(iPort);

  //����acceptѭ��
  m_oWServer.start_accept();

  //����ASIO::io_service::runѭ��
  m_oWServer.run();
  return;
}

//��ͻ��˷�����Ϣ
//����1���ͻ������Ӿ��
//����2����Ϣ
//����3����Ϣ�������ͣ�Ĭ���ַ�������
void CClientLinker::SendMsgToClient(CHDL pHdl, const std::string& strMsg, CodeType eCodeType)
{
  m_oWServer.send(pHdl, strMsg, eCodeType);
  return;
}

//��ͻ��˷���UUID
//����1���ͻ������Ӿ��
//����2��UUID��
void CClientLinker::SendUUID(CHDL pHdl, const std::string& strUUID)
{
  // - - - - ƴװ���� - - - - -
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

  //ʹ��Դkey����������
  string strCoded=CEncodeAndDecode::CodingByString(strMsg, m_strKey);

  //��������
  SendMsgToClient(pHdl, strCoded);
}