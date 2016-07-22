/*
**�ͻ���������
**����ͻ������Ӽ����������շ�
**����WebSocketpp��ʵ������
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

  //��ͻ��˷���UUID
  //����1���ͻ������Ӿ��
  //����2��UUID��
  void SendUUID(CHDL pHdl, const std::string& strUUID);
private:
  //websocket server����
  WSServer m_oWServer;

  //ԭʼ����key�����������ܿͻ���UUID���ݰ�
  std::string m_strKey;

  //�ͻ������ӻص�����
  void OnOpen(WSServer* pServer, CHDL pHdl);

  //�ͻ��˶Ͽ��ص�����
  void OnClose(WSServer* pServer, CHDL pHdl);

  //�յ��ͻ�������
  void OnMessage(WSServer* pServer, CHDL pHdl, MsgPtr pMsg);

  //��ʼ���пͻ������ӷ���
  void StartServerRun();

  //��ͻ��˷�����Ϣ
  //����1���ͻ������Ӿ��
  //����2����Ϣ
  //����3����Ϣ�������ͣ�Ĭ���ַ�������
  void SendMsgToClient(CHDL pHdl, const std::string& strMsg, CodeType eCodeType=websocketpp::frame::opcode::text);
};
#endif
