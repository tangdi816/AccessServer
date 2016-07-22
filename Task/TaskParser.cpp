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

//��������
//����������������������ָ��
void CTaskParser::ResolveTask(SPtrCTask pTask)
{
  //��ȡ��������
  TaskType eTType=pTask->GetType();
  if(TaskType::CLIENTLINK==eTType){
    //�ͻ�����������
  	ClientLinked(pTask);
  }else if(TaskType::CLIENTCLOSE==eTType){
  	
  }else if(TaskType::CLIENTMSG==eTType){

  }else if(TaskType::SERVERMSG==eTType){

  }
}

//�ͻ�����������
//�����������������ָ��
void CTaskParser::ClientLinked(SPtrCTask pTask)
{
  //��ȡ�ͻ������Ӿ��
  CHDL hdlClient=pTask->GetHDL();
  //���ɿͻ���UUID
  random_generator oRGen;
  uuid oUId=oRGen();
  string strUUID=to_string(oUId);

  //���ͻ���������Ϣ�������
  g_oClientManager.InsertCInfo(hdlClient, strUUID);

  //����UUID���ͻ���
  g_oCLinker.SendUUID(hdlClient, strUUID);
}