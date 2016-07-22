/*
**客户端连接信息表管理类
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
#endif