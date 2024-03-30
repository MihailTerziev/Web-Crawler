#pragma once

#include <string>

#define ZERO			0
#define TERMINATOR		'\0'


class Scanner
{
	// Constants
	// ----------------


	// Constructor / Destructor
	// ----------------
public:
	Scanner(const std::string& strInput);
	virtual ~Scanner();


	// Overrides
	// ----------------


	// Methods
	// ----------------
public:
	void SetInput(const std::string& strInput);
	void GetNextChar(char& cSymbol);
	bool IsTerminatorReached();


	// Members
	// ----------------
private:
	std::string m_strInput;
	size_t m_szPosition;
	bool m_bIsTeminatorReached;
};