/*
**----- 工具函数类，静态类 ----
** 1、获取当前目录路径
** 1、获取配置文件绝对路径
*/
#ifndef __UTILITY_H__
#define __UTILITY_H__
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

class CUtility
{
public:
  //获取当前路径，绝对路径
  static std::string GetCurrPath();

  //获取配置文件绝对路径
  static std::string GetConfigFilePath();

  //获取配置文件指点字段值
  template<typename VType>
  static VType GetConfigValue(std::string strConfKey)
  {
      VType res;
      //获取配置文件路径
      std::string strPath=CUtility::GetConfigFilePath();

      //读取指定配置字段
      boost::property_tree::ptree oPt;
      read_json(strPath, oPt);
      res=oPt.get<VType>(strConfKey);

      return res;
  }


};
#endif
