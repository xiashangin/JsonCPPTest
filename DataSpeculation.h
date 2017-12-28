#pragma once

#include "healthData.h"

#define ECGSPECULATION	"ECG"
#define DATACNT			9000

class CDataSpeculation
{
public:
	CDataSpeculation(std::string strIp);
	~CDataSpeculation();

	std::string ecgSpeculation(const pdECG & ecgData);
protected:
	void *m_httpClient;
	std::vector<std::string> m_httpReply;
};

