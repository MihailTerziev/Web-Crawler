#include <iostream>

#include "HTTPClient.h"
#include "URLParser.h"


#define WINSOCK2_VERSION			2
#define RECEIVING_BUFFER_SIZE		512
#define DEFAULT_PORT				80

#define HTTP_REQUEST_METHOD_GET		"GET "
#define HTTP_REQUEST_METHOD_HEAD	"HEAD "
#define HTTP_REQUEST_METHOD_POST	"POST "
#define HTTP_REQUEST_METHOD_PUT 	"PUT "
#define HTTP_REQUEST_METHOD_DELETE	"DELETE "
#define HTTP_REQUEST_METHOD_PATCH	"PATCH "
#define HTTP_REQUEST_METHOD_OPTIONS	"OPTIONS "
#define HTTP_REQUEST_METHOD_CONNECT	"CONNECT "
#define HTTP_REQUEST_METHOD_TRACE	"TRACE "

#define HTTP_VERSION				" HTTP/1.1\r\n"
#define HTTP_HOST					"Host: "
#define HTTP_CONNECTION_CLOSED		"Connection: close\r\n\r\n"


HTTPClient::HTTPClient(const std::string& strURL)
	: m_oURLParser(strURL), m_recSocket(INVALID_SOCKET), m_bIsWSAStarted(false)
{
}

HTTPClient::~HTTPClient()
{
}

bool HTTPClient::InitClient()
{
	const WORD wRequestedVersion = MAKEWORD(WINSOCK_VERSION, WINSOCK_VERSION);
	WSADATA recWSAData;

	const int nResult = WSAStartup(wRequestedVersion, &recWSAData);

	if (nResult != ZERO ||
		LOBYTE(recWSAData.wVersion) != WINSOCK2_VERSION ||
		HIBYTE(recWSAData.wVersion) != WINSOCK2_VERSION)
	{
		std::cerr << "CHTTPClient::InitClient(): Winsock dll failed!" << std::endl;
		return false;
	}

	m_bIsWSAStarted = true;
	m_oURLParser.Parse();

	return true;
}

void HTTPClient::Cleanup()
{
	WSACleanup();
	m_bIsWSAStarted = false;
}

bool HTTPClient::CreateSocket()
{
	m_recSocket = socket(AF_INET, SOCK_STREAM, ZERO);

	if (m_recSocket == INVALID_SOCKET)
	{
		std::cerr << "CHTTPClient::CreateSocket(): Could not create socket!" << std::endl;
		return false;
	}

	return true;
}

bool HTTPClient::ShutdownSocket()
{
	const int nResult = shutdown(m_recSocket, SD_SEND);

	if (nResult == SOCKET_ERROR)
	{
		std::cerr << "CHTTPClient::ShutDownSocket(): Could not shut down socket!" << std::endl;
		return false;
	}

	return true;
}

std::string HTTPClient::CreateRequest(const HTTPRequestMethods& eHTTPRequestMethod)
{
	std::string strRequest = EMPTY_STRING;

	switch (eHTTPRequestMethod)
	{
		case HTTPRequestMethodGET:
			strRequest += HTTP_REQUEST_METHOD_GET;
			break;
		case HTTPRequestMethodHEAD:
			strRequest += HTTP_REQUEST_METHOD_HEAD;
			break;
		case HTTPRequestMethodPOST:
			strRequest += HTTP_REQUEST_METHOD_POST;
			break;
		case HTTPRequestMethodPUT:
			strRequest += HTTP_REQUEST_METHOD_PUT;
			break;
		case HTTPRequestMethodDELETE:
			strRequest += HTTP_REQUEST_METHOD_DELETE;
			break;
		case HTTPRequestMethodPATCH:
			strRequest += HTTP_REQUEST_METHOD_PATCH;
			break;
		case HTTPRequestMethodOPTIONS:
			strRequest += HTTP_REQUEST_METHOD_OPTIONS;
			break;
		case HTTPRequestMethodCONNECT:
			strRequest += HTTP_REQUEST_METHOD_CONNECT;
			break;
		case HTTPRequestMethodTRACE:
			strRequest += HTTP_REQUEST_METHOD_TRACE;
			break;
		default:
			break;
	}

	strRequest += m_oURLParser.GetPath() + HTTP_VERSION + HTTP_HOST +
		          m_oURLParser.GetHost() + "\r\n" + HTTP_CONNECTION_CLOSED;

	return strRequest;
}

