#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "InvertedIndex.h"


#define ZERO		0
#define WHITESPACE	' '


InvertedIndex::InvertedIndex(const std::string& strFilePath)
	: m_sDocumentsCount(ZERO), m_strFilePath(strFilePath)
{
}

InvertedIndex::~InvertedIndex()
{
}

bool InvertedIndex::IsAlpha(const char& cSymbol)
{
	return (cSymbol >= 'A' && cSymbol <= 'Z') || (cSymbol >= 'a' && cSymbol <= 'z');
}

bool InvertedIndex::IsDigit(const char& cSymbol)
{
	return (cSymbol >= '0' && cSymbol <= '9');
}

void InvertedIndex::RemovePunctuation(std::string& strInput)
{
	const std::string strCopy = strInput;
	strInput.clear();

	for (std::string::const_iterator iterator = strCopy.begin(); iterator != strCopy.end(); iterator++)
	{
		const char cSymbol = *iterator;

		if (std::ispunct(cSymbol))
			continue;

		strInput.push_back(cSymbol);
	}
}

std::vector<std::string> InvertedIndex::Tokenize(const std::string& strInput)
{
	std::vector<std::string> oTokensVector;
	std::istringstream oStringStream(strInput);
	std::string strToken;

	while (oStringStream >> strToken)
		oTokensVector.push_back(strToken);

	return oTokensVector;
}

void InvertedIndex::AddDocument(const std::vector<std::string>& oTokensVector)
{
	m_sDocumentsCount++;

	for (size_t szIndex = 0; szIndex < oTokensVector.size(); szIndex++)
	{
		const std::string strWord = oTokensVector[szIndex];
		const std::pair<short, size_t> oWordData(m_sDocumentsCount, szIndex + 1);

		m_oBinaryTree.AddNode(strWord, oWordData);
	}
}

void InvertedIndex::PrintInfo()
{
	m_oBinaryTree.PrintInOrder();
}

void InvertedIndex::Construct()
{
	std::ifstream oInputStream;
	oInputStream.open(m_strFilePath);

	if (!oInputStream.is_open())
		std::cerr << "InvertedIndex::ConstructIndex(): Error opening file: " << m_strFilePath << std::endl;

	std::string strDocument;
	std::vector<std::string> oTokensVector;

	while (std::getline(oInputStream, strDocument))
	{
		RemovePunctuation(strDocument);
		oTokensVector = Tokenize(strDocument);
		AddDocument(oTokensVector);
	}

	oInputStream.close();
}