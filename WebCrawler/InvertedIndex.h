#pragma once

#include <vector>
#include <map>

#include "BinaryTree.h"


class InvertedIndex
{
	// Constants
	// ----------------


	// Constructor / Destructor
	// ----------------
public:
	InvertedIndex(const std::string& strFilePath);
	virtual ~InvertedIndex();


	// Overrides
	// ----------------


	// Methods
	// ----------------
private:
	bool IsAlpha(const char& cSymbol);
	bool IsDigit(const char& cSymbol);

	void RemovePunctuation(std::string& strInput);
	std::vector<std::string> Tokenize(const std::string& strInput);
	void RemoveCommonTokens(std::vector<std::string>& oTokensVector);
	void AddDocument(const std::vector<std::string>& oTokensVector);
	void CalculateTFIDF();

	/* 1. ������� ����� �� ���� Node.
	   2. ������� ����������� ���� ����� �� ����� ���� � TFIDF ���������� �� ����� Node � �������.
	   3. ������� ��������.
	   4. ������� Utilities.h � ������� defines � �� ������� � ������� .cpp �������.
	   5. ��������� ����� ���� � ������� �������� �� �� � ��� �� ����������� ��. 
	   6. ������ ���� �� ����� �� ��������� �� ���� �� ���������. 
	   7. ����� breakpoints. */

public:
	void Construct();
	void PrintInfo();


	// Members
	// ----------------
private:
	short m_sDocumentsCount;
	std::string m_strFilePath;
	BinaryTree m_oBinaryTree;
};