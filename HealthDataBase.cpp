#include "HealthDataBase.h"

#include <iostream>
#include <sstream>

CHealthDataBase::CHealthDataBase()
{
	m_strErr = std::make_shared<std::string>();
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
	//return m_iType;
	if (!m_parsedDataTypeQueue.empty())
	{
		m_iType = m_parsedDataTypeQueue.front();
		m_parsedDataTypeQueue.pop();
	}
	else
		m_iType = 0;
	return m_iType;
}

void CHealthDataBase::setDataType(const int iType)
{
	m_iType = iType;
	m_parsedDataTypeQueue.push(iType);
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
		if ((*m_strErr).length() > 0)
			(*m_strErr).clear();
		*m_strErr = "unknown data type, type = ";
		m_strErr->append(int2str(1));
		
		break;
	}
}

void CHealthDataBase::clearHealthData()
{
	*m_ppgData.m_fv.m_freq = "";
	(*m_ppgData.m_fv.m_listValue).clear();
	*m_ppgData.m_pdHR = "";
	*m_ppgData.m_timeId.m_pdPersonId = "";
	*m_ppgData.m_timeId.m_pdTime = "";

	*m_ecgData.m_fv.m_freq = "";
	(*m_ecgData.m_fv.m_listValue).clear();
	*m_ecgData.m_pdHR = "";
	*m_ecgData.m_timeId.m_pdPersonId = "";
	*m_ecgData.m_timeId.m_pdTime = "";

	*m_spo2Data.m_fv.m_freq = "";
	(*m_spo2Data.m_fv.m_listValue).clear();
	*m_spo2Data.m_pdHR = "";
	*m_spo2Data.m_pdSP = "";
	*m_spo2Data.m_timeId.m_pdPersonId = "";
	*m_spo2Data.m_timeId.m_pdTime = "";

	*m_gsrData.m_fv.m_freq = "";
	(*m_gsrData.m_fv.m_listValue).clear();
	*m_gsrData.m_timeId.m_pdPersonId = "";
	*m_gsrData.m_timeId.m_pdTime = "";

	*m_tempData.m_timeId.m_pdPersonId = "";
	*m_tempData.m_timeId.m_pdTime = "";
	*m_tempData.m_pdHeat = "";
	*m_tempData.m_pdIR = "";

	*m_bpData.m_timeId.m_pdPersonId = "";
	*m_bpData.m_timeId.m_pdTime = "";
	*m_bpData.m_pdL = "";
	*m_bpData.m_pdH = "";
	*m_bpData.m_pdHR = "";
}

std::string int2str(const int &int_temp)
{
	std::string str;
	std::stringstream st;
	st << int_temp;
	st >> str;
	return str;
}
