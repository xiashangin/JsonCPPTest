#pragma once

#include "http/mongoose.h"

#include <map>
#include <string>

#define HTTPHEADER "Content - Type: application / x - www - form - urlencoded\r\n"

#define HTTP_CONNFAIL		140			//����http����ʧ��
#define HTTP_REPLY			141			//�õ�http����Ļظ�
#define	HTTP_CLOSE			142			//http����ر�����

typedef void(*httpEvHandler)(int evType, std::string strOutResult);
typedef std::map<std::string, httpEvHandler> mapHandler;
typedef std::map<std::string, httpEvHandler>::iterator mapHandlerIter;
class CHttpClient
{
public:
	CHttpClient(std::string strIp);
	~CHttpClient();

	void registerEvHandler(std::string strReqType, httpEvHandler handler);
	void sendReq(const std::string &strReqType, const std::string & req);

private:
	static void ev_handler(struct mg_connection *nc, int ev, void *ev_data);
	static mapHandler m_mapHandler;
	std::string m_strIp;
	static std::string m_strReqType;
	static bool m_bExitFlag;
	struct mg_mgr m_mgr;
};

