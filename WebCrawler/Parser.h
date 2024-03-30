#pragma once

#include <iostream>
#include <string>

#include "TokenTypesEnums.h"


#define ZERO			0
#define MAXINTEGER		1000000

#define TERMINATOR		'\0'
#define WHITESPACE		' '
#define CARRIAGE_RETURN	'\r'
#define LINE_FEED		'\n'
#define TAB_CHARACTER	'\t'

#define EMPTY_STRING	""


template<typename TokenTypesEnum>
class Parser
{
	// Constants
	// ----------------


	// Constructor / Destructor
	// ----------------
public:
	Parser(const std::string& strInput);
	virtual ~Parser();


	// Overrides
	// ----------------
protected:
	virtual void GetNextToken() = 0;

public:
	virtual void Parse() = 0;


	// Methods
	// ----------------
protected:
	void SkipSpaces();
	void SkipToChar(const char& cSymbol);

	bool IsAlpha();
	bool IsDigit();
	virtual bool IsSpecialSymbol();

	void GetNextChar();
	void GetIdentifier();
	void GetConstant();
	
	bool AcceptToken(const TokenTypesEnum& eTokenType);
	bool ExpectToken(const TokenTypesEnum& eTokenType);

public:
	void SetInput(const std::string& strInput);


	// Members
	// ----------------
protected:
	size_t m_szPosition;
	std::string m_strInput;
	char m_cSymbol;
	int m_nConstant;
	std::string m_strIdent;
	TokenTypesEnum m_eTokenType;
};


template<typename TokenTypesEnum>
Parser<TokenTypesEnum>::Parser(const std::string& strInput)
	: m_strInput(strInput), m_szPosition(ZERO), m_cSymbol(WHITESPACE), m_nConstant(ZERO)
{
}

template<typename TokenTypesEnum>
Parser<TokenTypesEnum>::~Parser()
{
}

template<typename TokenTypesEnum>
void Parser<TokenTypesEnum>::SkipSpaces()
{
	while (m_cSymbol == WHITESPACE || m_cSymbol == CARRIAGE_RETURN ||
		   m_cSymbol == LINE_FEED  || m_cSymbol == TAB_CHARACTER)
	{
		GetNextChar();
	}
}

template<typename TokenTypesEnum>
void Parser<TokenTypesEnum>::SkipToChar(const char& cSymbol)
{
	while (m_cSymbol != cSymbol)
		GetNextChar();
}

template<typename TokenTypesEnum>
bool Parser<TokenTypesEnum>::IsAlpha()
{
	return (m_cSymbol >= 'A' && m_cSymbol <= 'Z') || (m_cSymbol >= 'a' && m_cSymbol <= 'z');
}

template<typename TokenTypesEnum>
bool Parser<TokenTypesEnum>::IsDigit()
{
	return (m_cSymbol >= '0' && m_cSymbol <= '9');
}

template<typename TokenTypesEnum>
bool Parser<TokenTypesEnum>::IsSpecialSymbol()
{
	return false;
}

template<typename TokenTypesEnum>
void Parser<TokenTypesEnum>::SetInput(const std::string& strInput)
{
	m_strInput = strInput;
}

template<typename TokenTypesEnum>
void Parser<TokenTypesEnum>::GetNextChar()
{
	m_cSymbol = m_strInput[m_szPosition];

	if (m_cSymbol != TERMINATOR)
		m_szPosition++;
}

template<typename TokenTypesEnum>
void Parser<TokenTypesEnum>::GetIdentifier()
{
	m_strIdent.clear();

	do
	{
		m_strIdent.push_back(m_cSymbol);
		GetNextChar();
	} 
	while (IsSpecialSymbol());

	std::cout << m_strIdent << std::endl;
}

template<typename TokenTypesEnum>
void Parser<TokenTypesEnum>::GetConstant()
{
	m_nConstant = ZERO;
	int nDigit = ZERO;

	do
	{
		nDigit = (unsigned int)m_cSymbol - (unsigned int)'0';

		if ((m_nConstant < MAXINTEGER / 10) ||
			((m_nConstant == MAXINTEGER / 10) &&
			 (nDigit == MAXINTEGER % 10)))
		{
			m_nConstant *= 10;
			m_nConstant += nDigit;
		}
		else
		{
			std::cerr << "CHTMLTokenizer::GetConstant: Int constant too large!" << std::endl;
			m_nConstant = ZERO;
		}

		GetNextChar();
	} while (IsDigit());

	std::cout << m_nConstant << std::endl;
}

template<typename TokenTypesEnum>
bool Parser<TokenTypesEnum>::AcceptToken(const TokenTypesEnum& eTokenType)
{
	if (m_eTokenType != eTokenType)
		return false;

	GetNextToken();

	return true;
}

template<typename TokenTypesEnum>
bool Parser<TokenTypesEnum>::ExpectToken(const TokenTypesEnum& eTokenType)
{
	if (!AcceptToken(eTokenType))
	{
		std::cerr << "CAnalyzer::ExpectToken: Unexpected symbol!" << std::endl;
		return false;
	}

	return true;
}