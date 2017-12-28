#pragma once

#include "healthData.h"

#define ECGSPECULATION	"ECG"

class CDataSpeculation
{
public:
	CDataSpeculation(std::string strIp);
	~CDataSpeculation();

	/************************************************************************/
	/*功能说明：向ECG数据预测模块请求期预测结果                                */
	/*参数说明：ecgData-->预测的ECG数据集，数据集大小可以任意大小，受计算机内存限制，
			填充ecgData时，只关心ecgData.m_fv.m_listValue字段
			   strOutResult-->预测结果，正常是json数组；异常则是异常信息	    */
		/*返回值说明：0->成功
					HTTP_CONNFAIL->连接http服务失败
					PACK_INVALIDREPLY->http应答结果不是json格式*/
	/************************************************************************/

	int ecgSpeculation(const pdECG & ecgData, std::string &strOutResult);
protected:
	void *m_httpClient;
	std::vector<std::string> m_httpReply;
	bool m_bConnected;
	std::string m_errStr;
};

