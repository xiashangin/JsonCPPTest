#include "DataSpeculation.h"
#include "HttpClient.h"
#include "PackHealthData.h"
#include "ParseHealthData.h"

#include <iostream>

CDataSpeculation::CDataSpeculation(std::string strIp)
{
	m_httpClient = new CHttpClient(strIp);
	
	auto my_lambda_func = [this](const int evType, const std::string & strOutResult) {
		std::cout << "got http server evType = " << evType << ", reply..." << strOutResult << std::endl;
		if(evType == HTTP_REPLY)
			this->m_httpReply.push_back(strOutResult);
	};
	((CHttpClient *)m_httpClient)->registerEvHandler(ECGSPECULATION, my_lambda_func);
}


CDataSpeculation::~CDataSpeculation()
{
	((CHttpClient *)m_httpClient)->removeEvHandler(ECGSPECULATION);
	if (m_httpClient != nullptr)
	{
		delete (CHttpClient *)m_httpClient;
		m_httpClient = nullptr;
	}
}

std::string CDataSpeculation::ecgSpeculation(const pdECG & ecgData)
{
	int iDataCnt = (ecgData.m_fv.m_listValue)->size();
	int iDataGroupCnt = iDataCnt % DATACNT;
	CPackHealthData packUtil;
	for (int i = 0; i <= iDataGroupCnt; ++i)
	{
		pdECG tmpEcgData;
		PDataListIterator iterBegin = tmpEcgData.m_fv.m_listValue->begin();
		PDataListIterator insertBegin = ecgData.m_fv.m_listValue->begin() + i * DATACNT;
		PDataListIterator insertEnd;
		if (((i + 1) * DATACNT)  > iDataCnt)
		{
			int iPaddingNum = (i + 1) * DATACNT - iDataCnt;
			insertEnd = ecgData.m_fv.m_listValue->end();
			tmpEcgData.m_fv.m_listValue->insert(iterBegin, insertBegin, insertEnd); 
			tmpEcgData.m_fv.m_listValue->insert(tmpEcgData.m_fv.m_listValue->end(), iPaddingNum,
				std::make_shared<std::string>(int2str(0)));
		}
		else
		{
			insertEnd = insertBegin + DATACNT;
			tmpEcgData.m_fv.m_listValue->insert(iterBegin, insertBegin, insertEnd);
		}

		std::string strEcgData;
		packUtil.packECGData(tmpEcgData, strEcgData);
		((CHttpClient *)m_httpClient)->sendReq(ECGSPECULATION, strEcgData);
	}
	std::string strReply;
	packUtil.packECGReply(m_httpReply, strReply);
	m_httpReply.clear();
	return strReply;
}
