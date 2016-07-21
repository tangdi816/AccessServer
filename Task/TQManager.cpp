#include "TQManager.h"

using namespace boost;
using namespace std;

CTQManager::CTQManager()
{
  //����������ȡ�߳�
  for( int i=0; i<5; ++i ){
    thread* pThread=m_tpReader.create_thread(bind(&CTQManager::ReadTaskQueue, this));
    {
      //�����߳�ָ�����
      boost::lock_guard<mutex> lk(m_lkRTQ);
      //�����½��߳�ָ��
      m_vctReadThread.push_back(pThread);
    }
  }
    
}


CTQManager::~CTQManager()
{}

//��ȡ�������
void CTQManager::ReadTaskQueue()
{
  //��ѭ����ȡ�������
  for(;;){
    //������ȡ������
    auto lkRead=make_unique_lock(m_lkRead);

    //ѭ����ѯ��������Ƿ�Ϊ��
    for(; m_quTasks.empty();){
      //����Ϊ�գ��Ҷ�ȡ�߳�������2���������Լ��߳�
      if(2<m_tpReader.size()){
        {
          //�����߳�ָ�����
          boost::lock_guard<mutex> lk(m_lkRTQ);
          //�����߳�ָ�����
          for(vector<thread*>::iterator it=m_vctReadThread.begin(); it!=m_vctReadThread.end(); ++it){
          	thread* pThread=*it;
            //�ҵ���ǰ�߳�ָ��
            if(this_thread::get_id()==pThread->get_id()){
              //����ǰ�̴߳��̳߳���ɾ��
              m_tpReader.remove_thread(pThread);
              //���߳�ָ�������ɾ����ǰ�߳�ָ��
            	m_vctReadThread.erase(it);
              break;
            }
          }//end for
        }
        return;
      }

      //�������Ϊ�գ������ȴ��ɶ��ź�������
      m_cvRead.wait(lkRead);
    }

    //��ȡ��ɾ����������
    auto spTask=m_quTasks.front();
    m_quTasks.pop();

    //������ִ������
    m_oTParser.ResolveTask(spTask);
  }//end for ��ѭ����ȡ�������
}

//д���������
void CTQManager::WriteTaskQueue(SPtrCTask spTask)
{
  {
    //��������д��
    auto lkWrite=make_unique_lock(m_lkWrite);
    //������������
    m_quTasks.push(spTask);
  }

  //��ȡ��������������
  int iTaskNum=m_quTasks.size();

  //���Ϳɶ�ȡ�ź���
  m_cvRead.notify_one();

  //��ȡ��ǰ�̳߳����߳�����
  int iThreadNum=m_tpReader.size();

  //�������������߳�����10��
  if(10.0>iTaskNum/iThreadNum){
    //���һ����ȡ�̴߳�������
    thread* pThread=m_tpReader.create_thread(bind(&CTQManager::ReadTaskQueue, this));
    {
      //�����߳�ָ�����
      boost::lock_guard<mutex> lk(m_lkRTQ);
      //�����½��߳�ָ��
      m_vctReadThread.push_back(pThread);
    }
  }
}
