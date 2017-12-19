#include "HttpClient.h"

#include <iostream>

bool CHttpClient::m_bExitFlag = false;
mapHandler CHttpClient::m_mapHandler;
std::string CHttpClient::m_strReqType;

CHttpClient::CHttpClient(std::string strIp)
{
	m_strIp = strIp;
	mg_mgr_init(&m_mgr, NULL);
}

CHttpClient::~CHttpClient()
{
	mg_mgr_free(&m_mgr);
}

void CHttpClient::registerEvHandler(std::string strReqType, httpEvHandler handler)
{
	if (strReqType.empty())
	{
		std::cout << "register handler failed!!! ReqType is empty!!!!" << std::endl;
		return;
	}
	mapHandlerIter iter = m_mapHandler.find(strReqType);
	if (iter == m_mapHandler.end())
	{
		std::cout << "register handler success!!! strReqType = " << strReqType << std::endl;
		m_mapHandler.insert(std::make_pair(strReqType, handler));
	}
	else
		std::cout << "register handler failed!!! strReqType = " << strReqType << " existed" << std::endl;
}

void CHttpClient::sendReq(const std::string &strReqType, const std::string & req)
{
	m_strReqType = strReqType;
	mapHandlerIter iter = m_mapHandler.find(strReqType);
	if (strReqType.length() == 0 || iter == m_mapHandler.end())
	{
		std::cout << "strReqType = " << strReqType << " is not registered..." << std::endl;
		return;
	}

	mg_connect_http(&m_mgr, ev_handler, m_strIp.c_str(), HTTPHEADER, req.c_str());

	while (!m_bExitFlag) {
		mg_mgr_poll(&m_mgr, 1000);
	}
}

void CHttpClient::ev_handler(struct mg_connection *nc, int ev, void *ev_data)
{
	struct http_message *hm = (struct http_message *) ev_data;
	mapHandlerIter iter = m_mapHandler.find(m_strReqType);
	if (iter == m_mapHandler.end())
	{
		std::cout << "strReqType = " << m_strReqType << " not found!!!" << std::endl;
		return;
	}
	httpEvHandler handler = m_mapHandler[m_strReqType];
	switch (ev) {
	case MG_EV_CONNECT:
		if (*(int *)ev_data != 0) {
			//fprintf(stderr, "connect() failed: %s\n", strerror(*(int *)ev_data));
			if (handler)
				handler(HTTP_CONNFAIL, strerror(*(int *)ev_data));
			m_bExitFlag = true;
		}
		break;
	case MG_EV_HTTP_REPLY:
		{
			nc->flags |= MG_F_CLOSE_IMMEDIATELY;
			//fwrite(hm->body.p, 1, hm->body.len, stdout);
			std::string strReply(hm->body.p, hm->body.len);
			if (handler)
				handler(HTTP_REPLY, strReply);
			m_bExitFlag = true;
		}
		break;
	case MG_EV_CLOSE:
		if (!m_bExitFlag) {
			//printf("Server closed connection\n");
			handler(HTTP_CLOSE, "Server closed the connection");
			m_bExitFlag = true;
		}
		break;
	default:
		break;
	}
}
