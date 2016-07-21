/*
**�ͻ���������Ϣ�������
*/
#include <boost/unordered_map.hpp>
#include <websocketpp/server.hpp>
#include <boost/thread.hpp>
#include <boost/thread/lock_factories.hpp>

class CCInfoManager
{
public:
  typedef websocketpp::connection_hdl CHDL;
  typedef boost::unordered_map<CHDL, std::string> CInfoMap;

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

