#include <iostream>
#include <fstream>

#include "HTMLParser.h"


#define SINGLE_QUOTES		'\''
#define DOUBLE_QUOTES		'\"'
#define SLASH				'/'
#define LEFT_ANGLE_BRACKET	'<'
#define RIGHT_ANGLE_BRACKET	'>'
#define EQUALS_SIGN			'='

#define HTML_TAG			"html"
#define BODY_TAG			"body"
#define ANCHOR_TAG			"a"

#define HREF_TAG			"href"
#define HTTP_TAG			"http"

#define OPENING_HTML_TAG	"<html>"
#define CLOSING_HTML_TAG	"</html>"


HTMLParser::HTMLParser(const std::string& strInput, const std::string& strFilePath /* = EMPTY_STRING */)
	: Parser<HTMLTokenTypes>(strInput), m_strFilePath(strFilePath)
{
}

HTMLParser::~HTMLParser()
{
}

void HTMLParser::GetNextToken()
{
	SkipSpaces();

	if (m_eTokenType != HTMLTokenTypeOther && !IsSpecialSymbol())
	{
		GetPlainText();
		m_eTokenType = HTMLTokenTypePlainText;
	}
	else
	{
		switch (m_cSymbol)
		{
			case SINGLE_QUOTES:
			{
				m_eTokenType = HTMLTokenTypeSingleQuotes;
				break;
			}
			case DOUBLE_QUOTES:
			{
				m_eTokenType = HTMLTokenTypeDoubleQuotes;
				break;
			}
			case SLASH:
			{
				m_eTokenType = HTMLTokenTypeSlash;
				break;
			}
			case LEFT_ANGLE_BRACKET:
			{
				m_eTokenType = HTMLTokenTypeLeftAngleBracket;
				break;
			}
			case RIGHT_ANGLE_BRACKET:
			{
				m_eTokenType = HTMLTokenTypeRightAngleBracket;
				break;
			}
			case EQUALS_SIGN:
			{
				m_eTokenType = HTMLTokenTypeEqualsSign;
				break;
			}
			default:
			{
				m_eTokenType = HTMLTokenTypeOther;
				break;
			}
		}

		std::cout << m_cSymbol;

		if (m_cSymbol == RIGHT_ANGLE_BRACKET)
			std::cout << std::endl;

		GetNextChar();
	}
}

void HTMLParser::Parse()
{
	TruncateFile();
	HTMLDocument();
}

void HTMLParser::OpenTag(void (HTMLParser::*TagAttributesFunction)())
{
	if (m_eTokenType == HTMLTokenTypeLeftAngleBracket && m_cSymbol != SLASH)
	{
		AcceptToken(HTMLTokenTypeLeftAngleBracket);
		ExpectToken(HTMLTokenTypePlainText);

		if (TagAttributesFunction != nullptr && m_eTokenType == HTMLTokenTypePlainText)
			(this->*TagAttributesFunction)();

		ExpectToken(HTMLTokenTypeRightAngleBracket);
	}
}

void HTMLParser::CloseTag()
{
	if (m_eTokenType == HTMLTokenTypeLeftAngleBracket)
	{
		AcceptToken(HTMLTokenTypeLeftAngleBracket);
		ExpectToken(HTMLTokenTypeSlash);
		ExpectToken(HTMLTokenTypePlainText);
		ExpectToken(HTMLTokenTypeRightAngleBracket);
	}
}

bool HTMLParser::IsTag()
{
	return m_strIdent == HTML_TAG ||
		   m_strIdent == BODY_TAG ||
		   m_strIdent == ANCHOR_TAG;
}

bool HTMLParser::IsTagAttribute()
{
	return m_strIdent == HREF_TAG;
}

bool HTMLParser::IsSpecialSymbol()
{
	return IsEncapsulatingTextSymbol() || m_cSymbol == SLASH || m_cSymbol == TERMINATOR;
}

bool HTMLParser::IsEncapsulatingTextSymbol()
{
	return m_cSymbol == SINGLE_QUOTES ||
		   m_cSymbol == DOUBLE_QUOTES ||
	       m_cSymbol == LEFT_ANGLE_BRACKET ||
		   m_cSymbol == RIGHT_ANGLE_BRACKET ||
		   m_cSymbol == EQUALS_SIGN;
}

