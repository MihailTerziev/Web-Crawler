//#pragma once
//
//
//#include "Tokenizer.h"
//
//
//class CURLTokenizer : public CTokenizer
//{
//	// Constants
//	// ----------------
//
//
//	// Constructor / Destructor
//	// ----------------
//public:
//	CURLTokenizer();
//	virtual ~CURLTokenizer();
//
//
//	// Overrides
//	// ----------------
//protected:
//	virtual void GetNextToken() override;
//
//
//	// Methods
//	// ----------------
//private:
//	bool IsXalpha(const char& cSymbol);
//	bool IsAlpha(const char& cSymbol);
//	bool IsDigit(const char& cSymbol);
//	bool IsSafe(const char& cSymbol);
//	void GetIdentifier();
//	void GetConstant();
//	void SetSymbolTokenType();
//
//
//	// Members
//	// ----------------
//};