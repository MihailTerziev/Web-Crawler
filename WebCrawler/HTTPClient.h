#pragma once

#include <string>
#include <ws2tcpip.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

#include "HTTPRequestMethodsEnum.h"
#include "URLParser.h"
#include "DNS.h"


class HTTPClient
{
	// Constants
	// ----------------


	// Constructor / Destructor
	// ----------------
public:
	HTTPClient(const std::string& strURL);
	virtual ~HTTPClient();


	// Overrides
	// ----------------


	// Methods
	// ----------------
private:
	bool InitClient();
	void Cleanup();

	bool CreateSocket();
	bool ShutdownSocket();

	std::string CreateRequest(const HTTPRequestMethods& eHTTPRequestMethod);

public:
	bool ConnectToServer();
	bool DownloadDocument();
	bool CloseConnection();

	bool Send(const HTTPRequestMethods& eHTTPRequestMethod);
	bool Receive(std::string& strBuffer);

	void SetURL(const std::string& strURL, bool bParse = true);
	const std::string GetBuffer() const;


	// Members
	// ----------------
private:
	bool m_bIsWSAStarted;
	URLParser m_oURLParser;
	DNS m_oDNS;
	SOCKET m_recSocket;
	std::string m_strBuffer;
};