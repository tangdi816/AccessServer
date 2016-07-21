/*
**ͨ��������й���
**����ͨ��������ӣ�����
**���������������ģ�鴦��ͨ������
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

  //��ȡ�������
  void ReadTaskQueue();

  //д���������
  void WriteTaskQueue(SPtrCTask spTask);

  //��ȡ��ǰ��ȡ�߳�����
  size_t GetCurRTNum()
  {
    return m_tpReader.size();
  }
private:
  //ͨ���������
  std::queue<SPtrCTask> m_quTasks;

  //������ж���
  boost::mutex m_lkRead;
  //�������д��
  boost::mutex m_lkWrite;

  //������ж�ȡ�ź���
  boost::condition_variable m_cvRead;

  //��ȡ�����̳߳�
  ThreadPool m_tpReader;

  //���߳�ָ�����
  VctPT m_vctReadThread;
  //�߳�ָ�������
  boost::mutex m_lkRTQ;

  //���������
  CTaskParser m_oTParser;
};
#endif
