/*
**客户端连接信息表管理类
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

  //插入客户端信息
  //参数1：客户端连接句柄
  //参数2：客户端UUID
  void InsertCInfo(CHDL pHdl, const std::string& strUUID);
public:
  //客户端信息表
  CInfoMap m_mapCIM;

  //信息表锁
  boost::mutex m_lkMap; 

};

