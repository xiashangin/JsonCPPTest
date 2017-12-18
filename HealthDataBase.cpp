#include "HealthDataBase.h"



CHealthDataBase::CHealthDataBase()
{
}


CHealthDataBase::~CHealthDataBase()
{
}

void* CHealthDataBase::getHealthData()
{
	switch (m_iType)
	{
	case TYPE_PPG:
		return &m_ppgData;

	case TYPE_ECG:
		return &m_ecgData;

	case TYPE_SPO2:
		return &m_spo2Data;

	case TYPE_GSR:
		return &m_gsrData;

	case TYPE_TEMP:
		return &m_tempData;

	case TYPE_BP:
		return &m_bpData;

	default:
		return nullptr;
	}
}

int CHealthDataBase::getDataType()
{
	return m_iType;
}

void CHealthDataBase::setDataType(const int iType)
{
	m_iType = iType;
}

void CHealthDataBase::setHealthData(void *lpHealthData)
{
	switch (m_iType)
	{
	case TYPE_PPG:
		m_ppgData = *(pdPPG *)lpHealthData;
		break;
	case TYPE_ECG:
		m_ecgData = *(pdECG *)lpHealthData;
		break;

	case TYPE_SPO2:
		m_spo2Data = *(pdSPO2 *)lpHealthData;
		break;

	case TYPE_GSR:
		m_gsrData = *(pdGSR *)lpHealthData;
		break;

	case TYPE_TEMP:
		m_tempData = *(pdTEMP *)lpHealthData;
		break;

	case TYPE_BP:
		m_bpData = *(pdBP *)lpHealthData;
		break;

	default:
		if (m_strErr->length() > 0)
			m_strErr->clear();
		*m_strErr = "unknown data type, type = ";
		m_strErr->append(int2str(1));
		
		break;
	}
}

std::string int2str(const int &int_temp)
{
	std::string str;
	std::stringstream st;
	st << int_temp;
	st >> str;
	return str;
}
