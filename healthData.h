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
	PData freq;
	PDataList listValue;
	_FreqAndValue(){
		freq = std::make_shared<std::string>();
		listValue = std::make_shared<std::vector<PData> >();
	}
}freqAndValue;

typedef struct _TimeAndId {
	PData pdTime;
	PData pdPersonId;

	_TimeAndId(){
		pdTime = std::make_shared<std::string>();
		pdPersonId = std::make_shared<std::string>();
	}
}timeAndId;

//脉搏波
typedef struct _PPG {
	timeAndId timeId;

	freqAndValue fv;	//采样频率和当前采集的数据集合
	PData pdHR;

	_PPG(){
		pdHR = std::make_shared<std::string>();
	}
}pdPPG;

//心电图
typedef struct _ECG {
	timeAndId timeId;

	freqAndValue fv;	//采样频率和当前采集的数据集合
	PData pdHR;

	_ECG() {
		pdHR = std::make_shared<std::string>();
	}
}pdECG;

//血氧
typedef struct _SPO2 {
	timeAndId timeId;

	freqAndValue fv;	//采样频率和当前采集的数据集合
	PData pdHR;
	PData pdSP;

	_SPO2() {
		pdHR = std::make_shared<std::string>();
		pdSP = std::make_shared<std::string>();
	}
}pdSPO2;

//皮电
typedef struct _GSR {
	timeAndId timeId;

	freqAndValue fv;	//采样频率和当前采集的数据集合
}pdGSR;

//体温
typedef struct _TEMP {
	timeAndId timeId;

	PData pdHeat;
	PData pdIR;

	_TEMP() {
		pdHeat = std::make_shared<std::string>();
		pdIR = std::make_shared<std::string>();
	}
}pdTEMP;

//血压
typedef struct _BP {
	timeAndId timeId;

	PData pdH;
	PData pdL;
	PData pdPulse;

	_BP() {
		pdH = std::make_shared<std::string>();
		pdL = std::make_shared<std::string>();
		pdPulse = std::make_shared<std::string>();
	}
}pdBP;