#pragma once

#include "http/mongoose.h"

#include <functional>
#include <map>
#include <string>

#define HTTPHEADER "Content - Type: application / x - www - form - urlencoded\r\n"

#define HTTP_CONNFAIL		140			//连接http服务失败
#define HTTP_REPLY			141			//得到http服务的回复
#define	HTTP_CLOSE			142			//http服务关闭连接

//http请求回调函数
/************************************************************************/
/* 参数说明：
	evType：请求结果，HTTP_CONNFAIL->连接http服务失败
					HTTP_REPLY->http服务应答
					HTTP_CLOSE->http服务关闭此连接
	strOutResult：http请求的处理结果或者相关错误信息
					HTTP_CONNFAIL->连接失败的原因
					HTTP_REPLY->http应答结果
					HTTP_CLOSE->http服务关闭连接的原因*/
/************************************************************************/
typedef std::function<void(const int evType, const std::string & strOutResult)> httpEvHandler;
typedef std::map<std::string, httpEvHandler> mapHandler;
typedef std::map<std::string, httpEvHandler>::iterator mapHandlerIter;
class CHttpClient
{
public:
	CHttpClient(std::string strIp);
	~CHttpClient();

	void registerEvHandler(std::string strReqType, httpEvHandler handler);
	void sendReq(const std::string &strReqType, const std::string & req);
	void removeEvHandler(std::string strReqType);
private:
	static void ev_handler(struct mg_connection *nc, int ev, void *ev_data);
	static mapHandler m_mapHandler;
	std::string m_strIp;
	static std::string m_strReqType;
	static bool m_bExitFlag;
	struct mg_mgr m_mgr;
};

