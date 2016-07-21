#include "EncodeAndDecode.h"

using namespace std;

//�ַ������ܽ��ܺ������ӽ���ʹ��ͬһ������
//����1��ԭ�ַ���
//����2��key��
//���ؼӽ���֮����ַ���
string CEncodeAndDecode::CodingByString(const string& strSource, const string& strKey)
{
  string strRes;
  //��ȡԭ������
  size_t iLenSrc=strSource.length();
  //��ȡkey���ĳ���
  size_t iLenKey=strKey.length();
  for(size_t i=0; i<iLenSrc; ++i){
  	unsigned char cCode=CodingByChar(strSource[i], strKey[i%iLenKey]);
    strRes+=cCode;
  }
  return strRes;
}

//���ַ��ӽ���
//����1��ԭ�ַ�
//����2��key�ַ�
//���ؼӽ���֮����ַ�
unsigned char CEncodeAndDecode::CodingByChar(const unsigned char& cSource, const unsigned char& cKey)
{
  unsigned char cRes=cSource^cKey;
  return cRes;
}