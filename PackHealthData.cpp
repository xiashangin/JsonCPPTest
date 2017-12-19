#include "PackHealthData.h"
#include <sstream>


CPackHealthData::CPackHealthData()
{
}


CPackHealthData::~CPackHealthData()
{
}

int CPackHealthData::packECGData(const pdECG & ecgData, std::string & strOutResult)
{
	Json::Value root;
	Json::StreamWriterBuilder builder;
	builder.settings_["indentation"] = "";
	std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());

	root[ECG_HTTP][ECG_LENGTH] = (*ecgData.m_fv.m_listValue).size();

	Json::Value array; 
	for (int i = 0; i < (*ecgData.m_fv.m_listValue).size(); ++i)
		array.append(*(*ecgData.m_fv.m_listValue)[i]);
	root[ECG_HTTP][ECG_VALUES] = array;

	//root["ECG"]["HR"] = *ecgData.m_pdHR;
	std::stringstream ss;
	writer->write(root, &ss);
	strOutResult = ss.str();
	return PACK_OK;
}


bool CPackHealthData::packTimeId(Json::Value &jsonValue, void *lpInHealthData)
{
	bool bRlt = true;

	jsonValue["t"] = "2017-12-11 21:46:43:656";
	jsonValue["id"] = "0000009999";
	return bRlt;
}
