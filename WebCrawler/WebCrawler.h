#pragma once

#include "HTMLParser.h"
#include "HTTPClient.h"
#include "InvertedIndex.h"


class WebCrawler
{
	// Constants
	// ----------------


	// Constructor / Destructor
	// ----------------
public:
	WebCrawler(const std::string& strInput);
	virtual ~WebCrawler();


	// Overrides
	// ----------------


	// Methods
	// ----------------
public:
	bool Run();
	void SetURL(const std::string& strURL);
	void PrintIndexInfo();


	// Members
	// ----------------
private:
	HTTPClient m_oHTTPClient;
	HTMLParser m_oHTMLParser;
	InvertedIndex m_oInvertedIndex;
};