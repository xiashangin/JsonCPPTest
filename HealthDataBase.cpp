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
	{
		if (m_ppgDataQueue.empty())
			return nullptr;
		m_ppgData = m_ppgDataQueue.front();
		m_ppgDataQueue.pop();
		return &m_ppgData;
	}

	case TYPE_ECG:
	{
		if (m_ecgDataQueue.empty())
			return nullptr;
		m_ecgData = m_ecgDataQueue.front();
		m_ecgDataQueue.pop();
		return &m_ecgData;
	}

	case TYPE_SPO2:
	{
		if (m_spo2DataQueue.empty())
			return nullptr;
		m_spo2Data = m_spo2DataQueue.front();
		m_spo2DataQueue.pop();
		return &m_spo2Data;
	}

	case TYPE_GSR:
	{
		if (m_gsrDataQueue.empty())
			return nullptr;
		m_gsrData = m_gsrDataQueue.front();
		m_gsrDataQueue.pop();
		return &m_gsrData;
	}

	case TYPE_TEMP:
	{
		if (m_tempDataQueue.empty())
			return nullptr;
		m_tempData = m_tempDataQueue.front();
		m_tempDataQueue.pop();
		return &m_tempData;
	}

	case TYPE_BP:
	{
		if (m_bpDataQueue.empty())
			return nullptr;
		m_bpData = m_bpDataQueue.front();
		m_bpDataQueue.pop();
		return &m_bpData;
	}

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
		m_ppgDataQueue.push(m_ppgData);
		break;
	case TYPE_ECG:
		m_ecgData = *(pdECG *)lpHealthData;
		m_ecgDataQueue.push(m_ecgData);
		break;

	case TYPE_SPO2:
		m_spo2Data = *(pdSPO2 *)lpHealthData;
		m_spo2DataQueue.push(m_spo2Data);
		break;

	case TYPE_GSR:
		m_gsrData = *(pdGSR *)lpHealthData;
		m_gsrDataQueue.push(m_gsrData);
		break;

	case TYPE_TEMP:
		m_tempData = *(pdTEMP *)lpHealthData;
		m_tempDataQueue.push(m_tempData);
		break;

	case TYPE_BP:
		m_bpData = *(pdBP *)lpHealthData;
		m_bpDataQueue.push(m_bpData);
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
	while (m_ppgDataQueue.size())
		m_ppgDataQueue.pop();
	while (m_ecgDataQueue.size())
		m_ecgDataQueue.pop();
	while (m_gsrDataQueue.size())
		m_gsrDataQueue.pop();
	while (m_spo2DataQueue.size())
		m_spo2DataQueue.pop();
	while (m_tempDataQueue.size())
		m_tempDataQueue.pop();
	while (m_bpDataQueue.size())
		m_bpDataQueue.pop();
	while (m_parsedDataTypeQueue.size())
		m_parsedDataTypeQueue.pop();

	//*m_ppgData.m_fv.m_freq = "";
	//(*m_ppgData.m_fv.m_listValue).clear();
	//*m_ppgData.m_pdHR = "";
	//*m_ppgData.m_timeId.m_pdPersonId = "";
	//*m_ppgData.m_timeId.m_pdTime = "";

	//*m_ecgData.m_fv.m_freq = "";
	//(*m_ecgData.m_fv.m_listValue).clear();
	//*m_ecgData.m_pdHR = "";
	//*m_ecgData.m_timeId.m_pdPersonId = "";
	//*m_ecgData.m_timeId.m_pdTime = "";

	//*m_spo2Data.m_fv.m_freq = "";
	//(*m_spo2Data.m_fv.m_listValue).clear();
	//*m_spo2Data.m_pdHR = "";
	//*m_spo2Data.m_pdSP = "";
	//*m_spo2Data.m_timeId.m_pdPersonId = "";
	//*m_spo2Data.m_timeId.m_pdTime = "";

	//*m_gsrData.m_fv.m_freq = "";
	//(*m_gsrData.m_fv.m_listValue).clear();
	//*m_gsrData.m_timeId.m_pdPersonId = "";
	//*m_gsrData.m_timeId.m_pdTime = "";

	//*m_tempData.m_timeId.m_pdPersonId = "";
	//*m_tempData.m_timeId.m_pdTime = "";
	//*m_tempData.m_pdHeat = "";
	//*m_tempData.m_pdIR = "";

	//*m_bpData.m_timeId.m_pdPersonId = "";
	//*m_bpData.m_timeId.m_pdTime = "";
	//*m_bpData.m_pdL = "";
	//*m_bpData.m_pdH = "";
	//*m_bpData.m_pdHR = "";
}

std::string int2str(const int &int_temp)
{
	std::string str;
	std::stringstream st;
	st << int_temp;
	st >> str;
	return str;
}
