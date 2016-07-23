/*
**���������
*/
#ifndef __TASK_PARSER_H__
#define __TASK_PARSER_H__
#include <boost/smart_ptr.hpp>
#include "CommTask.h"

class CTaskParser
{
public:
  typedef boost::shared_ptr<CCommTask> SPtrCTask;
  typedef CCommTask::TaskType TaskType;
  typedef websocketpp::connection_hdl CHDL;

  CTaskParser();
  ~CTaskParser();

  //��������
  //����������������������ָ��
  void ResolveTask(SPtrCTask pTask);
private:
  //�ͻ�����������
  //�����������������ָ��
  void ClientLinked(SPtrCTask pTask);

  //�ͻ��˶Ͽ�����
  //�����������������ָ��

};

#endif