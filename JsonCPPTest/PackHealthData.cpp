#include "PackHealthData.h"
#include <iostream>
#include <sstream>

CPackHealthData::CPackHealthData()
{
}


CPackHealthData::~CPackHealthData()
{
}

int CPackHealthData::packECGData(const pdECG & ecgData, std::string & strOutResult)
{
	if (!strOutResult.empty())
		strOutResult.clear();
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

int CPackHealthData::packECGReply(const std::vector<std::string> & ecgReply, std::string & strOutResult)
{
	if (!strOutResult.empty())
		strOutResult.clear();

	Json::Value root;
	Json::StreamWriterBuilder builder;
	builder.settings_["indentation"] = "";
	std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());

	for (int i = 0; i < ecgReply.size(); ++i)
	{
		Json::CharReaderBuilder builder;
		Json::CharReader* reader(builder.newCharReader());
		Json::Value jsonRoot;
		JSONCPP_STRING errs;
		const char* lpStrJson = ecgReply[i].c_str();
		bool is_ok = reader->parse(lpStrJson, lpStrJson + strlen(lpStrJson), &jsonRoot, &errs);
		if (!is_ok || errs.size() > 0) //从ifs中读取数据到jsonRoot
		{
			std::cout << "parse Json file failed!!! errstr = " << errs << std::endl;
			strOutResult = "parse Json file failed!!! errstr = " + errs + "http reply = " + lpStrJson;
			return PACK_INVALIDREPLY;
		}
		if (jsonRoot[ECG_HTTP][REPLY_TYPES].isNull())		
		{
			std::cout << "[" << ECG_HTTP << "]" << "[" << REPLY_TYPES << "]" << " is null" << std::endl;
			return PACK_INVALIDREPLY;
		}
		if (jsonRoot[ECG_HTTP][REPLY_PROBS].isNull())
		{
			std::cout << "[" << ECG_HTTP << "]" << "[" << REPLY_PROBS << "]" << " is null" << std::endl;
			return PACK_INVALIDREPLY;
		}
		if (jsonRoot[ECG_HTTP][ECG_STATUS].isNull())
		{
			std::cout << "[" << ECG_HTTP << "]" << "[" << ECG_STATUS << "]" << " is null" << std::endl;
			return PACK_INVALIDREPLY;
		}

		Json::Value types = jsonRoot[ECG_HTTP][REPLY_TYPES];
		Json::Value probes = jsonRoot[ECG_HTTP][REPLY_PROBS];
		std::string strTypes, strProbes;
		for (int i = 0; i < types.size(); ++i)
		{
			strTypes.append(types[i].asString());
			strTypes.append(",");
		}
		for (int i = 0; i < probes.size(); ++i)
		{
			strProbes.append(probes[i].asString());
			strProbes.append(",");
		}
		strTypes = strTypes.substr(0, strTypes.length() - 1);
		strProbes = strProbes.substr(0, strProbes.length() - 1);
		std::string status = jsonRoot[ECG_HTTP][ECG_STATUS].asString();
		//std::string info = jsonRoot[ECG_HTTP][ECG_INFO].asString();
		
		Json::Value array;
		array["index"] = int2str(i + 1);
		array["total"] = int2str(DATACNT);
		array["replay"] = status;
		array["types"] = strTypes;
		array["probs"] = strProbes;
		root.append(array);
	}
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
