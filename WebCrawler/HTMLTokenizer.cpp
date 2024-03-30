//#include "HTMLTokenizer.h"
//
//
//#define PERIOD			'.'
//#define SEMICOLON		';'
//#define QUOTES			'\"'
//
//
//CHTMLTokenizer::CHTMLTokenizer()
//{
//}
//
//CHTMLTokenizer::~CHTMLTokenizer()
//{
//}
//
//void CHTMLTokenizer::GetNextToken(CHTMLParser& oHTMLParser)
//{
	//while (oHTMLParser.m_cSymbol == WHITESPACE)
	//	oHTMLParser.m_oScanner.GetNextChar(oHTMLParser.m_cSymbol);

	//if (IsAlpha(oHTMLParser.m_cSymbol))
	//{
	//	GetIdentifier(oHTMLParser);
	//	oHTMLParser.m_eTokenType = HTMLTokenTypeText;
	//}
	//else if (IsDigit(oHTMLParser.m_cSymbol))
	//{
	//	GetConstant(oHTMLParser);
	//	oHTMLParser.m_eTokenType = HTMLTokenTypeIntconst;
	//}
	//else
	//{
	//	switch (oHTMLParser.m_cSymbol)
	//	{
	//		case SEMICOLON:
	//		{
	//			oHTMLParser.m_eTokenType = HTMLTokenTypeSemicolon;
	//			break;
	//		}
	//		case PERIOD:
	//		{
	//			oHTMLParser.m_eTokenType = HTMLTokenTypePeriod;
	//			break;
	//		}
	//		case QUOTES:
	//		{
	//			oHTMLParser.m_eTokenType = HTMLTokenTypeQuotes;
	//			break;
	//		}
	//		default:
	//		{
	//			oHTMLParser.m_eTokenType = HTMLTokenTypeOther;
	//			break;
	//		}
	//	}

	//	std::cout << oHTMLParser.m_cSymbol << std::endl;
	//	oHTMLParser.m_oScanner.GetNextChar(oHTMLParser.m_cSymbol);
	//}
//}
//
//bool CHTMLTokenizer::IsAlpha(const char& cSymbol)
//{
//	return (cSymbol >= 'A' && cSymbol <= 'Z') || (cSymbol >= 'a' && cSymbol <= 'z');
//}
//
//bool CHTMLTokenizer::IsDigit(const char& cSymbol)
//{
//	return (cSymbol >= '0' && cSymbol <= '9');
//}
//
//void CHTMLTokenizer::GetIdentifier()
//{
//	oHTMLParser.CleanIdentBuffer();
//	size_t szPosition = ZERO;
//
//	do
//	{
//		if (szPosition < MAXLENGTH)
//		{
//			oParser.m_strIdentBuffer[szPosition] = oParser.m_cSymbol;
//			szPosition++;
//		}
//
//		oParser.m_oScanner.GetNextChar(oParser.m_cSymbol);
//	} while (IsAlpha(oParser.m_cSymbol) || IsDigit(oParser.m_cSymbol));
//
//	std::cout << oParser.m_strIdentBuffer << std::endl;
//}
//
//void CHTMLTokenizer::GetConstant(CHTMLParser& oHTMLParser)
//{
//	oHTMLParser.m_nConstant = ZERO;
//	int nDigit = ZERO;
//
//	do
//	{
//		nDigit = (unsigned int)oHTMLParser.m_cSymbol - (unsigned int)'0';
//
//		if ((oHTMLParser.m_nConstant < MAXINTEGER / 10) ||
//			((oHTMLParser.m_nConstant == MAXINTEGER / 10) &&
//			 (nDigit == MAXINTEGER % 10)))
//		{
//			oHTMLParser.m_nConstant *= 10;
//			oHTMLParser.m_nConstant += nDigit;
//		}
//		else
//		{
//			std::cerr << "CHTMLTokenizer::GetConstant: Int constant too large!" << std::endl;
//			oHTMLParser.m_nConstant = ZERO;
//		}
//
//		oHTMLParser.m_oScanner.GetNextChar(oHTMLParser.m_cSymbol);
//	} while (IsDigit(oHTMLParser.m_cSymbol));
//
//	std::cout << oHTMLParser.m_nConstant << std::endl;
//}