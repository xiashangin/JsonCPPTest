 #include "JsonUtils.h"

#include "ParseHealthData.h"
#include "PackHealthData.h"

CJsonUtils::CJsonUtils()
{
	m_jsonPacker = (void *)new CPackHealthData();
	m_jsonParser = (void *)new CParseHealthData();
}

CJsonUtils::~CJsonUtils()
{
	if (m_jsonParser != nullptr)
	{
		delete (CParseHealthData *)m_jsonParser;
		m_jsonParser = nullptr;
	}
	if (m_jsonPacker != nullptr)
	{
		delete (CPackHealthData *)m_jsonPacker;
		m_jsonPacker = nullptr;
	}
}

int CJsonUtils::parseFromFile(const std::string & strFileName)
{
	return ((CParseHealthData *)m_jsonParser)->parseFromFile(strFileName);
}

int CJsonUtils::parseFromString(const std::string & strJsonString)
{
	return ((CParseHealthData *)m_jsonParser)->parseFromString(strJsonString);
}

std::string CJsonUtils::readFileIntoString(const char * filename)
{
	return ((CParseHealthData *)m_jsonParser)->readFileIntoString(filename);
}

int CJsonUtils::getHealthData(void ** lpParseRlt)
{
	int iDataType = ((CParseHealthData *)m_jsonParser)->getDataType();
	switch (iDataType)
	{
	case TYPE_PPG:
		*lpParseRlt = ((CParseHealthData *)m_jsonParser)->getHealthData();
		break;

	case TYPE_ECG:
		*lpParseRlt = ((CParseHealthData *)m_jsonParser)->getHealthData();
		break;

	case TYPE_SPO2:
		*lpParseRlt = ((CParseHealthData *)m_jsonParser)->getHealthData();
		break;

	case TYPE_GSR:
		*lpParseRlt = ((CParseHealthData *)m_jsonParser)->getHealthData();
		break;

	case TYPE_TEMP:
		*lpParseRlt = ((CParseHealthData *)m_jsonParser)->getHealthData();
		break;

	case TYPE_BP:
		*lpParseRlt = ((CParseHealthData *)m_jsonParser)->getHealthData();
		break;

	case TYPE_PERSONINFO:
		*lpParseRlt = ((CParseHealthData *)m_jsonParser)->getHealthData();
		break;

	default:
		lpParseRlt = nullptr;
		break;
	}
	return iDataType;
}

//int CJsonUtils::getDataType()
//{
//	return ((CParseHealthData *)m_jsonParser)->getDataType();
//}
//
//void * CJsonUtils::getHealthData()
//{
//	return ((CParseHealthData *)m_jsonParser)->getHealthData();
//}


int CJsonUtils::packECGData(const pdECG & ecgData, std::string & strOutResult)
{
	return ((CPackHealthData *)m_jsonPacker)->packECGData(ecgData, strOutResult);
}
