#include "TaskParser.h"



CTaskParser::CTaskParser()
{
}


CTaskParser::~CTaskParser()
{
}

//��������
//����������������������ָ��
void CTaskParser::ResolveTask(SPtrCTask pTask)
{
  //��ȡ��������
  TaskType eTType=pTask->GetType();
  if(TaskType::CLIENTLINK==eTType){
  	
  }else if(TaskType::CLIENTCLOSE==eTType){
  	
  }else if(TaskType::CLIENTMSG==eTType){

  }else if(TaskType::SERVERMSG==eTType){

  }
}
