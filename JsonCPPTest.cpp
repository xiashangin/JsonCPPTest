// JsonCPPTest.cpp : 定义控制台应用程序的入口点。
//

#include "ParseHealthData.h"
#include "PackHealthData.h"
#include "HttpClient.h"

#include <iostream>

#include <windows.h>
static int s_exit_flag = 0;

static void ev_handler(struct mg_connection *nc, int ev, void *ev_data) {
	struct http_message *hm = (struct http_message *) ev_data;

	switch (ev) {
	case MG_EV_CONNECT:
		if (*(int *)ev_data != 0) {
			fprintf(stderr, "connect() failed: %s\n", strerror(*(int *)ev_data));
			s_exit_flag = 1;
		}
		break;
	case MG_EV_HTTP_REPLY:
		nc->flags |= MG_F_CLOSE_IMMEDIATELY;
		fwrite(hm->body.p, 1, hm->body.len, stdout);
		s_exit_flag = 1;
		break;
	case MG_EV_CLOSE:
		if (s_exit_flag == 0) {
			printf("Server closed connection\n");
			s_exit_flag = 1;
		}
		break;
	default:
		break;
	}
}

void evHandler(int evType, std::string strOutResult)
{
	std::cout << "got http server reply..." << strOutResult << std::endl;
}

