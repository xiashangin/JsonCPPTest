#pragma once

#include "http/mongoose.h"

#include <functional>
#include <map>
#include <string>

#define HTTPHEADER "Content - Type: application / x - www - form - urlencoded\r\n"

#define HTTP_CONNFAIL		140			//����http����ʧ��
#define HTTP_REPLY			141			//�õ�http����Ļظ�
#define	HTTP_CLOSE			142			//http����ر�����

//http����ص�����
/************************************************************************/
/* ����˵����
	evType����������HTTP_CONNFAIL->����http����ʧ��
					HTTP_REPLY->http����Ӧ��
					HTTP_CLOSE->http����رմ�����
	strOutResult��http����Ĵ�����������ش�����Ϣ
					HTTP_CONNFAIL->����ʧ�ܵ�ԭ��
					HTTP_REPLY->httpӦ����
					HTTP_CLOSE->http����ر����ӵ�ԭ��*/
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

