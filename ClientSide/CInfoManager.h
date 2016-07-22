/*
**�ͻ���������Ϣ�������
*/
#ifndef __CLIENT_INRO_MANAGER_H__
#define __CLIENT_INRO_MANAGER_H__

#include <map>
#include <websocketpp/server.hpp>
#include <boost/thread.hpp>
#include <boost/thread/lock_factories.hpp>
#include <boost/smart_ptr.hpp>

class CCInfoManager
{
public:
  typedef websocketpp::connection_hdl CHDL;
  typedef std::map<CHDL, std::string> CInfoMap;

  CCInfoManager();
  ~CCInfoManager();

  //����ͻ�����Ϣ
  //����1���ͻ������Ӿ��
  //����2���ͻ���UUID
  void InsertCInfo(CHDL pHdl, const std::string& strUUID);
public:
  //�ͻ�����Ϣ��
  CInfoMap m_mapCIM;

  //��Ϣ����
  boost::mutex m_lkMap; 

};
#endif