bool HTTPClient::ConnectToServer()
{
	if (!m_bIsWSAStarted)
		InitClient();

	if (!CreateSocket())
	{
		Cleanup();
		return false;
	}

	const std::string strHost = m_oURLParser.GetHost();
	const unsigned short usPort = m_oURLParser.GetPort();

	sockaddr_in recServerAddress;
	recServerAddress.sin_family = AF_INET;

	if (usPort > ZERO && usPort != DEFAULT_PORT)
		recServerAddress.sin_port = htons(usPort);
	else
		recServerAddress.sin_port = htons(DEFAULT_PORT);

	addrinfo* pAddressInfo = nullptr;
	if (!m_oDNS.GetAddressInfo(strHost.c_str(), pAddressInfo))
	{
		ShutdownSocket();
		closesocket(m_recSocket);
		Cleanup();

		return false;
	}

	sockaddr_in* pServerAddress = (sockaddr_in*)(pAddressInfo->ai_addr);
	recServerAddress.sin_addr = pServerAddress->sin_addr;

	const int nResult = connect(m_recSocket, (sockaddr*)(&recServerAddress), sizeof(recServerAddress));

	if (nResult == SOCKET_ERROR)
	{
		std::cerr << "CHTTPClient::ConnectToServer(): Could not connect to server! Error code: " << WSAGetLastError() << std::endl;

		ShutdownSocket();
		closesocket(m_recSocket);
		Cleanup();

		return false;
	}

	freeaddrinfo(pAddressInfo);
	std::cout << "Connection established.\n" << std::endl;

	return true;
}

bool HTTPClient::DownloadDocument()
{
	if (!m_bIsWSAStarted || m_recSocket == INVALID_SOCKET)
	{
		std::cerr << "CHTTPClient::DownloadDocument(): Connection not established!" << std::endl;
		return false;
	}

	if (!Send(HTTPRequestMethodGET))
		return false;

	if (!Receive(m_strBuffer))
		return false;

	std::cout << "Document downloaded.\n" << std::endl;

	return true;
}

bool HTTPClient::CloseConnection()
{
	if (!m_bIsWSAStarted)
	{
		std::cerr << "CHTTPClient::CloseConnection(): WSA not started, connect to server!" << std::endl;
		return false;
	}

	if (!ShutdownSocket())
	{
		closesocket(m_recSocket);
		Cleanup();

		return false;
	}

	if (!Receive(m_strBuffer))
		return false;

	closesocket(m_recSocket);
	Cleanup();

	std::cout << "Connection closed.\n" << std::endl;

	return true;
}

bool HTTPClient::Send(const HTTPRequestMethods& eHTTPRequestMethod)
{
	const std::string strRequest = CreateRequest(eHTTPRequestMethod);
	const int nResult = send(m_recSocket, strRequest.c_str(), static_cast<int>(strRequest.length()), ZERO);

	if (nResult == SOCKET_ERROR)
	{
		std::cerr << "CHTTPClient::Send(): Failed to send HTTP request!\n\n" << strRequest << std::endl;
		return false;
	}

	return true;
}

bool HTTPClient::Receive(std::string& strBuffer)
{
	char cReceivingBuffer[RECEIVING_BUFFER_SIZE];
	int nBytesRead = ZERO;

	strBuffer.clear();

	do
	{
		nBytesRead = recv(m_recSocket, cReceivingBuffer, RECEIVING_BUFFER_SIZE, ZERO);

		if (nBytesRead > ZERO)
		{
			strBuffer += cReceivingBuffer;
		}
		else if (nBytesRead == ZERO)
		{
			std::cout << "Data received.\n" << std::endl;
		}
		else
		{
			std::cerr << "CHTTPClient::Receive(): There was a problem from the other side while attempting to close the connection!" << std::endl;
			return false;
		}
	} while (nBytesRead > ZERO);

	return true;
}

void HTTPClient::SetURL(const std::string& strURL, bool bParse /* = true */)
{
	m_oURLParser.SetInput(strURL);

	if (bParse)
		m_oURLParser.Parse();
}

const std::string HTTPClient::GetBuffer() const
{
	return m_strBuffer;
}