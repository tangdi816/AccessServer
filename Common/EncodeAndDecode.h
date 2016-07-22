/*
**字符串加解密类，静态类
**将字符串中每个字节，于key串中每个字节进行异或，从而生成加密串和解密串
*/
#ifndef __ENCODE_AND_DECODE_H__
#define __ENCODE_AND_DECODE_H__
#include <string>

class CEncodeAndDecode
{
public:
  //字符串加密解密函数，加解密使用同一个函数
  //参数1：原字符串
  //参数2：key串
  //返回加解密之后的字符串
  static std::string CodingByString(const std::string& strSource, const std::string& strKey);

  //单字符加解密
  //参数1：原字符
  //参数2：key字符
  //返回加解密之后的字符
  static unsigned char CodingByChar(const unsigned char& cSource, const unsigned char& cKey);
};
#endif
