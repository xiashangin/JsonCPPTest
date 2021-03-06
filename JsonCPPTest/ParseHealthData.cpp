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
		if (!parseJson(jsonRoot[i]))
			return false;
	}
	return true;
}
bool CParseHealthData::parseJson(Json::Value & jsonRoot)
{
	bool bRlt = true;
	if (jsonRoot[PPG].isObject())
		bRlt = parsePPG(jsonRoot);
	else if (jsonRoot[ECG].isObject())
		bRlt = parseECG(jsonRoot);
	else if (jsonRoot[SPO2].isObject())
		bRlt = parseSPO2(jsonRoot);
	else if (jsonRoot[GSR].isObject())
		bRlt = parseGSR(jsonRoot);
	else if (jsonRoot[TEMP].isObject())
		bRlt = parseTEMP(jsonRoot);
	else if (jsonRoot[BP].isObject())
		bRlt = parseBP(jsonRoot);
	else if (jsonRoot[ECG_HTTP].isObject())
		bRlt = parseECGRespond(jsonRoot);
	else if (jsonRoot[PERSONINFO].isObject())
		bRlt = parsePersonInfo(jsonRoot);
	else
	{
		m_heathData.setDataType(TYPE_UNKNOWN);
		std::string strErr = "unknown data type-->";
		strErr.append(jsonRoot.getMemberNames()[0]);
		m_heathData.setHealthData((void *)strErr.c_str());
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
bool CParseHealthData::getBaseData(Json::Value &jsonValue, baseData & baseData)
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

	if (jsonValue[EXAMNUM].isNull())		//采样时间
	{
		std::cout << "[" << EXAMNUM << "]"
			<< " is null" << std::endl;
		bRlt = false;
	}
	else
		*baseData.m_pdNum = jsonValue[EXAMNUM].asString();

	if (jsonValue[PERSONID].isNull())		//人员ID
	{
		std::cout << "[" << PERSONID << "]"
			<< " is null" << std::endl;
		bRlt = false;
	}
	else
		*baseData.m_pdPersonId = jsonValue[PERSONID].asString();
	return bRlt;
}

bool CParseHealthData::parsePPG(Json::Value &jsonValue)
{
	pdPPG ppgData;
	bool bRlt = getFreqVal(jsonValue, ppgData.m_fv, PPG);
	bRlt = getBaseData(jsonValue, ppgData.m_timeId);

	if (jsonValue[PPG][HR].isNull())		//HR
	{
		std::cout << "[" << PPG << "]" << "[" << HR << "]" << " is null" << std::endl;
		bRlt = false;
	}
	else
		*ppgData.m_pdHR = jsonValue[PPG][HR].asString();

	if (bRlt)
	{
		m_heathData.setDataType(TYPE_PPG);
		m_heathData.setHealthData(&ppgData);
	}
	return bRlt;
}
bool CParseHealthData::parseECG(Json::Value &jsonValue)
{
	pdECG ecgData;
	bool bRlt = getFreqVal(jsonValue, ecgData.m_fv, ECG);
	bRlt = getBaseData(jsonValue, ecgData.m_timeId);

	if (jsonValue[ECG][HR].isNull())		//HR
	{
		std::cout << "[" << ECG << "]" << "[" << HR << "]" << " is null" << std::endl;
		bRlt = false;
	}
	else
		*ecgData.m_pdHR = jsonValue[ECG][HR].asString();

	if (bRlt)
	{
		m_heathData.setDataType(TYPE_ECG);
		m_heathData.setHealthData(&ecgData);
	}

	return bRlt;
}
bool CParseHealthData::parseSPO2(Json::Value &jsonValue)
{
	pdSPO2 spo2Data;
	bool bRlt = getFreqVal(jsonValue, spo2Data.m_fv, SPO2);
	bRlt = getBaseData(jsonValue, spo2Data.m_timeId);

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

	if (bRlt)
	{
		m_heathData.setDataType(TYPE_SPO2);
		m_heathData.setHealthData(&spo2Data);
	}
	return bRlt;
}
bool CParseHealthData::parseGSR(Json::Value &jsonValue)
{
	pdGSR gsrData;
	bool bRlt = getFreqVal(jsonValue, gsrData.m_fv, GSR);
	bRlt = getBaseData(jsonValue, gsrData.m_timeId);

	if (bRlt)
	{
		m_heathData.setDataType(TYPE_GSR);
		m_heathData.setHealthData(&gsrData);
	}
	return bRlt;
}
bool CParseHealthData::parseTEMP(Json::Value &jsonValue)
{
	pdTEMP tempData;
	bool bRlt = getBaseData(jsonValue, tempData.m_timeId);
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

	if (bRlt)
	{
		m_heathData.setDataType(TYPE_TEMP);
		m_heathData.setHealthData(&tempData);
	}
	return bRlt;
}
bool CParseHealthData::parseBP(Json::Value &jsonValue)
{
	pdBP bpData;
	bool bRlt = getBaseData(jsonValue, bpData.m_timeId);
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

	if (bRlt)
	{
		m_heathData.setDataType(TYPE_BP);
		m_heathData.setHealthData(&bpData);
	}
	return bRlt;
}
bool CParseHealthData::parsePersonInfo(Json::Value &jsonValue)
{
	pdPersonInfo personInfo;
	bool bRlt = true;
	if (jsonValue[PERSONINFO][NAME].isNull())		//姓名
	{
		std::cout << "[" << PERSONINFO << "]" << "[" << NAME << "]" << " is null" << std::endl;
		bRlt = false;
	}
	else
		*personInfo.m_name = jsonValue[PERSONINFO][NAME].asString();

	if (jsonValue[PERSONINFO][GENDER].isNull())		//性别
	{
		std::cout << "[" << PERSONINFO << "]" << "[" << GENDER << "]" << " is null" << std::endl;
		bRlt = false;
	}
	else
		*personInfo.m_gender= jsonValue[PERSONINFO][GENDER].asString();

	if (jsonValue[PERSONINFO][BIRTHDAY].isNull())		//生日
	{
		std::cout << "[" << PERSONINFO << "]" << "[" << BIRTHDAY << "]" << " is null" << std::endl;
		bRlt = false;
	}
	else
		*personInfo.m_birth = jsonValue[PERSONINFO][BIRTHDAY].asString();

	if (jsonValue[PERSONINFO][PHONE].isNull())		//电话
	{
		std::cout << "[" << PERSONINFO << "]" << "[" << PHONE << "]" << " is null" << std::endl;
		bRlt = false;
	}
	else
		*personInfo.m_phone = jsonValue[PERSONINFO][PHONE].asString();

	if (jsonValue[PERSONINFO][PERSONID].isNull())		//id
	{
		std::cout << "[" << PERSONINFO << "]" << "[" << PERSONID << "]" << " is null" << std::endl;
		bRlt = false;
	}
	else
		*personInfo.m_id = jsonValue[PERSONINFO][PERSONID].asString();

	if (bRlt)
	{
		m_heathData.setDataType(TYPE_PERSONINFO);
		m_heathData.setHealthData(&personInfo);
	}
	return bRlt;
}
bool CParseHealthData::parseECGRespond(Json::Value &jsonValue)
{
	pdECGRespond ecgRespondData;
	bool bRlt = true;
	Json::Value types = jsonValue[ECG_HTTP][REPLY_TYPES];
	Json::Value probes = jsonValue[ECG_HTTP][REPLY_PROBS];
	if (types.isNull())		//采样值
	{
		std::cout << "[" << ECG_HTTP << "]" << "[" << REPLY_TYPES << "]"
			<< " is null" << std::endl;
		bRlt = false;
	}
	if (bRlt && probes.isNull())
	{
		std::cout << "[" << ECG_HTTP << "]" << "[" << REPLY_PROBS << "]"
			<< " is null" << std::endl;
		bRlt = false;
	}
	if (bRlt)
	{
		if (jsonValue[ECG_HTTP][ECG_STATUS].isNull())
		{
			std::cout << "[" << ECG_HTTP << "]" << "[" << ECG_STATUS << "]"
				<< " is null" << std::endl;
			bRlt = false;
		}
		else
			ecgRespondData.m_iStatus = jsonValue[ECG_HTTP][ECG_STATUS].asInt();
		
		if (jsonValue[ECG_HTTP][ECG_INFO].isNull())
		{
			std::cout << "[" << ECG_HTTP << "]" << "[" << ECG_INFO << "]"
				<< " is null" << std::endl;
			bRlt = false;
		}
		else
			ecgRespondData.m_strInfo = jsonValue[ECG_HTTP][ECG_INFO].asString();
		
		for(int i = 0; i < ecgRespondData.m_vecProbs.size(); ++i)
		{
			int type = types[i].asInt();
			double probe = probes[i].asDouble();

			if (type < 4)
				ecgRespondData.m_vecProbs[type] = probe;
			else
				std::cout << "type >= 4 --> type = " << type << std::endl;
		}
	}
	if (bRlt)
	{
		m_heathData.setDataType(TYPE_ECGREPLY);
		m_heathData.setHealthData(&ecgRespondData);
	}
	return bRlt;
}


