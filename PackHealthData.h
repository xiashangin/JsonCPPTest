#pragma once
#include "HealthDataBase.h"
#include <json/json.h>

#define PACK_OK				0

class CPackHealthData
{
public:
	CPackHealthData();
	~CPackHealthData();

	int packECGData(const pdECG & ecgData, std::string & strOutResult);

private:
	int packJson(Json::Value &jsonValue, void *lpInHealthData, int iType);
	bool packFreqVal(Json::Value &jsonValue, void *lpInHealthData);
	bool packTimeId(Json::Value &jsonValue, void *lpInHealthData);

	CHealthDataBase m_healthData;
};
