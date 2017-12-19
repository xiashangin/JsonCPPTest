#include "ParseHealthData.h"

#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>

CParseHealthData::CParseHealthData()
{
}


CParseHealthData::~CParseHealthData()
{
}

int CParseHealthData::parseFromFile(const std::string & strFileName)
{
	std::ifstream ifs; //标准输入流
	ifs.open(strFileName.c_str(), std::ifstream::binary);
	if (!ifs.is_open())
	{
		std::cout << "open file " << strFileName << " failed!!!" << std::endl;
		return PARSE_FILENOTEXIST;
	}
	std::cout << "open file " << strFileName << " success!!!" << std::endl;

	Json::CharReaderBuilder builder;
	Json::Value jsonRoot;
	builder["collectComments"] = false;
	JSONCPP_STRING errs;
	bool is_ok = Json::parseFromStream(builder, ifs, &jsonRoot, &errs);
	if (!is_ok) //从ifs中读取数据到jsonRoot
	{
		std::cout << "parse Json file failed!!!" << std::endl;
		return PARSE_INVALIDJSON;
	}
	std::cout << "parse json file success!!!" << std::endl;

	//m_heathData.clearHealthData();
	if(parseDataGroup(jsonRoot))
		return PARSE_OK;
	else
		return PARSE_KEYNOTEXIST;
	//if (parseJson(jsonRoot))
	//	return PARSE_OK;
	//else
	//	return PARSE_KEYNOTEXIST;
}
int CParseHealthData::parseFromString(const std::string & strJsonString)
{
	Json::CharReaderBuilder builder;
	Json::CharReader* reader(builder.newCharReader());
	Json::Value jsonRoot;
	JSONCPP_STRING errs;
	const char* lpStrJson = strJsonString.c_str();
	bool is_ok = reader->parse(lpStrJson, lpStrJson + strlen(lpStrJson), &jsonRoot, &errs);
	if (!is_ok || errs.size() > 0) //从ifs中读取数据到jsonRoot
	{
		std::cout << "parse Json file failed!!! errstr = " << errs << std::endl;
		return PARSE_INVALIDJSON;
	}
	std::cout << "parse json file success!!!" << std::endl;
	
	if (parseDataGroup(jsonRoot))
		return PARSE_OK;
	else
		return PARSE_KEYNOTEXIST;

	//if (parseJson(jsonRoot))
	//	return PARSE_OK;
	//else
	//	return PARSE_KEYNOTEXIST;
}
std::string CParseHealthData::readFileIntoString(const char * filename)
{
	std::ifstream ifile(filename);
	std::ostringstream buf;
	char ch;
	while (buf && ifile.get(ch))
		buf.put(ch);
	return buf.str();
}
int CParseHealthData::getDataType()
{
	int iDataType = m_heathData.getDataType();
	return iDataType;
}
void * CParseHealthData::getHealthData()
{
	return m_heathData.getHealthData();
}

bool CParseHealthData::parseDataGroup(Json::Value & jsonRoot)
{
	//std::cout << jsonRoot.isArray() << std::endl;
	m_heathData.clearHealthData();
	if (!jsonRoot.isArray())
	{
		if (parseJson(jsonRoot))
			return true;
		else
			return false;
	}
	for (int i = 0; i < jsonRoot.size(); ++i)
	{
		std::cout << jsonRoot[i][PERSONID] << std::endl;
		if (!parseJson(jsonRoot[i]))
			return false;
	}
	return true;
}

