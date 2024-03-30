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

	/* 1. Промени името на клас Node.
	   2. Направи транспортен клас който ще държи мапа и TFIDF стойността за всеки Node в дървото.
	   3. Разпиши методите.
	   4. Попълни Utilities.h с нужните defines и го постави в нужните .cpp файлове.
	   5. Прегледай всеки клас и подреди методите да са в ред на дефиницията им. 
	   6. Добави флаг за опция на парсерите да може да принтират. 
	   7. Махни breakpoints. */

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