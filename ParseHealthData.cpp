#include "ParseHealthData.h"

#include <fstream>
#include <cstring>


CParseHealthData::CParseHealthData()
{
}


CParseHealthData::~CParseHealthData()
{
}

bool CParseHealthData::parseFromFile(const std::string & strFileName, int iDataType, void *lpOutResult)
{	
	std::ifstream ifs; //��׼������
	ifs.open(strFileName.c_str(), std::ifstream::binary);
	if (!ifs.is_open())
	{
		std::cout << "open file " << strFileName << " failed!!!" << std::endl;
		getchar();
		return false;
	}
	std::cout << "open file " << strFileName << " success!!!" << std::endl;
	
	Json::CharReaderBuilder builder;
	Json::Value jsonRoot;
	builder["collectComments"] = false;
	JSONCPP_STRING errs;
	bool is_ok = Json::parseFromStream(builder, ifs, &jsonRoot, &errs);
	if (!is_ok) //��ifs�ж�ȡ���ݵ�jsonRoot
	{
		std::cout << "parse Json file failed!!!" << std::endl;
		getchar();
		return false;
	}
	std::cout << "parse json file success!!!" << std::endl;

	bool bRlt = parseJson(jsonRoot, iDataType, lpOutResult);
	return bRlt;
}

bool CParseHealthData::parseFromString(const std::string & strJsonString, int iDataType, void *lpOutResult)
{
	Json::CharReaderBuilder builder;
	Json::CharReader* reader(builder.newCharReader());
	Json::Value jsonRoot;
	JSONCPP_STRING errs;
	const char* lpStrJson = strJsonString.c_str();
	bool is_ok = reader->parse(lpStrJson, lpStrJson + strlen(lpStrJson), &jsonRoot, &errs);
	if (!is_ok || errs.size() > 0) //��ifs�ж�ȡ���ݵ�jsonRoot
	{
		std::cout << "parse Json file failed!!! errstr = " << errs << std::endl;
		getchar();
		return false;
	}
	std::cout << "parse json file success!!!" << std::endl;
	bool bRlt = parseJson(jsonRoot, iDataType, lpOutResult);
	return bRlt;
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

bool CParseHealthData::parseJson(Json::Value & jsonRoot, int iDataType, void *lpOutResult)
{
	bool bRlt = true;
	switch (iDataType)
	{
	case TYPE_PPG:
		if (jsonRoot[PPG].isObject())
		{
			pdPPG *pData = (pdPPG *)lpOutResult;
			if (!(*(pData->fv.listValue)).empty())
				(*(pData->fv.listValue)).clear();
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
			if (!(*(pData->fv.listValue)).empty())
				(*(pData->fv.listValue)).clear();
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
			if (!(*(pData->fv.listValue)).empty())
				(*(pData->fv.listValue)).clear();
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
			if (!(*(pData->fv.listValue)).empty())
				(*(pData->fv.listValue)).clear();
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
	std::ifstream ifs; //��׼������
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
	if (jsonValue[strRoot][COLLECTFREQ].isNull())		//����Ƶ��
	{
		std::cout << "[" << strRoot << "]" << "[" << COLLECTFREQ << "]"
			<< " is null" << std::endl;
		bRlt = false;
	}
	else
		*fv.freq = int2str(jsonValue[strRoot][COLLECTFREQ].asInt());

	if (jsonValue[strRoot][COLLECTVAL].isNull())		//����ֵ
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
			fv.listValue.get()->push_back(pd);
		}
	}
	return bRlt;
}
bool CParseHealthData::getTimeId(Json::Value &jsonValue, timeAndId & timeId)
{
	bool bRlt = true;

	if (jsonValue[COLLECTTIME].isNull())		//����ʱ��
	{
		std::cout << "[" << COLLECTTIME << "]"
			<< " is null" << std::endl;
		bRlt = false;
	}
	else
		*timeId.pdTime = jsonValue[COLLECTTIME].asString();

	if (jsonValue[PERSONID].isNull())		//��ԱID
	{
		std::cout << "[" << PERSONID << "]"
			<< " is null" << std::endl;
		bRlt = false;
	}
	else
		*timeId.pdPersonId = jsonValue[PERSONID].asString();
	return bRlt;
}

bool CParseHealthData::parsePPG(Json::Value &jsonValue, pdPPG & ppgData)
{
	bool bRlt = getFreqVal(jsonValue, ppgData.fv, PPG);
	bRlt = getTimeId(jsonValue, ppgData.timeId);

	if (jsonValue[PPG][HR].isNull())		//HRֵ
	{
		std::cout << "[" << PPG << "]" << "[" << HR << "]" << " is null" << std::endl;
		bRlt = false;
	}
	else
		*ppgData.pdHR = jsonValue[PPG][HR].asString();

	return bRlt;
}
bool CParseHealthData::parseECG(Json::Value &jsonValue, pdECG & ecgData)
{
	bool bRlt = getFreqVal(jsonValue, ecgData.fv, ECG);
	bRlt = getTimeId(jsonValue, ecgData.timeId);

	if (jsonValue[ECG][HR].isNull())		//HRֵ
	{
		std::cout << "[" << ECG << "]" << "[" << HR << "]" << " is null" << std::endl;
		bRlt = false;
	}
	else
		*ecgData.pdHR = jsonValue[ECG][HR].asString();

	return bRlt;
}
bool CParseHealthData::parseSPO2(Json::Value &jsonValue, pdSPO2 & spo2Data)
{
	bool bRlt = getFreqVal(jsonValue, spo2Data.fv, SPO2);
	bRlt = getTimeId(jsonValue, spo2Data.timeId);

	if (jsonValue[SPO2][HR].isNull())		//HRֵ
	{
		std::cout << "[" << SPO2 << "]" << "[" << HR << "]" << " is null" << std::endl;
		bRlt = false;
	}
	else
		*spo2Data.pdHR = jsonValue[SPO2][HR].asString();

	if (jsonValue[SPO2][SP].isNull())		//HRֵ
	{
		std::cout << "[" << SPO2 << "]" << "[" << SP << "]" << " is null" << std::endl;
		bRlt = false;
	}
	else
		*spo2Data.pdSP = jsonValue[SPO2][SP].asString();
	return bRlt;
}
bool CParseHealthData::parseGSR(Json::Value &jsonValue, pdGSR & gsrData)
{
	bool bRlt = getFreqVal(jsonValue, gsrData.fv, GSR);
	bRlt = getTimeId(jsonValue, gsrData.timeId);

	return bRlt;
}

bool CParseHealthData::parseTEMP(Json::Value &jsonValue, pdTEMP & tempData)
{
	bool bRlt = getTimeId(jsonValue, tempData.timeId);
	if (jsonValue[TEMP][HEAT].isNull())		//�¶ȴ�����ֵ
	{
		std::cout << "[" << TEMP << "]" << "[" << HEAT << "]" << " is null" << std::endl;
		bRlt = false;
	}
	else
		*tempData.pdHeat = jsonValue[TEMP][HEAT].asString();

	if (jsonValue[TEMP][IR].isNull())		//��������ֵ
	{
		std::cout << "[" << TEMP << "]" << "[" << IR << "]" << " is null" << std::endl;
		bRlt = false;
	}
	else
		*tempData.pdIR = jsonValue[TEMP][IR].asString();
	return bRlt;
}
bool CParseHealthData::parseBP(Json::Value &jsonValue, pdBP & bpData)
{
	bool bRlt = getTimeId(jsonValue, bpData.timeId);
	if (jsonValue[BP][BP_H].isNull())		//��ѹֵ
	{
		std::cout << "[" << BP << "]" << "[" << BP_H << "]" << " is null" << std::endl;
		bRlt = false;
	}
	else
		*bpData.pdH = jsonValue[BP][BP_H].asString();

	if (jsonValue[BP][BP_L].isNull())		//��ѹֵ
	{
		std::cout << "[" << BP << "]" << "[" << BP_L << "]" << " is null" << std::endl;
		bRlt = false;
	}
	else
		*bpData.pdL = jsonValue[BP][BP_L].asString();

	if (jsonValue[BP][PULSE].isNull())		//��������ֵ
	{
		std::cout << "[" << BP << "]" << "[" << PULSE << "]" << " is null" << std::endl;
		bRlt = false;
	}
	else
		*bpData.pdPulse = jsonValue[BP][PULSE].asString();

	return bRlt;
}

std::string CParseHealthData::int2str(const int &int_temp)
{
	std::string str;
	std::stringstream st;
	st << int_temp;
	st >> str;
	return str;
}