bool CParseHealthData::parseJson(Json::Value & jsonRoot)
{

	bool bRlt = true;
	if (jsonRoot[PPG].isObject())
	{
		pdPPG ppgData;
		bRlt = __parseJson(jsonRoot, TYPE_PPG, &ppgData);
		if (bRlt)
		{
			m_heathData.setDataType(TYPE_PPG);
			m_heathData.setHealthData(&ppgData);
		}
	}
	else if (jsonRoot[ECG].isObject())
	{
		pdECG ecgData;
		bRlt = __parseJson(jsonRoot, TYPE_ECG, &ecgData);
		if (bRlt)
		{
			m_heathData.setDataType(TYPE_ECG);
			m_heathData.setHealthData(&ecgData);
		}
	}
	else if (jsonRoot[SPO2].isObject())
	{
		pdSPO2 spo2Data;
		bRlt = __parseJson(jsonRoot, TYPE_SPO2, &spo2Data);
		if (bRlt)
		{
			m_heathData.setDataType(TYPE_SPO2);
			m_heathData.setHealthData(&spo2Data);
		}
	}
	else if (jsonRoot[GSR].isObject())
	{
		pdGSR gsrData;
		bRlt = __parseJson(jsonRoot, TYPE_GSR, &gsrData);
		if (bRlt)
		{
			m_heathData.setDataType(TYPE_GSR);
			m_heathData.setHealthData(&gsrData);
		}
	}
	else if (jsonRoot[TEMP].isObject())
	{
		pdTEMP tempData;
		bRlt = __parseJson(jsonRoot, TYPE_TEMP, &tempData);
		if (bRlt)
		{
			m_heathData.setDataType(TYPE_TEMP);
			m_heathData.setHealthData(&tempData);
		}
	}
	else if (jsonRoot[BP].isObject())
	{
		pdBP bpData;
		bRlt = __parseJson(jsonRoot, TYPE_BP, &bpData);
		if (bRlt)
		{
			m_heathData.setDataType(TYPE_BP);
			m_heathData.setHealthData(&bpData);
		}
	}
	else
	{
		m_heathData.setDataType(TYPE_UNKNOWN);
		std::string strErr = "unknown data type-->";
		strErr.append(jsonRoot.getMemberNames()[0]);
		m_heathData.setHealthData((void *)strErr.c_str());
	}
	return bRlt;
}
bool CParseHealthData::__parseJson(Json::Value & jsonRoot, int iDataType, void *lpOutResult)
{
	bool bRlt = true;
	switch (iDataType)
	{
	case TYPE_PPG:
		if (jsonRoot[PPG].isObject())
		{
			pdPPG *pData = (pdPPG *)lpOutResult;
			if (!(*(pData->m_fv.m_listValue)).empty())
				(*(pData->m_fv.m_listValue)).clear();
			parsePPG(jsonRoot, *pData);
		}
		else
		{
			std::cout << "can not find type [" << PPG << "]" << std::endl;
			bRlt = false;
		}
		break;

	case TYPE_ECG:
		if (jsonRoot[ECG].isObject())
		{
			pdECG *pData = (pdECG *)lpOutResult;
			if (!(*(pData->m_fv.m_listValue)).empty())
				(*(pData->m_fv.m_listValue)).clear();
			parseECG(jsonRoot, *pData);
		}
		else
		{
			std::cout << "can not find type [" << ECG << "]" << std::endl;
			bRlt = false;
		}
		break;

	case TYPE_SPO2:
		if (jsonRoot[SPO2].isObject())
		{
			pdSPO2 *pData = (pdSPO2 *)lpOutResult;
			if (!(*(pData->m_fv.m_listValue)).empty())
				(*(pData->m_fv.m_listValue)).clear();
			parseSPO2(jsonRoot, *pData);
		}
		else
		{
			std::cout << "can not find type [" << SPO2 << "]" << std::endl;
			bRlt = false;
		}
		break;

	case TYPE_GSR:
		if (jsonRoot[GSR].isObject())
		{
			pdGSR *pData = (pdGSR *)lpOutResult;
			if (!(*(pData->m_fv.m_listValue)).empty())
				(*(pData->m_fv.m_listValue)).clear();
			parseGSR(jsonRoot, *pData);
		}
		else
		{
			std::cout << "can not find type [" << GSR << "]" << std::endl;
			bRlt = false;
		}
		break;

	case TYPE_TEMP:
		if (jsonRoot[TEMP].isObject())
		{
			pdTEMP *pData = (pdTEMP *)lpOutResult;
			parseTEMP(jsonRoot, *pData);
		}
		else
		{
			std::cout << "can not find type [" << TEMP << "]" << std::endl;
			bRlt = false;
		}
		break;

	case TYPE_BP:
		if (jsonRoot[BP].isObject())
		{
			pdBP *pData = (pdBP *)lpOutResult;
			parseBP(jsonRoot, *pData);
		}
		else
		{
			std::cout << "can not find type [" << BP << "]" << std::endl;
			bRlt = false;
		}
		break;
	default:
		std::cout << "unknown data type [" << iDataType << "]" << std::endl;
		bRlt = false;
		break;
	}
	return bRlt;
}
bool CParseHealthData::openFile(const char * lpStrFileName)
{
	std::ifstream ifs; //标准输入流
	ifs.open(lpStrFileName, std::ifstream::binary);
	if (!ifs.is_open())
	{
		std::cout << "open file " << lpStrFileName << " failed!!!" << std::endl;
		getchar();
		return false;
	}
	std::cout << "open file " << lpStrFileName << " success!!!" << std::endl;
	return true;
}

bool CParseHealthData::getFreqVal(Json::Value &jsonValue, freqAndValue & fv, const char * strRoot)
{
	bool bRlt = true;
	if (jsonValue[strRoot][COLLECTFREQ].isNull())		//采样频率
	{
		std::cout << "[" << strRoot << "]" << "[" << COLLECTFREQ << "]"
			<< " is null" << std::endl;
		bRlt = false;
	}
	else
		*fv.m_freq = int2str(jsonValue[strRoot][COLLECTFREQ].asInt());

	if (jsonValue[strRoot][COLLECTVAL].isNull())		//采样值
	{
		std::cout << "[" << strRoot << "]" << "[" << COLLECTVAL << "]"
			<< " is null" << std::endl;
		bRlt = false;
	}
	else
	{
		Json::Value v = jsonValue[strRoot][COLLECTVAL];
		for (unsigned int i = 0; i < v.size(); ++i)
		{
			PData pd(new std::string);
			*pd = int2str(v[i].asInt());
			fv.m_listValue.get()->push_back(pd);
		}
	}
	return bRlt;
}
bool CParseHealthData::getTimeId(Json::Value &jsonValue, timeAndId & timeId)
{
	bool bRlt = true;

	//if (jsonValue[COLLECTTIME].isNull())		//采样时间
	//{
	//	std::cout << "[" << COLLECTTIME << "]"
	//		<< " is null" << std::endl;
	//	bRlt = false;
	//}
	//else
	//	*timeId.m_pdTime = jsonValue[COLLECTTIME].asString();

	if (jsonValue[PERSONID].isNull())		//人员ID
	{
		std::cout << "[" << PERSONID << "]"
			<< " is null" << std::endl;
		bRlt = false;
	}
	else
		*timeId.m_pdPersonId = jsonValue[PERSONID].asString();
	return bRlt;
}

