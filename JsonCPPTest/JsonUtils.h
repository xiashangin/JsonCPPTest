#pragma once

#include "healthData.h"

#define PARSE_OK				0
#define PARSE_FILENOTEXIST		170
#define PARSE_INVALIDJSON		171
#define PARSE_UNKNOWNERR		172
#define PARSE_INVALIDTYPE		173
#define PARSE_KEYNOTEXIST		174

#define TYPE_UNKNOWN	149
#define TYPE_PPG		150
#define TYPE_ECG		151
#define TYPE_SPO2		152
#define TYPE_GSR		153
#define TYPE_TEMP		154
#define TYPE_BP			155
#define TYPE_PERSONINFO	160
#define TYPE_ECGREPLY	165

class CJsonUtils
{
public:
	CJsonUtils();
	~CJsonUtils();

	//json解析
	/************************************************************************/
	/* 使用说明：目前解析的数据包括6中健康数据以及人员信息，详见healthData.h
		解析的json对象支持json数组，或者json字符串
		
		调用parseFromFile或者parseFromString接口解析json对象成功之后，
		调用getDataType接口获取解析的数据类型，最后getHealthData接口获取已解析的数据，
		最后根据获取到的数据类型转换成对应的结构体。
		TYPE_PPG		--> pdPPG
		TYPE_ECG		--> pdECG
		TYPE_SPO2		--> pdSPO2
		TYPE_GSR		--> pdGSR
		TYPE_TEMP		--> pdTEMP
		TYPE_BP			--> pdBP
		TYPE_PERSONINFO	--> pdPersonInfo
		TYPE_ECGREPLY	--> pdECGRespond

		使用例子：
		CJsonUtils parseUtil;
		int iRlt = parseUtil.parseFromString(parseUtil.readFileIntoString("json/j_id.json"));
		int iDataType;
		while ((iDataType = parseUtil.getDataType()) != 0)
		{
			switch (iDataType)
			{
			case TYPE_PPG:
			{
				pdPPG ppgData = *(pdPPG *)parseUtil.getHealthData();
				//process ppgData...
			}
			break;

			case TYPE_ECG:
			{
				pdECG ecgData = *(pdECG *)parseUtil.getHealthData();
				//process ecgData...
			}
			break;

			case TYPE_SPO2:
			{
				pdSPO2 spo2Data = *(pdSPO2 *)parseUtil.getHealthData();
				//process spo2Data...
			}
			break;

			case TYPE_GSR:
			{
				pdGSR gsrData = *(pdGSR *)parseUtil.getHealthData();
				//process gsrData...
			}
			break;

			case TYPE_TEMP:
			{
				pdTEMP tempData = *(pdTEMP *)parseUtil.getHealthData();
				//process tempData...
			}
			break;

			case TYPE_BP:
			{
				pdBP bpData = *(pdBP *)parseUtil.getHealthData();
				//process bpData...
			}
			break;

			case TYPE_PERSONINFO:
			{
				pdPersonInfo personInfo = *(pdPersonInfo *)parseUtil.getHealthData();
				//process personInfo...
			}
			break;

			default:
				std::cout << "unknown type-->" << iDataType << std::endl;
			break;
			}
		}
		*/
	/************************************************************************/
	//解析json文件
	int parseFromFile(const std::string & strFileName);
	//解析json字符串
	int parseFromString(const std::string & strJsonString);
	//读取文件到字符串，文件不存在等错误返回空字符串
	std::string readFileIntoString(const char * filename);
	
	/************************************************************************/
	/*获取解析的json文件的数据类型                   
		使用说明：解析的json对象可能是一个json数组，解析的结果可能不止一个
		返回值说明：返回解析结果的数据类型
				lpParseRlt解析结果,根据返回的数据类型转成需要的结构体*/
	/************************************************************************/
	int getHealthData(void **lpParseRlt);

	//json封装
	int packECGData(const pdECG & ecgData, std::string & strOutResult);

protected:
	void *m_jsonParser;		//json解析类
	void *m_jsonPacker;		//json封装类
};

