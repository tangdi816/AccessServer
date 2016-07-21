#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <string>
#include "TaskParser.h"
#include "Utility.h"
#include "EncodeAndDecode.h"

using namespace std;
using namespace boost::uuids;
using namespace boost::property_tree;

CTaskParser::CTaskParser()
{
  //从配置文件中读取加密key
  GetKey();
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


  //加密客户端UUID
  string strCoded=CEncodeAndDecode::CodingByString(strUUID, m_strKey);

  //发送加密UUID到客户端

}

//获取加密key串
void CTaskParser::GetKey()
{
  //获取配置文件路径
  string strPath=CUtility::GetConfigFilePath();

  //从配置文件中读取Key串
  ptree oPt;
  read_json(strPath, oPt);
  m_strKey=oPt.get<string>("conf.code_key");
}
