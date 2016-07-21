#include "CInfoManager.h"

using namespace std;
using namespace boost;

CCInfoManager::CCInfoManager()
{
}


CCInfoManager::~CCInfoManager()
{
}

//����ͻ�����Ϣ
//����1���ͻ������Ӿ��
//����2���ͻ���UUID
void CCInfoManager::InsertCInfo(CHDL pHdl, const string& strUUID)
{
  {
    //��ס��
    lock_guard<mutex> lkg(m_lkMap);
    if(!m_mapCIM.insert(make_pair(pHdl, strUUID)).second){
      //����ʧ��
      auto itFider=m_mapCIM.find(pHdl);
      //�ҵ�֮ǰ����ͻ�����Ϣ
      if(itFider!=m_mapCIM.end()){
        //���Ŀͻ���UUID
      	(*itFider).second=strUUID;
      }
    }
  }//������
}
