#include <iostream>

#include "DNS.h"


DNS::DNS()
{
}

DNS::~DNS()
{
}

bool DNS::GetAddressInfo(PCSTR pHostName, addrinfo*& pAddressInfo, PCSTR pServiceName /* = nullptr */, ADDRINFOA* pHints /* = nullptr */)
{
	pAddressInfo = nullptr;

	const int nResult = getaddrinfo(pHostName, pServiceName, pHints, &pAddressInfo);

	if (nResult && pAddressInfo == nullptr)
	{
		std::cerr << "CDomainNameSystem::GetAddressInfo(): DNS resolution failed!" << std::endl;
		return false;
	}

	return true;
}