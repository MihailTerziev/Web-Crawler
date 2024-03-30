#pragma once

#include "Parser.h"


class HTMLParser : public Parser<HTMLTokenTypes>
{
	// Constants
	// ----------------


	// Constructor / Destructor
	// ----------------
public:
	HTMLParser(const std::string& strInput, const std::string& strFilePath = EMPTY_STRING);
	virtual ~HTMLParser();


	// Overrides
	// ----------------
private:
	virtual void GetNextToken() override;

public:
	virtual void Parse() override;


	// Methods
	// ----------------
private:
	void OpenTag(void (HTMLParser::*TagAttributesFunction)() = nullptr);
	void CloseTag();

	bool IsTag();
	bool IsTagAttribute();
	bool IsSpecialSymbol();
	bool IsEncapsulatingTextSymbol();

	void GetPlainText();
	void AddInFile();
	void TruncateFile();

	void HTMLDocument();
	void Body();
	void HTML();
	void Anchor();
	void AnchorAttributes();
	void AttributeValue();

public:
	bool ExtractHTML(const std::string& strInput);
	const std::string GetURL() const;


	// Members
	// ----------------
private:
	std::string m_strURL;
	std::string m_strFilePath;
};