#pragma once

#include "healthData.h"

#define ECGSPECULATION	"ECG"

class CDataSpeculation
{
public:
	CDataSpeculation(std::string strIp);
	~CDataSpeculation();

	/************************************************************************/
	/*����˵������ECG����Ԥ��ģ��������Ԥ����                                */
	/*����˵����ecgData-->Ԥ���ECG���ݼ������ݼ���С���������С���ܼ�����ڴ����ƣ�
			���ecgDataʱ��ֻ����ecgData.m_fv.m_listValue�ֶ�
			   strOutResult-->Ԥ������������json���飻�쳣�����쳣��Ϣ	    */
		/*����ֵ˵����0->�ɹ�
					HTTP_CONNFAIL->����http����ʧ��
					PACK_INVALIDREPLY->httpӦ��������json��ʽ*/
	/************************************************************************/

	int ecgSpeculation(const pdECG & ecgData, std::string &strOutResult);
protected:
	void *m_httpClient;
	std::vector<std::string> m_httpReply;
	bool m_bConnected;
	std::string m_errStr;
};

