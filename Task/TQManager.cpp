#include "TQManager.h"

using namespace boost;
using namespace std;

CTQManager::CTQManager()
{
  //开启两个读取线程
  for( int i=0; i<5; ++i ){
    thread* pThread=m_tpReader.create_thread(bind(&CTQManager::ReadTaskQueue, this));
    {
      //锁定线程指针队列
      boost::lock_guard<mutex> lk(m_lkRTQ);
      //保存新建线程指针
      m_vctReadThread.push_back(pThread);
    }
  }
    
}


CTQManager::~CTQManager()
{}

//读取任务队列
void CTQManager::ReadTaskQueue()
{
  //死循环读取任务队列
  for(;;){
    //锁定读取队列锁
    auto lkRead=make_unique_lock(m_lkRead);

    //循环查询任务队列是否为空
    for(; m_quTasks.empty();){
      //队列为空，且读取线程数超过2个，结束自己线程
      if(2<m_tpReader.size()){
        {
          //锁定线程指针队列
          boost::lock_guard<mutex> lk(m_lkRTQ);
          //遍历线程指针队列
          for(vector<thread*>::iterator it=m_vctReadThread.begin(); it!=m_vctReadThread.end(); ++it){
          	thread* pThread=*it;
            //找到当前线程指针
            if(this_thread::get_id()==pThread->get_id()){
              //将当前线程从线程池中删除
              m_tpReader.remove_thread(pThread);
              //从线程指针队列中删除当前线程指针
            	m_vctReadThread.erase(it);
              break;
            }
          }//end for
        }
        return;
      }

      //任务队列为空，阻塞等待可读信号量到达
      m_cvRead.wait(lkRead);
    }

    //提取并删除队首任务
    auto spTask=m_quTasks.front();
    m_quTasks.pop();

    //解析并执行任务
    m_oTParser.ResolveTask(spTask);
  }//end for 死循环读取任务队列
}

//写入任务队列
void CTQManager::WriteTaskQueue(SPtrCTask spTask)
{
  {
    //锁定队列写锁
    auto lkWrite=make_unique_lock(m_lkWrite);
    //将任务加入队列
    m_quTasks.push(spTask);
  }

  //提取队列中任务数量
  int iTaskNum=m_quTasks.size();

  //发送可读取信号量
  m_cvRead.notify_one();

  //提取当前线程池中线程数量
  int iThreadNum=m_tpReader.size();

  //任务数量超过线程数量10倍
  if(10.0>iTaskNum/iThreadNum){
    //添加一条读取线程处理任务
    thread* pThread=m_tpReader.create_thread(bind(&CTQManager::ReadTaskQueue, this));
    {
      //锁定线程指针队列
      boost::lock_guard<mutex> lk(m_lkRTQ);
      //保存新建线程指针
      m_vctReadThread.push_back(pThread);
    }
  }
}
