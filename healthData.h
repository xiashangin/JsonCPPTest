#pragma once

#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

typedef std::shared_ptr<std::string> PData;
typedef std::shared_ptr<std::vector<PData>> PDataList;
typedef std::vector< PData >::iterator PDataListIterator;
typedef std::shared_ptr<std::vector<PDataList>> PDataListList;
typedef std::vector< PDataList >::iterator PDataListListIterator;
typedef std::shared_ptr<std::vector< PDataListList >> PDataListListList;

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


typedef struct _FreqAndValue {
	PData m_freq;
	PDataList m_listValue;
	_FreqAndValue(){
		m_freq = std::make_shared<std::string>();
		m_listValue = std::make_shared<std::vector<PData> >();
	}
}freqAndValue;

typedef struct _TimeAndId {
	PData m_pdTime;
	PData m_pdPersonId;

	_TimeAndId(){
		m_pdTime = std::make_shared<std::string>();
		m_pdPersonId = std::make_shared<std::string>();
	}
}timeAndId;

//脉搏波
typedef struct _PPG {
	timeAndId m_timeId;

	freqAndValue m_fv;	//采样频率和当前采集的数据集合
	PData m_pdHR;

	_PPG(){
		m_pdHR = std::make_shared<std::string>();
	}
}pdPPG;

//心电图
typedef struct _ECG {
	timeAndId m_timeId;

	freqAndValue m_fv;	//采样频率和当前采集的数据集合
	PData m_pdHR;

	_ECG() {
		m_pdHR = std::make_shared<std::string>();
	}
}pdECG;

//血氧
typedef struct _SPO2 {
	timeAndId m_timeId;

	freqAndValue m_fv;	//采样频率和当前采集的数据集合
	PData m_pdHR;
	PData m_pdSP;

	_SPO2() {
		m_pdHR = std::make_shared<std::string>();
		m_pdSP = std::make_shared<std::string>();
	}
}pdSPO2;

//皮电
typedef struct _GSR {
	timeAndId m_timeId;

	freqAndValue m_fv;	//采样频率和当前采集的数据集合
}pdGSR;

//体温
typedef struct _TEMP {
	timeAndId m_timeId;

	PData m_pdHeat;
	PData m_pdIR;

	_TEMP() {
		m_pdHeat = std::make_shared<std::string>();
		m_pdIR = std::make_shared<std::string>();
	}
}pdTEMP;

//血压
typedef struct _BP {
	timeAndId m_timeId;

	PData m_pdH;
	PData m_pdL;
	PData m_pdHR;

	_BP() {
		m_pdH = std::make_shared<std::string>();
		m_pdL = std::make_shared<std::string>();
		m_pdHR = std::make_shared<std::string>();
	}
}pdBP;