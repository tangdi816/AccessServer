/*
**�ַ����ӽ����࣬��̬��
**���ַ�����ÿ���ֽڣ���key����ÿ���ֽڽ�����򣬴Ӷ����ɼ��ܴ��ͽ��ܴ�
*/
#ifndef __ENCODE_AND_DECODE_H__
#define __ENCODE_AND_DECODE_H__
#include <string>

class CEncodeAndDecode
{
public:
  //�ַ������ܽ��ܺ������ӽ���ʹ��ͬһ������
  //����1��ԭ�ַ���
  //����2��key��
  //���ؼӽ���֮����ַ���
  static std::string CodingByString(const std::string& strSource, const std::string& strKey);

  //���ַ��ӽ���
  //����1��ԭ�ַ�
  //����2��key�ַ�
  //���ؼӽ���֮����ַ�
  static unsigned char CodingByChar(const unsigned char& cSource, const unsigned char& cKey);
};
#endif
