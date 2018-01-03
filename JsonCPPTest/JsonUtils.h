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

	//json����
	/************************************************************************/
	/* ʹ��˵����Ŀǰ���������ݰ���6�н��������Լ���Ա��Ϣ�����healthData.h
		������json����֧��json���飬����json�ַ���
		
		����parseFromFile����parseFromString�ӿڽ���json����ɹ�֮��
		����getDataType�ӿڻ�ȡ�������������ͣ����getHealthData�ӿڻ�ȡ�ѽ��������ݣ�
		�����ݻ�ȡ������������ת���ɶ�Ӧ�Ľṹ�塣
		TYPE_PPG		--> pdPPG
		TYPE_ECG		--> pdECG
		TYPE_SPO2		--> pdSPO2
		TYPE_GSR		--> pdGSR
		TYPE_TEMP		--> pdTEMP
		TYPE_BP			--> pdBP
		TYPE_PERSONINFO	--> pdPersonInfo
		TYPE_ECGREPLY	--> pdECGRespond

		ʹ�����ӣ�
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
	//����json�ļ�
	int parseFromFile(const std::string & strFileName);
	//����json�ַ���
	int parseFromString(const std::string & strJsonString);
	//��ȡ�ļ����ַ������ļ������ڵȴ��󷵻ؿ��ַ���
	std::string readFileIntoString(const char * filename);
	
	/************************************************************************/
	/*��ȡ������json�ļ�����������                   
		ʹ��˵����������json���������һ��json���飬�����Ľ�����ܲ�ֹһ��
		����ֵ˵�������ؽ����������������
				lpParseRlt�������,���ݷ��ص���������ת����Ҫ�Ľṹ��*/
	/************************************************************************/
	int getHealthData(void **lpParseRlt);

	//json��װ
	int packECGData(const pdECG & ecgData, std::string & strOutResult);

protected:
	void *m_jsonParser;		//json������
	void *m_jsonPacker;		//json��װ��
};

