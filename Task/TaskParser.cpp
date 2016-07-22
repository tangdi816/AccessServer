#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <string>
#include "TaskParser.h"
#include "Utility.h"
#include "EncodeAndDecode.h"
#include "CInfoManager.h"
#include "ClientLinker.h"

using namespace std;
using namespace boost::uuids;

extern CCInfoManager g_oClientManager;
extern CClientLinker g_oCLinker;

CTaskParser::CTaskParser()
{
}


CTaskParser::~CTaskParser()
{
}

//解析任务
//参数：传入待解析任务对象指针
void CTaskParser::ResolveTask(SPtrCTask pTask)
{
  //提取任务类型
  TaskType eTType=pTask->GetType();
  if(TaskType::CLIENTLINK==eTType){
    //客户端连接任务
  	ClientLinked(pTask);
  }else if(TaskType::CLIENTCLOSE==eTType){
  	
  }else if(TaskType::CLIENTMSG==eTType){

  }else if(TaskType::SERVERMSG==eTType){

  }
}

//客户端连接任务
//参数：传入任务对象指针
void CTaskParser::ClientLinked(SPtrCTask pTask)
{
  //提取客户端连接句柄
  CHDL hdlClient=pTask->GetHDL();
  //生成客户端UUID
  random_generator oRGen;
  uuid oUId=oRGen();
  string strUUID=to_string(oUId);

  //将客户端连接信息存入队列
  g_oClientManager.InsertCInfo(hdlClient, strUUID);

  //发送UUID到客户端
  g_oCLinker.SendUUID(hdlClient, strUUID);
}