#pragma once
#include "healthData.h"

#define TYPE_PPG		150
#define TYPE_ECG		151
#define TYPE_SPO2		152
#define TYPE_GSR		153
#define TYPE_TEMP		154
#define TYPE_BP			155
#define TYPE_UNKNOWN	149


#include <memory>
std::string int2str(const int &int_temp);

class CHealthDataBase
{
public:
	CHealthDataBase();
	~CHealthDataBase();

	void * getHealthData();
	int getDataType();
	void setDataType(const int iType);
	void setHealthData(void *lpHealthData);
private:

	pdPPG m_ppgData;
	pdECG m_ecgData;
	pdSPO2 m_spo2Data;
	pdGSR m_gsrData;
	pdTEMP m_tempData;
	pdBP m_bpData;
	int m_iType;
	std::shared_ptr<std::string> m_strErr;
};

