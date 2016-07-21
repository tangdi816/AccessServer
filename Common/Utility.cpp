#include "Utility.h"
#include <boost/filesystem.hpp>

using namespace std;
using namespace boost::filesystem;

//获取当前路径，绝对路径
string CUtility::GetCurrPath()
{
  string strPaht=current_path().string();
  return strPaht;
}

//获取配置文件绝对路径
string CUtility::GetConfigFilePath()
{
  //当前路径
  string strPath=CUtility::GetCurrPath();
  //拼装配置文件路径
  strPath+="\\conf.json";
  return strPath;
}