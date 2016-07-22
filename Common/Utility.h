/*
**----- ���ߺ����࣬��̬�� ----
** 1����ȡ��ǰĿ¼·��
** 1����ȡ�����ļ�����·��
*/
#ifndef __UTILITY_H__
#define __UTILITY_H__
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

class CUtility
{
public:
  //��ȡ��ǰ·��������·��
  static std::string GetCurrPath();

  //��ȡ�����ļ�����·��
  static std::string GetConfigFilePath();

  //��ȡ�����ļ�ָ���ֶ�ֵ
  template<typename VType>
  static VType GetConfigValue(std::string strConfKey)
  {
      VType res;
      //��ȡ�����ļ�·��
      std::string strPath=CUtility::GetConfigFilePath();

      //��ȡָ�������ֶ�
      boost::property_tree::ptree oPt;
      read_json(strPath, oPt);
      res=oPt.get<VType>(strConfKey);

      return res;
  }


};
#endif
