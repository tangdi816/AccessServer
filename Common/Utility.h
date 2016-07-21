/*
**----- 工具函数类，静态类 ----
** 1、获取当前目录路径
** 1、获取配置文件绝对路径
*/
#ifndef __UTILITY_H__
#define __UTILITY_H__
#include <string>

class CUtility
{
public:
  //获取当前路径，绝对路径
  static std::string GetCurrPath();

  //获取配置文件绝对路径
  static std::string GetConfigFilePath();
};
#endif
