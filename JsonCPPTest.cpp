// JsonCPPTest.cpp : 定义控制台应用程序的入口点。
//

#include "ParseHealthData.h"
#include <windows.h>
int main(int argc, char **argv)
{
	CParseHealthData parseUtil;
	while(1)
	{
		//int iRlt = parseUtil.parseFromFile(std::string("json/PPG.json"));
		int iRlt = parseUtil.parseFromString(parseUtil.readFileIntoString("json/PPG.json"));
		if (iRlt == 0)
		{
			std::cout << "parse json success!!!" << std::endl;
			if (parseUtil.getDataType() == TYPE_PPG)
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
			else
				std::cout << "health data type error, type = " << parseUtil.getDataType() << std::endl;
		}
		else
			std::cout << "parse json failed!!!" << std::endl;

		//iRlt = parseUtil.parseFromFile(std::string("json/ECG.json"));
		iRlt = parseUtil.parseFromString(parseUtil.readFileIntoString("json/ECG.json"));
		if (iRlt == 0)
		{
			std::cout << "parse json success!!!" << std::endl;
			if (parseUtil.getDataType() == TYPE_ECG)
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
			else
				std::cout << "health data type error, type = " << parseUtil.getDataType() << std::endl;
		}
		else
			std::cout << "parse json failed!!!" << std::endl;

		//iRlt = parseUtil.parseFromFile(std::string("json/SPO2.json"));
		iRlt = parseUtil.parseFromString(parseUtil.readFileIntoString("json/SPO2.json"));
		if (iRlt == 0)
		{
			std::cout << "parse json success!!!" << std::endl;
			if (parseUtil.getDataType() == TYPE_SPO2)
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
			else
				std::cout << "health data type error, type = " << parseUtil.getDataType() << std::endl;
		}
		else
			std::cout << "parse json failed!!!" << std::endl;

		//iRlt = parseUtil.parseFromFile(std::string("json/GSR.json"));
		iRlt = parseUtil.parseFromString(parseUtil.readFileIntoString("json/GSR.json"));
		if (iRlt == 0)
		{
			std::cout << "parse json success!!!" << std::endl;
			if (parseUtil.getDataType() == TYPE_GSR)
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
			else
				std::cout << "health data type error, type = " << parseUtil.getDataType() << std::endl;
		}
		else
			std::cout << "parse json failed!!!" << std::endl;

		//iRlt = parseUtil.parseFromFile(std::string("json/TEMP.json"));
		iRlt = parseUtil.parseFromString(parseUtil.readFileIntoString("json/TEMP.json"));
		if (iRlt == 0)
		{
			std::cout << "parse json success!!!" << std::endl;
			if (parseUtil.getDataType() == TYPE_TEMP)
			{
				pdTEMP tempData = *(pdTEMP *)parseUtil.getHealthData();
				std::cout << "id-->" << *tempData.m_timeId.m_pdPersonId << std::endl;
				std::cout << "time-->" << *tempData.m_timeId.m_pdTime << std::endl;
				std::cout << "heat-->" << *tempData.m_pdHeat << std::endl;
				std::cout << "ir-->" << *tempData.m_pdIR << std::endl;
				std::cout << std::endl << std::endl << std::endl;
			}
			else
				std::cout << "health data type error, type = " << parseUtil.getDataType() << std::endl;
		}
		else
			std::cout << "parse json failed!!!" << std::endl;

		//iRlt = parseUtil.parseFromFile(std::string("json/BP.json"));
		iRlt = parseUtil.parseFromString(parseUtil.readFileIntoString("json/BP.json"));
		if (iRlt == 0)
		{
			std::cout << "parse json success!!!" << std::endl;
			if (parseUtil.getDataType() == TYPE_BP)
			{
				pdBP bpData = *(pdBP *)parseUtil.getHealthData();
				std::cout << "id-->" << *bpData.m_timeId.m_pdPersonId << std::endl;
				std::cout << "time-->" << *bpData.m_timeId.m_pdTime << std::endl;
				std::cout << "H-->" << *bpData.m_pdH << std::endl;
				std::cout << "L-->" << *bpData.m_pdL << std::endl;
				std::cout << "pulse-->" << *bpData.m_pdPulse << std::endl;
			}
			else
				std::cout << "health data type error, type = " << parseUtil.getDataType() << std::endl;
		}
		else
			std::cout << "parse json failed!!!" << std::endl;

		Sleep(500);
	}
    return 0;
}