void HTMLParser::GetPlainText()
{
	m_strIdent.clear();

	bool bIsTag = false;
	bool bIsTagAttribute = false;

	do
	{
		m_strIdent.push_back(m_cSymbol);

		bIsTag = IsTag();
		bIsTagAttribute = IsTagAttribute();

		GetNextChar();

		if (bIsTagAttribute)
			SkipSpaces();
	} 
	while (!IsEncapsulatingTextSymbol() && !bIsTag);

	if (!bIsTag && !bIsTagAttribute && m_strIdent.find(HTTP_TAG) == std::string::npos)
		AddInFile();

	std::cout << m_strIdent;

	if (bIsTag && m_cSymbol != RIGHT_ANGLE_BRACKET)
		std::cout << WHITESPACE;
}

void HTMLParser::AddInFile()
{
	if (m_strFilePath.empty())
		return;

	std::ofstream oOutputStream(m_strFilePath, std::ios::app);

	if (!oOutputStream.is_open())
	{
		std::cerr << "CHTMLParser::AddInFile(): Error opening file: " << m_strFilePath << std::endl;
		return;
	}

	oOutputStream << m_strIdent << std::endl;

	oOutputStream.close();
}

void HTMLParser::TruncateFile()
{
	if (m_strFilePath.empty())
		return;

	std::ofstream oOutputStream(m_strFilePath, std::ios::trunc);

	if (!oOutputStream.is_open())
	{
		std::cerr << "CHTMLParser::TruncateFile(): Error opening file: " << m_strFilePath << std::endl;
		return;
	}

	oOutputStream.close();
}

void HTMLParser::HTMLDocument()
{
	GetNextToken();

	OpenTag();
	Body();
	CloseTag();

	std::cout << std::endl;
}

void HTMLParser::Body()
{
	OpenTag();
	HTML();
	CloseTag();
}

void HTMLParser::HTML()
{
	if (m_cSymbol == SLASH)
		return;

	if (m_eTokenType == HTMLTokenTypePlainText)
	{
		std::cout << std::endl;
		AcceptToken(HTMLTokenTypePlainText);
	}

	if (m_eTokenType == HTMLTokenTypeLeftAngleBracket && m_cSymbol != SLASH)
		Anchor();

	HTML();
}

void HTMLParser::Anchor()
{
	OpenTag(&HTMLParser::AnchorAttributes);
	HTML();
	CloseTag();
}

void HTMLParser::AnchorAttributes()
{
	if (m_eTokenType == HTMLTokenTypePlainText)
	{
		AcceptToken(HTMLTokenTypePlainText);
		ExpectToken(HTMLTokenTypeEqualsSign);

		AttributeValue();
	}
}

void HTMLParser::AttributeValue()
{
	const HTMLTokenTypes eQuotesType = m_eTokenType;

	if (eQuotesType == HTMLTokenTypeSingleQuotes || eQuotesType == HTMLTokenTypeDoubleQuotes)
		AcceptToken(eQuotesType);

	m_strURL = m_strIdent;

	ExpectToken(HTMLTokenTypePlainText);

	if (m_eTokenType != HTMLTokenTypeRightAngleBracket)
		ExpectToken(eQuotesType);
}

bool HTMLParser::ExtractHTML(const std::string& strInput)
{
	const size_t szHTMLOpeningTagPosition = strInput.find(OPENING_HTML_TAG);

	if (szHTMLOpeningTagPosition == std::string::npos)
	{
		std::cerr << "CHTMLParser::ExtractHTML(): Opening HTML tag was not extracted from server responce!" << std::endl;
		return false;
	}

	const size_t szHTMLClosingTagPosition = strInput.find(CLOSING_HTML_TAG, szHTMLOpeningTagPosition);

	if (szHTMLClosingTagPosition == std::string::npos)
	{
		std::cerr << "CHTMLParser::ExtractHTML(): Closing HTML tag was not extracted from server responce!" << std::endl;
		return false;
	}

	const size_t szCount = szHTMLClosingTagPosition - szHTMLOpeningTagPosition + (sizeof(CLOSING_HTML_TAG) / sizeof(char)) - 1;

	SetInput(strInput.substr(szHTMLOpeningTagPosition, szCount));

	return true;
}

const std::string HTMLParser::GetURL() const
{
	return m_strURL;
}