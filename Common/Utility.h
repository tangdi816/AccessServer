/*
**----- ���ߺ����࣬��̬�� ----
** 1����ȡ��ǰĿ¼·��
** 1����ȡ�����ļ�����·��
*/
#ifndef __UTILITY_H__
#define __UTILITY_H__
#include <string>

class CUtility
{
public:
  //��ȡ��ǰ·��������·��
  static std::string GetCurrPath();

  //��ȡ�����ļ�����·��
  static std::string GetConfigFilePath();
};
#endif
