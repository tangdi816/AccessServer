#include "Utility.h"
#include <boost/filesystem.hpp>

using namespace std;
using namespace boost::filesystem;

//��ȡ��ǰ·��������·��
string CUtility::GetCurrPath()
{
  string strPaht=current_path().string();
  return strPaht;
}

//��ȡ�����ļ�����·��
string CUtility::GetConfigFilePath()
{
  //��ǰ·��
  string strPath=CUtility::GetCurrPath();
  //ƴװ�����ļ�·��
  strPath+="\\conf.json";
  return strPath;
}