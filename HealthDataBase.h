#pragma once
#include "healthData.h"

#define TYPE_UNKNOWN	149
#define TYPE_PPG		150
#define TYPE_ECG		151
#define TYPE_SPO2		152
#define TYPE_GSR		153
#define TYPE_TEMP		154
#define TYPE_BP			155

#define TYPE_PERSONINFO	160

#define TYPE_ECGREPLY	165

#include <queue>
std::string int2str(const int &int_temp);

class CHealthDataBase
{
public:
	CHealthDataBase();
	~CHealthDataBase();

	void * getHealthData();
	void setHealthData(void *lpHealthData);
	int  getDataType();
	void setDataType(const int iType);

	void clearHealthData();
private:
	pdPPG	m_ppgData;
	pdECG	m_ecgData;
	pdSPO2	m_spo2Data;
	pdGSR	m_gsrData;
	pdTEMP	m_tempData;
	pdBP	m_bpData;
	
	pdPersonInfo	m_personInfo;
	pdECGRespond	m_ecgRespond;
	
	std::queue<pdPPG>	m_ppgDataQueue;
	std::queue<pdECG>	m_ecgDataQueue;
	std::queue<pdSPO2>	m_spo2DataQueue;
	std::queue<pdGSR>	m_gsrDataQueue;
	std::queue<pdTEMP>	m_tempDataQueue;
	std::queue<pdBP>	m_bpDataQueue;
	
	std::queue<pdPersonInfo>	m_personInfoQueue;
	std::queue<pdECGRespond>	m_ecgRespondQueue;

	int m_iType;
	std::queue<int>	m_iTypeQueue;
	std::shared_ptr<std::string> m_strErr;
};

