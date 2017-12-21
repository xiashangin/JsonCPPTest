#pragma once
#include "HealthDataBase.h"
#include <json/json.h>

#define PARSE_OK				0
#define PARSE_FILENOTEXIST		170
#define PARSE_INVALIDJSON		171
#define PARSE_UNKNOWNERR		172
#define PARSE_INVALIDTYPE		173
#define PARSE_KEYNOTEXIST		174

class CParseHealthData
{
public:
	CParseHealthData();
	~CParseHealthData();

	//����json�ļ�
	int parseFromFile(const std::string & strFileName);

	//����json�ַ���
	int parseFromString(const std::string & strJsonString);

	//��ȡ�ļ����ַ������ļ������ڵȴ��󷵻ؿ��ַ���
	std::string readFileIntoString(const char * filename);

	//��ȡ������json�ļ�����������
	int getDataType();
	//��ȡ�������
	void *getHealthData();
	
private:
	bool parseDataGroup(Json::Value & jsonRoot);
	bool parseJson(Json::Value & jsonRoot);
	bool openFile(const char * lpStrFileName);
	bool getFreqVal(Json::Value &jsonValue, freqAndValue & fv, const char * strRoot);
	bool getBaseData(Json::Value &jsonValue, baseData & baseData);
	bool parsePPG(Json::Value &jsonValue);
	bool parseECG(Json::Value &jsonValue);
	bool parseSPO2(Json::Value &jsonValue);
	bool parseGSR(Json::Value &jsonValue);
	bool parseTEMP(Json::Value &jsonValue);
	bool parseBP(Json::Value &jsonValue);
	bool parsePersonInfo(Json::Value &jsonValue);
	bool parseECGRespond(Json::Value &jsonValue);
	CHealthDataBase m_heathData;
};

