#pragma once

#include "Parser.h"


class URLParser : public Parser<URLTokenTypes>
{
	// Constants
	// ----------------


	// Constructor / Destructor
	// ----------------
public:
	URLParser(const std::string& strInput);
	virtual ~URLParser();


	// Overrides
	// ----------------
private:
	virtual void GetNextToken() override;
	virtual bool IsSpecialSymbol() override;

public:
	virtual void Parse() override;


	// Methods
	// ----------------
private:
	bool IsXalpha();
	bool IsSafe();

	void HTTPAddress();
	void Hostport();
	void Host();
	void Hostname();
	void Hostnumber();
	void Port();
	void Path();

public:
	const std::string GetHost() const;
	const std::string GetPath() const;
	const unsigned short GetPort() const;


	// Members
	// ----------------
private:
	std::string m_strHost;
	std::string m_strPath;
	unsigned short m_usPort;
};