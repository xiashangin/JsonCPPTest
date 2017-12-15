// JsonCPPTest.cpp : 定义控制台应用程序的入口点。
//

#include "ParseHealthData.h"

int main(int argc, char **argv)
{
	CParseHealthData parseUtil;
	
	pdPPG ppgData;
	parseUtil.parseFromFile(std::string("json/PPG.json"), TYPE_PPG, &ppgData);
	std::cout << "id-->" << *ppgData.timeId.pdPersonId << std::endl;
	std::cout << "time-->" << *ppgData.timeId.pdTime << std::endl;
	std::cout << "frequency-->" << *ppgData.fv.freq << std::endl;
	std::cout << "value : ";
	for (int i = 0; i < (*ppgData.fv.listValue).size(); ++i)
		std::cout << *(*ppgData.fv.listValue)[i] << "\t";
	std::cout << std::endl;
	std::cout << "HR-->" << *ppgData.pdHR << std::endl;
	std::cout << std::endl << std::endl << std::endl;
	parseUtil.parseFromString(parseUtil.readFileIntoString("json/PPG.json"), TYPE_PPG, &ppgData);
	std::cout << "id-->" << *ppgData.timeId.pdPersonId << std::endl;
	std::cout << "time-->" << *ppgData.timeId.pdTime << std::endl;
	std::cout << "frequency-->" << *ppgData.fv.freq << std::endl;
	std::cout << "value : ";
	for (int i = 0; i < (*ppgData.fv.listValue).size(); ++i)
		std::cout << *(*ppgData.fv.listValue)[i] << "\t";
	std::cout << std::endl;
	std::cout << "HR-->" << *ppgData.pdHR << std::endl;
	std::cout << std::endl << std::endl << std::endl;


	pdECG ecgData;
	//parseUtil.parseFromFile(std::string("json/ECG.json"), TYPE_ECG, &ecgData);
	parseUtil.parseFromString(parseUtil.readFileIntoString("json/ECG.json"), TYPE_ECG, &ecgData);
	std::cout << "id-->" << *ecgData.timeId.pdPersonId << std::endl;
	std::cout << "time-->" << *ecgData.timeId.pdTime << std::endl;
	std::cout << "frequency-->" << *ecgData.fv.freq << std::endl;
	std::cout << "value : ";
	for (int i = 0; i < (*ecgData.fv.listValue).size(); ++i)
		std::cout << *(*ecgData.fv.listValue)[i] << "\t";
	std::cout << std::endl;
	std::cout << "HR-->" << *ecgData.pdHR << std::endl;
	std::cout << std::endl << std::endl << std::endl;

	pdSPO2 spo2Data;
	//parseUtil.parseFromFile(std::string("json/SPO2.json"), TYPE_SPO2, &spo2Data);
	parseUtil.parseFromString(parseUtil.readFileIntoString("json/SPO2.json"), TYPE_SPO2, &spo2Data);
	std::cout << "id-->" << *spo2Data.timeId.pdPersonId << std::endl;
	std::cout << "time-->" << *spo2Data.timeId.pdTime << std::endl;
	std::cout << "frequency-->" << *spo2Data.fv.freq << std::endl;
	std::cout << "value : ";
	for (int i = 0; i < (*spo2Data.fv.listValue).size(); ++i)
		std::cout << *(*spo2Data.fv.listValue)[i] << "\t";
	std::cout << std::endl;
	std::cout << "HR-->" << *spo2Data.pdHR << std::endl;
	std::cout << "SP-->" << *spo2Data.pdSP << std::endl;
	std::cout << std::endl << std::endl << std::endl;

	pdGSR gsrData;
	//parseUtil.parseFromFile(std::string("json/GSR.json"), TYPE_GSR, &gsrData);
	parseUtil.parseFromString(parseUtil.readFileIntoString("json/GSR.json"), TYPE_GSR, &gsrData);
	std::cout << "id-->" << *gsrData.timeId.pdPersonId << std::endl;
	std::cout << "time-->" << *gsrData.timeId.pdTime << std::endl;
	std::cout << "frequency-->" << *gsrData.fv.freq << std::endl;
	for (int i = 0; i < (*gsrData.fv.listValue).size(); ++i)
		std::cout << *(*gsrData.fv.listValue)[i] << "\t";
	std::cout << std::endl;
	std::cout << std::endl << std::endl << std::endl;

	pdTEMP tempData;
	//parseUtil.parseFromFile(std::string("json/TEMP.json"), TYPE_TEMP, &tempData);
	parseUtil.parseFromString(parseUtil.readFileIntoString("json/TEMP.json"), TYPE_TEMP, &tempData);
	std::cout << "id-->" << *tempData.timeId.pdPersonId << std::endl;
	std::cout << "time-->" << *tempData.timeId.pdTime << std::endl;
	std::cout << "heat-->" << *tempData.pdHeat << std::endl;
	std::cout << "ir-->" << *tempData.pdIR << std::endl;
	std::cout << std::endl << std::endl << std::endl;

	pdBP bpData;
	//parseUtil.parseFromFile(std::string("json/BP.json"), TYPE_BP, &bpData);
	parseUtil.parseFromString(parseUtil.readFileIntoString("json/BP.json"), TYPE_BP, &bpData);
	std::cout << "id-->" << *bpData.timeId.pdPersonId << std::endl;
	std::cout << "time-->" << *bpData.timeId.pdTime << std::endl;
	std::cout << "H-->" << *bpData.pdH << std::endl;
	std::cout << "L-->" << *bpData.pdL << std::endl;
	std::cout << "pulse-->" << *bpData.pdPulse << std::endl;

	getchar();
    return 0;
}


