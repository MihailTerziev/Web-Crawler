//#pragma once
//
//#include "Tokenizer.h"
//#include "TokenTypesEnums.h"
//
//
//class CHTMLTokenizer : public CTokenizer<HTMLTokenTypes>
//{
//	// Constants
//	// ----------------
//
//
//	// Constructor / Destructor
//	// ----------------
//public:
//	CHTMLTokenizer();
//	virtual ~CHTMLTokenizer();
//
//
//	// Overrides
//	// ----------------
//public:
//	virtual void GetNextToken() override;
//
//
//	// Methods
//	// ----------------
//private:
//	bool IsAlpha(const char& cSymbol);
//	bool IsDigit(const char& cSymbol);
//
//	void GetIdentifier();
//	void GetConstant();
//
//
//	// Members
//	// ----------------
//};