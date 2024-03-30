#include "WebCrawler.h"


#define WORDS_FILE	"words.txt"


WebCrawler::WebCrawler(const std::string& strInput)
	: m_oHTTPClient(strInput), m_oHTMLParser(EMPTY_STRING, WORDS_FILE), m_oInvertedIndex(WORDS_FILE)
{
}

WebCrawler::~WebCrawler()
{
}

bool WebCrawler::Run()
{
	if (!m_oHTTPClient.ConnectToServer())
		return false;

	if (!m_oHTTPClient.DownloadDocument())
		return m_oHTTPClient.CloseConnection();

	const std::string strServerResponse = m_oHTTPClient.GetBuffer();
	const bool bResult = m_oHTMLParser.ExtractHTML(strServerResponse);

	if (!m_oHTTPClient.CloseConnection())
		return false;

	if (bResult)
	{
		m_oHTMLParser.Parse();
		m_oInvertedIndex.Construct();
	}

	return true;
}

void WebCrawler::SetURL(const std::string& strURL)
{
	m_oHTTPClient.SetURL(strURL, false);
}

void WebCrawler::PrintIndexInfo()
{
	m_oInvertedIndex.PrintInfo();
}