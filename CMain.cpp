/*
**�����ǹ� ��������� ��������
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