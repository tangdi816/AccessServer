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
  //�������ļ��ж�ȡ����key
  GetKey();
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


  //���ܿͻ���UUID
  string strCoded=CEncodeAndDecode::CodingByString(strUUID, m_strKey);

  //���ͼ���UUID���ͻ���

}

//��ȡ����key��
void CTaskParser::GetKey()
{
  //��ȡ�����ļ�·��
  string strPath=CUtility::GetConfigFilePath();

  //�������ļ��ж�ȡKey��
  ptree oPt;
  read_json(strPath, oPt);
  m_strKey=oPt.get<string>("conf.code_key");
}
