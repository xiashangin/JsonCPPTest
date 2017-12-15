#pragma once
#include "healthData.h"
#include <json/json.h>

#define TYPE_PPG	150
#define TYPE_ECG	151
#define TYPE_SPO2	152
#define TYPE_GSR	153
#define TYPE_TEMP	154
#define TYPE_BP		155

class CParseHealthData
{
public:
	CParseHealthData();
	~CParseHealthData();

	//解析json文件
	bool parseFromFile(const std::string & strFileName, int iDataType, void *lpOutResult);
	//解析json字符串
	bool parseFromString(const std::string & strJsonString, int iDataType, void *lpOutResult);
	//读取文件到字符串，文件不存在等错误返回空字符串。
	std::string readFileIntoString(const char * filename);
	
private:
	bool parseJson(Json::Value & jsonRoot, int iDataType, void *lpOutResult);
	bool openFile(const char * lpStrFileName);
	bool getFreqVal(Json::Value &jsonValue, freqAndValue & fv, const char * strRoot);
	bool getTimeId(Json::Value &jsonValue, timeAndId & timeId);
	bool parsePPG(Json::Value &jsonValue, pdPPG & ppgData);
	bool parseECG(Json::Value &jsonValue, pdECG & ecgData);
	bool parseSPO2(Json::Value &jsonValue, pdSPO2 & spo2Data);
	bool parseGSR(Json::Value &jsonValue, pdGSR & gsrData);
	bool parseTEMP(Json::Value &jsonValue, pdTEMP & tempData);
	bool parseBP(Json::Value &jsonValue, pdBP & bpData);

	std::string int2str(const int &int_temp);
};

