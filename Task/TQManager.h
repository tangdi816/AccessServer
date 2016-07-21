/*
**通信任务队列管理
**负责通信任务入队，出队
**调用任务解析处理模块处理通信任务
*/
#ifndef __TQ_MANAGER_H__
#define __TQ_MANAGER_H__
#include <queue>
#include <vector>
#include <boost/smart_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/thread/lock_factories.hpp>
#include <boost/bind.hpp>
#include "CommTask.h"
#include "TaskParser.h"

class CTQManager
{
public:
  typedef boost::shared_ptr<CCommTask> SPtrCTask;
  typedef boost::thread_group ThreadPool;
  typedef std::vector<boost::thread*> VctPT;

  CTQManager();
  ~CTQManager();

  //读取任务队列
  void ReadTaskQueue();

  //写入任务队列
  void WriteTaskQueue(SPtrCTask spTask);

  //获取当前读取线程数量
  size_t GetCurRTNum()
  {
    return m_tpReader.size();
  }
private:
  //通信任务队列
  std::queue<SPtrCTask> m_quTasks;

  //任务队列读锁
  boost::mutex m_lkRead;
  //任务队列写锁
  boost::mutex m_lkWrite;

  //任务队列读取信号量
  boost::condition_variable m_cvRead;

  //读取任务线程池
  ThreadPool m_tpReader;

  //读线程指针队列
  VctPT m_vctReadThread;
  //线程指针队列锁
  boost::mutex m_lkRTQ;

  //任务解析器
  CTaskParser m_oTParser;
};
#endif
