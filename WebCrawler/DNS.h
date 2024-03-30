#pragma once

#include <string>
#include <ws2tcpip.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")


class DNS
{
	// Constants
	// ----------------


	// Constructor / Destructor
	// ----------------
public:
	DNS();
	virtual ~DNS();


	// Overrides
	// ----------------


	// Methods
	// ----------------
public:
	bool GetAddressInfo(PCSTR pHostName, addrinfo*& pAddressInfo, PCSTR pServiceName = nullptr, ADDRINFOA* pHints = nullptr);


	// Members
	// ----------------
};