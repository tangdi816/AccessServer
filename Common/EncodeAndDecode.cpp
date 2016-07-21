#include "EncodeAndDecode.h"

using namespace std;

//字符串加密解密函数，加解密使用同一个函数
//参数1：原字符串
//参数2：key串
//返回加解密之后的字符串
string CEncodeAndDecode::CodingByString(const string& strSource, const string& strKey)
{
  string strRes;
  //提取原串长度
  size_t iLenSrc=strSource.length();
  //提取key串的长度
  size_t iLenKey=strKey.length();
  for(size_t i=0; i<iLenSrc; ++i){
  	unsigned char cCode=CodingByChar(strSource[i], strKey[i%iLenKey]);
    strRes+=cCode;
  }
  return strRes;
}

//单字符加解密
//参数1：原字符
//参数2：key字符
//返回加解密之后的字符
unsigned char CEncodeAndDecode::CodingByChar(const unsigned char& cSource, const unsigned char& cKey)
{
  unsigned char cRes=cSource^cKey;
  return cRes;
}