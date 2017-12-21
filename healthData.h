#pragma once

#include <memory>
#include <string>
#include <vector>

typedef std::shared_ptr<std::string> PData;
typedef std::shared_ptr<std::vector<PData>> PDataList;
typedef std::vector< PData >::iterator PDataListIterator;
typedef std::shared_ptr<std::vector<PDataList>> PDataListList;
typedef std::vector< PDataList >::iterator PDataListListIterator;
typedef std::shared_ptr<std::vector< PDataListList >> PDataListListList;

//6�н�������
#define PPG		"PPG"
#define ECG		"ECG"
#define SPO2	"SPO2"
#define GSR		"GSR"
#define TEMP	"TEMP"
#define BP		"BP"
#define HR		"HR"
#define SP		"SP"
#define HEAT	"HEAT"
#define IR		"IR"
#define BP_H	"H"
#define BP_L	"L"
#define PULSE	"PULSE"

#define COLLECTFREQ		"f"
#define COLLECTVAL		"v"

#define COLLECTTIME		"t"
#define PERSONID		"id"
#define EXAMNUM			"num"

//�û���Ϣ
#define PERSONINFO		"PersonInfo"
#define NAME			"name"
#define GENDER			"sex"
#define BIRTHDAY		"birth"
#define PHONE			"phone"
#define PERSON_ID		"id"

typedef struct _PersonInfo {
	PData m_id;
	PData m_name;
	PData m_gender;
	PData m_phone;
	PData m_birth;

	_PersonInfo() {
		m_id	= std::make_shared<std::string>();
		m_name	= std::make_shared<std::string>();
		m_gender= std::make_shared<std::string>();
		m_phone	= std::make_shared<std::string>();
		m_birth	= std::make_shared<std::string>();
	}
}pdPersonInfo;

typedef struct _FreqAndValue {
	PData m_freq;
	PDataList m_listValue;
	_FreqAndValue(){
		m_freq = std::make_shared<std::string>();
		m_listValue = std::make_shared<std::vector<PData> >();
	}
}freqAndValue;

typedef struct _BaseData {
	PData m_pdTime;
	PData m_pdPersonId;
	PData m_pdNum;

	_BaseData(){
		m_pdTime = std::make_shared<std::string>();
		m_pdPersonId = std::make_shared<std::string>();
		m_pdNum = std::make_shared<std::string>();
	}
}baseData;

//������
typedef struct _PPG {
	baseData m_timeId;

	freqAndValue m_fv;	//����Ƶ�ʺ͵�ǰ�ɼ������ݼ���
	PData m_pdHR;

	_PPG(){
		m_pdHR = std::make_shared<std::string>();
	}
}pdPPG;

//�ĵ�ͼ
typedef struct _ECG {
	baseData m_timeId;

	freqAndValue m_fv;	//����Ƶ�ʺ͵�ǰ�ɼ������ݼ���
	PData m_pdHR;

	_ECG() {
		m_pdHR = std::make_shared<std::string>();
	}
}pdECG;

//Ѫ��
typedef struct _SPO2 {
	baseData m_timeId;

	freqAndValue m_fv;	//����Ƶ�ʺ͵�ǰ�ɼ������ݼ���
	PData m_pdHR;
	PData m_pdSP;

	_SPO2() {
		m_pdHR = std::make_shared<std::string>();
		m_pdSP = std::make_shared<std::string>();
	}
}pdSPO2;

//Ƥ��
typedef struct _GSR {
	baseData m_timeId;

	freqAndValue m_fv;	//����Ƶ�ʺ͵�ǰ�ɼ������ݼ���
}pdGSR;

//����
typedef struct _TEMP {
	baseData m_timeId;

	PData m_pdHeat;
	PData m_pdIR;

	_TEMP() {
		m_pdHeat = std::make_shared<std::string>();
		m_pdIR = std::make_shared<std::string>();
	}
}pdTEMP;

//Ѫѹ
typedef struct _BP {
	baseData m_timeId;

	PData m_pdH;
	PData m_pdL;
	PData m_pdHR;

	_BP() {
		m_pdH = std::make_shared<std::string>();
		m_pdL = std::make_shared<std::string>();
		m_pdHR = std::make_shared<std::string>();
	}
}pdBP;


//ecgԤ��ģ�������
#define ECG_HTTP		"ecg"
#define REPLY_TYPES		"types"
#define REPLY_PROBS		"probs"
#define ECG_LENGTH		"length"
#define ECG_VALUES		"values"
#define ECG_STATUS		"state"
#define ECG_INFO		"info"

#define TYPES_NORMAL		0		//����
#define TYPES_SICK			1		//�ز�
#define TYPES_OTHER			2		//����
#define TYPES_NOISE			3		//����
typedef struct _ECGRespond {
	std::vector<double> m_vecProbs;
	int m_iStatus;
	std::string m_strInfo;

	_ECGRespond(){
		m_vecProbs = std::vector<double>(4, 0);
	}
}pdECGRespond;