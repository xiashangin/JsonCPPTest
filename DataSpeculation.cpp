#include "DataSpeculation.h"
#include "HttpClient.h"
#include "PackHealthData.h"

#include <iostream>

CDataSpeculation::CDataSpeculation(std::string strIp)
{
	m_httpClient = new CHttpClient(strIp);
	m_bConnected = true;
	auto httpECGEvHandler = [this](const int evType, const std::string & strOutResult) {
		std::cout << "got http server evType = " << evType << ", reply..." << strOutResult << std::endl;
		if(evType == HTTP_REPLY)
		{
			this->m_httpReply.push_back(strOutResult);
			this->m_bConnected = true;
		}
		if (evType == HTTP_CONNFAIL)
		{
			//this->m_httpReply.push_back(strOutResult);
			m_errStr = strOutResult;
			this->m_bConnected = false;
		}
		if(evType == HTTP_CLOSE)
		{
			m_errStr = strOutResult;
			this->m_bConnected = false;
		}
	};
	((CHttpClient *)m_httpClient)->registerEvHandler(ECGSPECULATION, httpECGEvHandler);
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

int CDataSpeculation::ecgSpeculation(const pdECG & ecgData, std::string &strOutResult)
{
	int iDataCnt = (ecgData.m_fv.m_listValue)->size();
	int iDataGroupCnt = iDataCnt / DATACNT;
	CPackHealthData packUtil;
	for (int i = 0; i <= iDataGroupCnt; ++i)
	{
		pdECG tmpEcgData;
		PDataListIterator iterBegin = tmpEcgData.m_fv.m_listValue->begin();
		PDataListIterator insertBegin = ecgData.m_fv.m_listValue->begin() + i * DATACNT;
		PDataListIterator insertEnd;
		if (((i + 1) * DATACNT)  > iDataCnt)	//不足9000个的余下数据补0
		{
			int iPaddingNum = (i + 1) * DATACNT - iDataCnt;
			insertEnd = ecgData.m_fv.m_listValue->end();
			tmpEcgData.m_fv.m_listValue->insert(iterBegin, insertBegin, insertEnd); 
			tmpEcgData.m_fv.m_listValue->insert(tmpEcgData.m_fv.m_listValue->end(), iPaddingNum,
				std::make_shared<std::string>(int2str(0)));
		}
		else		//9000个一组
		{
			insertEnd = insertBegin + DATACNT;
			tmpEcgData.m_fv.m_listValue->insert(iterBegin, insertBegin, insertEnd);
		}

		std::string strEcgData;
		packUtil.packECGData(tmpEcgData, strEcgData);
		((CHttpClient *)m_httpClient)->sendReq(ECGSPECULATION, strEcgData);
		if (!m_bConnected)
		{
			m_httpReply.clear();
			strOutResult = m_errStr;
			return HTTP_CONNFAIL;
		}
	}

	int iRlt = packUtil.packECGReply(m_httpReply, strOutResult);
	m_httpReply.clear();
	return iRlt;
}
