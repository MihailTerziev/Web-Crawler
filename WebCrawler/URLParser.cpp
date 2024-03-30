#include "URLParser.h"


#define PERIOD			'.'
#define SEMICOLON		';'
#define QUOTES			'\"'
#define COLON			':'
#define SLASH			'/'


URLParser::URLParser(const std::string& strInput)
	: Parser<URLTokenTypes>(strInput), m_usPort(ZERO)
{
}

URLParser::~URLParser()
{
}

void URLParser::GetNextToken()
{
	SkipSpaces();

	if (IsAlpha())
	{
		GetIdentifier();
		m_eTokenType = URLTokenTypeXalphas;
	}
	else if (IsDigit())
	{
		GetConstant();
		m_eTokenType = URLTokenTypeIntconst;
	}
	else
	{
		switch (m_cSymbol)
		{
			case SEMICOLON:
			{
				m_eTokenType = URLTokenTypeSemicolon;
				break;
			}
			case PERIOD:
			{
				m_eTokenType = URLTokenTypePeriod;
				break;
			}
			case QUOTES:
			{
				m_eTokenType = URLTokenTypeQuotes;
				break;
			}
			case COLON:
			{
				m_eTokenType = URLTokenTypeColon;
				break;
			}
			case SLASH:
			{
				m_eTokenType = URLTokenTypeSlash;
				break;
			}
			default:
			{
				m_eTokenType = URLTokenTypeOther;
				break;
			}
		}

		std::cout << m_cSymbol << std::endl;
		GetNextChar();
	}
}

bool URLParser::IsSpecialSymbol()
{
	return IsXalpha();
}

void URLParser::Parse()
{
	HTTPAddress();
}

bool URLParser::IsXalpha()
{
	return IsAlpha() || IsDigit() || IsSafe();
}

bool URLParser::IsSafe()
{
	return m_cSymbol == '$' || m_cSymbol == '-' ||
		   m_cSymbol == '_' || m_cSymbol == '@' ||
		   m_cSymbol == '&';
}

void URLParser::HTTPAddress()
{
	GetNextToken();

	if (AcceptToken(URLTokenTypeXalphas))
	{
		ExpectToken(URLTokenTypeColon);
		ExpectToken(URLTokenTypeSlash);
		ExpectToken(URLTokenTypeSlash);
		Hostport();

		if (m_eTokenType != URLTokenTypeOther)
		{
			ExpectToken(URLTokenTypeSlash);
			Path();
		}
	}
}

void URLParser::Hostport()
{
	Host();

	if (m_eTokenType == URLTokenTypeColon)
	{
		AcceptToken(URLTokenTypeColon);
		Port();
	}
}

void URLParser::Host()
{
	if (m_eTokenType == URLTokenTypeXalphas)
	{
		//std::cout << "hostname: ";
		Hostname();
	}
	else if (m_eTokenType == URLTokenTypeIntconst)
	{
		//std::cout << "hostnumber: ";
		Hostnumber();
	}
	else
	{
		std::cerr << "CURLParser::Host(): Expects intconst or string!" << std::endl;
	}
}

void URLParser::Hostname()
{
	//std::cout << m_strIdentBuffer;
	//if (m_cSymbol != COLON) std::cout << m_cSymbol;

	m_strHost.append(m_strIdent);

	if (m_cSymbol == PERIOD)
		m_strHost.push_back(m_cSymbol);

	if (m_cSymbol == SLASH)
		m_strPath.push_back(m_cSymbol);

	ExpectToken(URLTokenTypeXalphas);

	if (m_eTokenType != URLTokenTypeSlash && 
		m_eTokenType != URLTokenTypeColon && 
		m_eTokenType != URLTokenTypeOther)
	{
		ExpectToken(URLTokenTypePeriod);
		Hostname();
	}

	//std::cout << std::endl;
}

void URLParser::Hostnumber()
{
	//std::cout << m_nConstant;
	//if (m_cSymbol != COLON) std::cout << m_cSymbol;

	m_strHost.append(std::to_string(m_nConstant));

	if (m_cSymbol == PERIOD)
		m_strHost.push_back(m_cSymbol);

	if (m_cSymbol == SLASH)
		m_strPath.push_back(m_cSymbol);

	ExpectToken(URLTokenTypeIntconst);

	if (m_eTokenType != URLTokenTypeSlash &&
		m_eTokenType != URLTokenTypeColon &&
		m_eTokenType != URLTokenTypeOther)
	{
		ExpectToken(URLTokenTypePeriod);
		Hostnumber();
	}

	//std::cout << std::endl;
}

void URLParser::Port()
{
	//std::cout << "Port: ";

	if (m_eTokenType == URLTokenTypeIntconst)
	{
		m_usPort = (unsigned short)m_nConstant;
		AcceptToken(URLTokenTypeIntconst);
	}

	//std::cout << m_nConstant;
	//std::cout << std::endl;
}

void URLParser::Path()
{
	if (m_eTokenType == URLTokenTypeOther)
		return;

	//std::cout << m_strIdentBuffer << m_cSymbol;
	m_strPath.append(m_strIdent).push_back(m_cSymbol);

	ExpectToken(URLTokenTypeXalphas);

	if (m_eTokenType != URLTokenTypePeriod)
	{
		ExpectToken(URLTokenTypeSlash);
		Path();
	}
	else
	{
		//std::cout << std::endl;
		//std::cout << "File: " << m_strIdentBuffer;
		if (ExpectToken(URLTokenTypePeriod)); 
			m_strPath.append(m_strIdent);
		//std::cout << m_strIdentBuffer;
		ExpectToken(URLTokenTypeXalphas);
	}
}

const std::string URLParser::GetHost() const
{
	return m_strHost;
}

const std::string URLParser::GetPath() const
{
	return m_strPath;
}

const unsigned short URLParser::GetPort() const
{
	return m_usPort;
}