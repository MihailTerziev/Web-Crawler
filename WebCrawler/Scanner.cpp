#include "Scanner.h"


Scanner::Scanner(const std::string& strInput)
	: m_strInput(strInput), m_szPosition(ZERO), m_bIsTeminatorReached(false)
{
}

Scanner::~Scanner()
{
}

void Scanner::SetInput(const std::string& strInput)
{
	m_strInput = strInput;
}

void Scanner::GetNextChar(char& cSymbol)
{
	cSymbol = m_strInput[m_szPosition];

	if (cSymbol == TERMINATOR)
	{
		m_bIsTeminatorReached = true;
	}
	else
	{
		m_szPosition++;
	}
}

bool Scanner::IsTerminatorReached()
{
	return m_bIsTeminatorReached;
}