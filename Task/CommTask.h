/*
**ͨ�������࣬ʵ��ͨ��������нڵ�
*/
#ifndef __TASK_H__
#define __TASK_H__
#include <string>
#include <iostream>
#include <websocketpp/server.hpp>

class CCommTask
{
public:
  typedef websocketpp::connection_hdl CHDL;

  //��������ö��
  enum class TaskType
  {
    CLIENTLINK=1,   //�ͻ�������
    CLIENTCLOSE,    //�ͻ��˶Ͽ�
    CLIENTMSG,      //�ͻ�����Ϣ
    SERVERMSG       //��������Ϣ
  };

  CCommTask(TaskType eType, CHDL hdl)
    :m_eType(eType)
    ,m_hdlClient(hdl)
  {
  }

  CCommTask(TaskType eType, CHDL hdl, const std::string& strData)
    :m_eType(eType)
    ,m_hdlClient(hdl)
    ,m_strData(strData)
  {
  }

  ~CCommTask()
  {
  }

  //������������
  void SetType(TaskType eType)
  {
    m_eType=eType;
  }

  //��ȡ��������
  TaskType GetType()
  {
    return m_eType;
  }

  //����socket���
  void SetHDL(CHDL hdl)
  {
    m_hdlClient=hdl;
  }

  //��ȡsocket���
  CHDL GetHDL()
  {
    return m_hdlClient;
  }

  //������������
  void SetData(std::string strData)
  {
    m_strData=strData;
  }

  //��ȡ��������
  std::string GetData()
  {
    return m_strData;
  }
private:
  std::string m_strData;    //���ݴ�
  CHDL m_hdlClient;         //�ͻ������Ӿ��
  TaskType m_eType;         //��������
};
#endif


