#include "CInfoManager.h"

using namespace std;
using namespace boost;

CCInfoManager::CCInfoManager()
{
}


CCInfoManager::~CCInfoManager()
{
}

//插入客户端信息
//参数1：客户端连接句柄
//参数2：客户端UUID
void CCInfoManager::InsertCInfo(CHDL pHdl, const string& strUUID)
{
  {
    //锁住表
    lock_guard<mutex> lkg(m_lkMap);
    if(!m_mapCIM.insert(make_pair(pHdl, strUUID)).second){
      //插入失败
      auto itFider=m_mapCIM.find(pHdl);
      //找到之前存入客户端信息
      if(itFider!=m_mapCIM.end()){
        //更改客户端UUID
      	(*itFider).second=strUUID;
      }
    }
  }//解锁表
}
