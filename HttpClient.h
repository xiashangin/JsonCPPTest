#pragma once

#include "http/mongoose.h"

#include <map>
#include <string>

#define HTTPHEADER "Content - Type: application / x - www - form - urlencoded\r\n"

#define HTTP_CONNFAIL		140			//连接http服务失败
#define HTTP_REPLY			141			//得到http服务的回复
#define	HTTP_CLOSE			142			//http服务关闭连接

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

