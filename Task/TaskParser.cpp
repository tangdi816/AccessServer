#include "TaskParser.h"



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
  	
  }else if(TaskType::CLIENTCLOSE==eTType){
  	
  }else if(TaskType::CLIENTMSG==eTType){

  }else if(TaskType::SERVERMSG==eTType){

  }
}