#include <random>
#include <functional>
int main(int argc, char **argv)
{
	std::random_device rd;
	std::default_random_engine engine(rd());
	std::uniform_int_distribution<> dis(1, 20);
	auto dice = std::bind(dis, engine);

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

	//struct mg_mgr mgr;
	//mg_mgr_init(&mgr, NULL);
	//std::string strIp = "http://192.168.31.227:8766/ecg";
	//mg_connect_http(&mgr, ev_handler, strIp.c_str(), "Content - Type: application / x - www - form - urlencoded\r\n", strECGData.c_str());

	//while (s_exit_flag == 0) {
	//	mg_mgr_poll(&mgr, 1000);
	//}
	//mg_mgr_free(&mgr);

	CHttpClient httpClient("http://192.168.31.227:8766/ecg");
	httpClient.registerEvHandler("ecg", evHandler);
	httpClient.sendReq("ecg", strECGData);

	CParseHealthData parseUtil;
	int iRlt = parseUtil.parseFromFile(std::string("json/healthData.json"));
	int iDataType;
	while ((iDataType = parseUtil.getDataType()) != 0)
	{
		switch(iDataType)
		{
		case TYPE_PPG:
		{
			pdPPG ppgData = *(pdPPG *)parseUtil.getHealthData();
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
			break;
		}
	}
	//while(1)
	//{
	//	//int iRlt = parseUtil.parseFromFile(std::string("json/PPG.json"));
	//	int iRlt = parseUtil.parseFromString(parseUtil.readFileIntoString("json/PPG.json"));
	//	if (iRlt == 0)
	//	{
	//		std::cout << "parse json success!!!" << std::endl;
	//		if (parseUtil.getDataType() == TYPE_PPG)
	//		{
	//			pdPPG ppgData = *(pdPPG *)parseUtil.getHealthData();
	//			std::cout << "id-->" << *ppgData.m_timeId.m_pdPersonId << std::endl;
	//			std::cout << "time-->" << *ppgData.m_timeId.m_pdTime << std::endl;
	//			std::cout << "frequency-->" << *ppgData.m_fv.m_freq << std::endl;
	//			std::cout << "value : ";
	//			for (int i = 0; i < (*ppgData.m_fv.m_listValue).size(); ++i)
	//				std::cout << *(*ppgData.m_fv.m_listValue)[i] << "\t";
	//			std::cout << std::endl;
	//			std::cout << "HR-->" << *ppgData.m_pdHR << std::endl;
	//			std::cout << std::endl << std::endl << std::endl;
	//		}
	//		else
	//			std::cout << "health data type error, type = " << parseUtil.getDataType() << std::endl;
	//	}
	//	else
	//		std::cout << "parse json failed!!!" << std::endl;

	//	//iRlt = parseUtil.parseFromFile(std::string("json/ECG.json"));
	//	iRlt = parseUtil.parseFromString(parseUtil.readFileIntoString("json/ECG.json"));
	//	if (iRlt == 0)
	//	{
	//		std::cout << "parse json success!!!" << std::endl;
	//		if (parseUtil.getDataType() == TYPE_ECG)
	//		{
	//			pdECG ecgData = *(pdECG *)parseUtil.getHealthData();
	//			std::cout << "id-->" << *ecgData.m_timeId.m_pdPersonId << std::endl;
	//			std::cout << "time-->" << *ecgData.m_timeId.m_pdTime << std::endl;
	//			std::cout << "frequency-->" << *ecgData.m_fv.m_freq << std::endl;
	//			std::cout << "value : ";
	//			for (int i = 0; i < (*ecgData.m_fv.m_listValue).size(); ++i)
	//				std::cout << *(*ecgData.m_fv.m_listValue)[i] << "\t";
	//			std::cout << std::endl;
	//			std::cout << "HR-->" << *ecgData.m_pdHR << std::endl;
	//			std::cout << std::endl << std::endl << std::endl;
	//		}
	//		else
	//			std::cout << "health data type error, type = " << parseUtil.getDataType() << std::endl;
	//	}
	//	else
	//		std::cout << "parse json failed!!!" << std::endl;
	//		

	//	//iRlt = parseUtil.parseFromFile(std::string("json/SPO2.json"));
	//	iRlt = parseUtil.parseFromString(parseUtil.readFileIntoString("json/SPO2.json"));
	//	if (iRlt == 0)
	//	{
	//		std::cout << "parse json success!!!" << std::endl;
	//		if (parseUtil.getDataType() == TYPE_SPO2)
	//		{
	//			pdSPO2 spo2Data = *(pdSPO2 *)parseUtil.getHealthData();
	//			std::cout << "id-->" << *spo2Data.m_timeId.m_pdPersonId << std::endl;
	//			std::cout << "time-->" << *spo2Data.m_timeId.m_pdTime << std::endl;
	//			std::cout << "frequency-->" << *spo2Data.m_fv.m_freq << std::endl;
	//			std::cout << "value : ";
	//			for (int i = 0; i < (*spo2Data.m_fv.m_listValue).size(); ++i)
	//				std::cout << *(*spo2Data.m_fv.m_listValue)[i] << "\t";
	//			std::cout << std::endl;
	//			std::cout << "HR-->" << *spo2Data.m_pdHR << std::endl;
	//			std::cout << "SP-->" << *spo2Data.m_pdSP << std::endl;
	//			std::cout << std::endl << std::endl << std::endl;
	//		}
	//		else
	//			std::cout << "health data type error, type = " << parseUtil.getDataType() << std::endl;
	//	}
	//	else
	//		std::cout << "parse json failed!!!" << std::endl;

	//	//iRlt = parseUtil.parseFromFile(std::string("json/GSR.json"));
	//	iRlt = parseUtil.parseFromString(parseUtil.readFileIntoString("json/GSR.json"));
	//	if (iRlt == 0)
	//	{
	//		std::cout << "parse json success!!!" << std::endl;
	//		if (parseUtil.getDataType() == TYPE_GSR)
	//		{
	//			pdGSR gsrData = *(pdGSR *)parseUtil.getHealthData();
	//			std::cout << "id-->" << *gsrData.m_timeId.m_pdPersonId << std::endl;
	//			std::cout << "time-->" << *gsrData.m_timeId.m_pdTime << std::endl;
	//			std::cout << "frequency-->" << *gsrData.m_fv.m_freq << std::endl;
	//			for (int i = 0; i < (*gsrData.m_fv.m_listValue).size(); ++i)
	//				std::cout << *(*gsrData.m_fv.m_listValue)[i] << "\t";
	//			std::cout << std::endl;
	//			std::cout << std::endl << std::endl << std::endl;
	//		}
	//		else
	//			std::cout << "health data type error, type = " << parseUtil.getDataType() << std::endl;
	//	}
	//	else
	//		std::cout << "parse json failed!!!" << std::endl;

	//	//iRlt = parseUtil.parseFromFile(std::string("json/TEMP.json"));
	//	iRlt = parseUtil.parseFromString(parseUtil.readFileIntoString("json/TEMP.json"));
	//	if (iRlt == 0)
	//	{
	//		std::cout << "parse json success!!!" << std::endl;
	//		if (parseUtil.getDataType() == TYPE_TEMP)
	//		{
	//			pdTEMP tempData = *(pdTEMP *)parseUtil.getHealthData();
	//			std::cout << "id-->" << *tempData.m_timeId.m_pdPersonId << std::endl;
	//			std::cout << "time-->" << *tempData.m_timeId.m_pdTime << std::endl;
	//			std::cout << "heat-->" << *tempData.m_pdHeat << std::endl;
	//			std::cout << "ir-->" << *tempData.m_pdIR << std::endl;
	//			std::cout << std::endl << std::endl << std::endl;
	//		}
	//		else
	//			std::cout << "health data type error, type = " << parseUtil.getDataType() << std::endl;
	//	}
	//	else
	//		std::cout << "parse json failed!!!" << std::endl;

	//	//iRlt = parseUtil.parseFromFile(std::string("json/BP.json"));
	//	iRlt = parseUtil.parseFromString(parseUtil.readFileIntoString("json/BP.json"));
	//	if (iRlt == 0)
	//	{
	//		std::cout << "parse json success!!!" << std::endl;
	//		if (parseUtil.getDataType() == TYPE_BP)
	//		{
	//			pdBP bpData = *(pdBP *)parseUtil.getHealthData();
	//			std::cout << "id-->" << *bpData.m_timeId.m_pdPersonId << std::endl;
	//			std::cout << "time-->" << *bpData.m_timeId.m_pdTime << std::endl;
	//			std::cout << "H-->" << *bpData.m_pdH << std::endl;
	//			std::cout << "L-->" << *bpData.m_pdL << std::endl;
	//			std::cout << "pulse-->" << *bpData.m_pdPulse << std::endl;
	//		}
	//		else
	//			std::cout << "health data type error, type = " << parseUtil.getDataType() << std::endl;
	//	}
	//	else
	//		std::cout << "parse json failed!!!" << std::endl;

	//	Sleep(500);
	//}
	getchar();
    return 0;
}


