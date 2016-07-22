/*
**超级糖果 接入服务器 启动函数
*/
#include <iostream>
#include <string>
#include "TQManager.h"
#include "EncodeAndDecode.h"
#include "CInfoManager.h"
#include "ClientLinker.h"

using namespace std;

//- - - - - - 全局变量 - - - - - - 
//客户端连接信息管理
CCInfoManager g_oClientManager;

//通信任务队列管理
CTQManager g_oTaskQueue;

//客户侧通信器
CClientLinker g_oCLinker;

int main()
{
//   Sleep(10000);
//   cout<<oTaskQueue.GetCurRTNum()<<endl;

//   string strSource="abcdef桑德菲杰-1234-56";
//   string strKey="7890sdfcnakn";
//   string strCoded=CEncodeAndDecode::CodingByString(strSource, strKey);
// 
//   cout<<strCoded<<endl;
//   strCoded=CEncodeAndDecode::CodingByString(strCoded, strKey);
//   cout<<strCoded<<endl;


  getchar();
}