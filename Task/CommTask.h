/*
**通信任务类，实现通信任务队列节点
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

  //任务类型枚举
  enum class TaskType
  {
    CLIENTLINK=1,   //客户端连接
    CLIENTCLOSE,    //客户端断开
    CLIENTMSG,      //客户端消息
    SERVERMSG       //服务器消息
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

  //设置任务类型
  void SetType(TaskType eType)
  {
    m_eType=eType;
  }

  //获取任务类型
  TaskType GetType()
  {
    return m_eType;
  }

  //设置socket句柄
  void SetHDL(CHDL hdl)
  {
    m_hdlClient=hdl;
  }

  //获取socket句柄
  CHDL GetHDL()
  {
    return m_hdlClient;
  }

  //设置任务数据
  void SetData(std::string strData)
  {
    m_strData=strData;
  }

  //获取任务数据
  std::string GetData()
  {
    return m_strData;
  }
private:
  std::string m_strData;    //数据串
  CHDL m_hdlClient;         //客户端连接句柄
  TaskType m_eType;         //任务类型
};
#endif


