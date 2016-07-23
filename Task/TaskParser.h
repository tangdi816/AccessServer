/*
**任务解析器
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

  //解析任务
  //参数：传入待解析任务对象指针
  void ResolveTask(SPtrCTask pTask);
private:
  //客户端连接任务
  //参数：传入任务对象指针
  void ClientLinked(SPtrCTask pTask);

  //客户端断开任务
  //参数：传入任务对象指针

};

#endif