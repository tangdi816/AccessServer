/*
**超级糖果 接入服务器 启动函数
*/
#include <iostream>
#include "TQManager.h"

using namespace std;

int main()
{
  CTQManager oTaskQueue;
  Sleep(10000);
  cout<<oTaskQueue.GetCurRTNum()<<endl;

  getchar();
}