bool CParseHealthData::parsePPG(Json::Value &jsonValue, pdPPG & ppgData)
{
	bool bRlt = getFreqVal(jsonValue, ppgData.m_fv, PPG);
	bRlt = getTimeId(jsonValue, ppgData.m_timeId);

	if (jsonValue[PPG][HR].isNull())		//HR
	{
		std::cout << "[" << PPG << "]" << "[" << HR << "]" << " is null" << std::endl;
		bRlt = false;
	}
	else
		*ppgData.m_pdHR = jsonValue[PPG][HR].asString();

	return bRlt;
}
bool CParseHealthData::parseECG(Json::Value &jsonValue, pdECG & ecgData)
{
	bool bRlt = getFreqVal(jsonValue, ecgData.m_fv, ECG);
	bRlt = getTimeId(jsonValue, ecgData.m_timeId);

	if (jsonValue[ECG][HR].isNull())		//HR
	{
		std::cout << "[" << ECG << "]" << "[" << HR << "]" << " is null" << std::endl;
		bRlt = false;
	}
	else
		*ecgData.m_pdHR = jsonValue[ECG][HR].asString();

	return bRlt;
}
bool CParseHealthData::parseSPO2(Json::Value &jsonValue, pdSPO2 & spo2Data)
{
	bool bRlt = getFreqVal(jsonValue, spo2Data.m_fv, SPO2);
	bRlt = getTimeId(jsonValue, spo2Data.m_timeId);

	if (jsonValue[SPO2][HR].isNull())		//HR
	{
		std::cout << "[" << SPO2 << "]" << "[" << HR << "]" << " is null" << std::endl;
		bRlt = false;
	}
	else
		*spo2Data.m_pdHR = jsonValue[SPO2][HR].asString();

	if (jsonValue[SPO2][SP].isNull())		//SP
	{
		std::cout << "[" << SPO2 << "]" << "[" << SP << "]" << " is null" << std::endl;
		bRlt = false;
	}
	else
		*spo2Data.m_pdSP = jsonValue[SPO2][SP].asString();
	return bRlt;
}
bool CParseHealthData::parseGSR(Json::Value &jsonValue, pdGSR & gsrData)
{
	bool bRlt = getFreqVal(jsonValue, gsrData.m_fv, GSR);
	bRlt = getTimeId(jsonValue, gsrData.m_timeId);

	return bRlt;
}
bool CParseHealthData::parseTEMP(Json::Value &jsonValue, pdTEMP & tempData)
{
	bool bRlt = getTimeId(jsonValue, tempData.m_timeId);
	if (jsonValue[TEMP][HEAT].isNull())		//温度传感器值
	{
		std::cout << "[" << TEMP << "]" << "[" << HEAT << "]" << " is null" << std::endl;
		bRlt = false;
	}
	else
		*tempData.m_pdHeat = jsonValue[TEMP][HEAT].asString();

	if (jsonValue[TEMP][IR].isNull())		//红外体温值
	{
		std::cout << "[" << TEMP << "]" << "[" << IR << "]" << " is null" << std::endl;
		bRlt = false;
	}
	else
		*tempData.m_pdIR = jsonValue[TEMP][IR].asString();
	return bRlt;
}
bool CParseHealthData::parseBP(Json::Value &jsonValue, pdBP & bpData)
{
	bool bRlt = getTimeId(jsonValue, bpData.m_timeId);
	if (jsonValue[BP][BP_H].isNull())		//高压值
	{
		std::cout << "[" << BP << "]" << "[" << BP_H << "]" << " is null" << std::endl;
		bRlt = false;
	}
	else
		*bpData.m_pdH = jsonValue[BP][BP_H].asString();

	if (jsonValue[BP][BP_L].isNull())		//低压值
	{
		std::cout << "[" << BP << "]" << "[" << BP_L << "]" << " is null" << std::endl;
		bRlt = false;
	}
	else
		*bpData.m_pdL = jsonValue[BP][BP_L].asString();

	if (jsonValue[BP][HR].isNull())		//脉搏心率值
	{
		std::cout << "[" << BP << "]" << "[" << HR << "]" << " is null" << std::endl;
		bRlt = false;
	}
	else
		*bpData.m_pdHR = jsonValue[BP][HR].asString();

	return bRlt;
}


