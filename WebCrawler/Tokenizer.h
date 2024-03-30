//#pragma once
//
//#include <string>
//
//#include "Scanner.h"
//
//#define MAXLENGTH		8
//#define WHITESPACE		' '
//
//
//template<typename TokenTypesEnum>
//class CTokenizer
//{
//	// Constants
//	// ----------------
//
//
//	// Constructor / Destructor
//	// ----------------
//public:
//	CTokenizer(const CScanner& oScanner, const size_t& szIdentBufferSize = MAXLENGTH);
//	virtual ~CTokenizer();
//
//
//	// Overrides
//	// ----------------
//protected:
//	virtual void GetNextToken() = 0;
//
//
//	// Methods
//	// ----------------
//protected:
//	void CleanIdentBuffer();
//
//public:
//	char GetSymbol();
//	int GetConstant();
//	std::string GetIdent();
//	TokenTypesEnum GetTokenType();
//
//
//	// Members
//	// ----------------
//protected:
//	char m_cSymbol;
//	int m_nConstant;
//	std::string m_strIdent;
//	TokenTypesEnum m_eTokenType;
//	const CScanner& m_oScanner;
//};
//
//
//template<typename TokenTypesEnum>
//CTokenizer<TokenTypesEnum>::CTokenizer(const CScanner& oScanner, const size_t& szIdentBufferSize)
//	: m_cSymbol(WHITESPACE), m_nConstant(ZERO),
//	  m_strIdentBuffer(szIdentBufferSize, WHITESPACE), m_oScanner(oScanner)
//{
//}
//
//template<typename TokenTypesEnum>
//CTokenizer<TokenTypesEnum>::~CTokenizer()
//{
//}
//
//template<typename TokenTypesEnum>
//void CTokenizer<TokenTypesEnum>::CleanIdentBuffer()
//{
//	for (size_t szPosition = ZERO; szPosition < m_strIdentBuffer.length(); szPosition++)
//		m_strIdentBuffer[szPosition] = WHITESPACE;
//}
//
//template<typename TokenTypesEnum>
//char CTokenizer<TokenTypesEnum>::GetSymbol()
//{
//	return m_cSymbol;
//}
//
//template<typename TokenTypesEnum>
//int CTokenizer<TokenTypesEnum>::GetConstant()
//{
//	return m_nConstant;
//}
//
//template<typename TokenTypesEnum>
//std::string CTokenizer<TokenTypesEnum>::GetIdent()
//{
//	return m_strIdent;
//}
//
//template<typename TokenTypesEnum>
//TokenTypesEnum CTokenizer<TokenTypesEnum>::GetTokenType()
//{
//	return m_eTokenType;
//}