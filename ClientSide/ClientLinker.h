/*
**客户端连接类
**负责客户端连接监听，数据收发
**调用WebSocketpp库实现连接
*/
#ifndef __CLIENT_LINKER_H__
#define __CLIENT_LINKER_H__

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <boost/smart_ptr.hpp>
#include "CommTask.h"

class CClientLinker
{
public:
  typedef websocketpp::server<websocketpp::config::asio> WSServer;
  typedef WSServer::message_ptr MsgPtr;
  typedef websocketpp::connection_hdl CHDL;
  typedef websocketpp::log::alevel ALogLvl;
  typedef boost::shared_ptr<CCommTask> SPtrCTask;
  typedef CCommTask::TaskType TaskType;
  typedef websocketpp::frame::opcode::value CodeType;

  CClientLinker();
  ~CClientLinker();

  //向客户端发送UUID
  //参数1：客户端连接句柄
  //参数2：UUID串
  void SendUUID(CHDL pHdl, const std::string& strUUID);
private:
  //websocket server对象
  WSServer m_oWServer;

  //原始加密key串，用来加密客户端UUID数据包
  std::string m_strKey;

  //客户端连接回调函数
  void OnOpen(WSServer* pServer, CHDL pHdl);

  //客户端断开回调函数
  void OnClose(WSServer* pServer, CHDL pHdl);

  //收到客户端数据
  void OnMessage(WSServer* pServer, CHDL pHdl, MsgPtr pMsg);

  //开始运行客户侧连接服务
  void StartServerRun();

  //向客户端发送消息
  //参数1：客户端连接句柄
  //参数2：消息
  //参数3：消息编码类型，默认字符串编码
  void SendMsgToClient(CHDL pHdl, const std::string& strMsg, CodeType eCodeType=websocketpp::frame::opcode::text);
};
#endif
