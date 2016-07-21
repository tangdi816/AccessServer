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

  CTaskParser();
  ~CTaskParser();

  //��������
  //����������������������ָ��
  void ResolveTask(SPtrCTask pTask);
};

#endif