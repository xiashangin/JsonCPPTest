// JsonCPPTest.cpp : 定义控制台应用程序的入口点。
//

#include "ParseHealthData.h"
#include "PackHealthData.h"
#include "HttpClient.h"

#include <iostream>

#include <windows.h>

void evHandler(int evType, std::string strOutResult)
{
	std::cout << "got http server reply..." << strOutResult << std::endl;
	CParseHealthData parse;
	parse.parseFromString(strOutResult);
	int iDataType;
	if ((iDataType = parse.getDataType()) == TYPE_ECGREPLY)
	{
		pdECGRespond replyData = *(pdECGRespond *)parse.getHealthData();
		if (replyData.m_iStatus == 0)
			for (int i = 0; i < replyData.m_vecProbs.size(); ++i)
				std::cout << "[" << i << "]" << "-->" << replyData.m_vecProbs[i] << std::endl;
		else
			std::cout << "http reply err info --> " << replyData.m_strInfo << std::endl;
	}
}

#include <random>
#include <functional>
int main(int argc, char **argv)
{
	std::random_device rd;
	std::default_random_engine engine(rd());
	std::uniform_int_distribution<> dis(1, 20);
	auto dice = std::bind(dis, engine);
	CHttpClient httpClient("http://192.168.31.227:8766/ecg");

	httpClient.registerEvHandler("ecg", evHandler);
	int i = 0;
	while(i < 5)
	{
		i++;
		CPackHealthData packUtil;
		std::string strECGData;
		pdECG ecgData;

		*ecgData.m_pdHR = "99";
		*ecgData.m_fv.m_freq = 100;
		for (int i = 0; i < 9000; ++i)
			(*ecgData.m_fv.m_listValue).push_back(std::make_shared<std::string>(int2str(dice())));
		*ecgData.m_timeId.m_pdTime = "2017-12-18 18:51:44:856";
		*ecgData.m_timeId.m_pdPersonId = "0000009999";

		packUtil.packECGData(ecgData, strECGData);
		std::cout << (*ecgData.m_fv.m_listValue).size();//<< strECGData << std::endl;
		httpClient.sendReq("ecg", strECGData);
	}

	CParseHealthData parseUtil;
	//int iRlt = parseUtil.parseFromFile(std::string("json/TEMP.json"));
	//int iRlt = parseUtil.parseFromString(parseUtil.readFileIntoString("json/TEMP.json"));
	//int iRlt = parseUtil.parseFromFile(std::string("json/healthData.json"));
	int iRlt = parseUtil.parseFromString(parseUtil.readFileIntoString("json/healthData.json"));
	int iDataType;
	while ((iDataType = parseUtil.getDataType()) != 0)
	{
		switch (iDataType)
		{
		case TYPE_PPG:
		{
			pdPPG ppgData = *(pdPPG *)parseUtil.getHealthData();
			std::cout << "TYPE_PPG" << std::endl;
			std::cout << "id-->" << *ppgData.m_timeId.m_pdPersonId << std::endl;
			std::cout << "time-->" << *ppgData.m_timeId.m_pdTime << std::endl;
			std::cout << "frequency-->" << *ppgData.m_fv.m_freq << std::endl;
			std::cout << "value : ";
			for (int i = 0; i < (*ppgData.m_fv.m_listValue).size(); ++i)
				std::cout << *(*ppgData.m_fv.m_listValue)[i] << "\t";
			std::cout << std::endl;
			std::cout << "HR-->" << *ppgData.m_pdHR << std::endl;
			std::cout << std::endl << std::endl << std::endl;
		}
		break;

		case TYPE_ECG:
		{
			std::cout << "TYPE_ECG" << std::endl;
			pdECG ecgData = *(pdECG *)parseUtil.getHealthData();
			std::cout << "id-->" << *ecgData.m_timeId.m_pdPersonId << std::endl;
			std::cout << "time-->" << *ecgData.m_timeId.m_pdTime << std::endl;
			std::cout << "frequency-->" << *ecgData.m_fv.m_freq << std::endl;
			std::cout << "value : ";
			for (int i = 0; i < (*ecgData.m_fv.m_listValue).size(); ++i)
				std::cout << *(*ecgData.m_fv.m_listValue)[i] << "\t";
			std::cout << std::endl;
			std::cout << "HR-->" << *ecgData.m_pdHR << std::endl;
			std::cout << std::endl << std::endl << std::endl;
		}
		break;

		case TYPE_SPO2:
		{
			std::cout << "TYPE_SPO2" << std::endl;
			pdSPO2 spo2Data = *(pdSPO2 *)parseUtil.getHealthData();
			std::cout << "id-->" << *spo2Data.m_timeId.m_pdPersonId << std::endl;
			std::cout << "time-->" << *spo2Data.m_timeId.m_pdTime << std::endl;
			std::cout << "frequency-->" << *spo2Data.m_fv.m_freq << std::endl;
			std::cout << "value : ";
			for (int i = 0; i < (*spo2Data.m_fv.m_listValue).size(); ++i)
				std::cout << *(*spo2Data.m_fv.m_listValue)[i] << "\t";
			std::cout << std::endl;
			std::cout << "HR-->" << *spo2Data.m_pdHR << std::endl;
			std::cout << "SP-->" << *spo2Data.m_pdSP << std::endl;
			std::cout << std::endl << std::endl << std::endl;
		}
		break;

		case TYPE_GSR:
		{
			std::cout << "TYPE_GSR" << std::endl;
			pdGSR gsrData = *(pdGSR *)parseUtil.getHealthData();
			std::cout << "id-->" << *gsrData.m_timeId.m_pdPersonId << std::endl;
			std::cout << "time-->" << *gsrData.m_timeId.m_pdTime << std::endl;
			std::cout << "frequency-->" << *gsrData.m_fv.m_freq << std::endl;
			for (int i = 0; i < (*gsrData.m_fv.m_listValue).size(); ++i)
				std::cout << *(*gsrData.m_fv.m_listValue)[i] << "\t";
			std::cout << std::endl;
			std::cout << std::endl << std::endl << std::endl;
		}
		break;

		case TYPE_TEMP:
		{
			std::cout << "TYPE_TEMP" << std::endl;
			pdTEMP tempData = *(pdTEMP *)parseUtil.getHealthData();
			std::cout << "id-->" << *tempData.m_timeId.m_pdPersonId << std::endl;
			std::cout << "time-->" << *tempData.m_timeId.m_pdTime << std::endl;
			std::cout << "heat-->" << *tempData.m_pdHeat << std::endl;
			std::cout << "ir-->" << *tempData.m_pdIR << std::endl;
			std::cout << std::endl << std::endl << std::endl;
		}
		break;

		case TYPE_BP:
		{
			std::cout << "TYPE_BP" << std::endl;
			pdBP bpData = *(pdBP *)parseUtil.getHealthData();
			std::cout << "id-->" << *bpData.m_timeId.m_pdPersonId << std::endl;
			std::cout << "time-->" << *bpData.m_timeId.m_pdTime << std::endl;
			std::cout << "H-->" << *bpData.m_pdH << std::endl;
			std::cout << "L-->" << *bpData.m_pdL << std::endl;
			std::cout << "HR-->" << *bpData.m_pdHR << std::endl;
			break;
		}

		default:
			std::cout << "unknown type-->" << iDataType << std::endl;
			std::cout << std::endl << std::endl << std::endl;
			break;
		}
	}
	getchar();
    return 0;
}


