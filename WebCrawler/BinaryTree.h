#pragma once

#include "Node.h"


class BinaryTree
{
	// Constants
	// ----------------


	// Constructor / Destructor
	// ----------------
public:
	BinaryTree();
	virtual ~BinaryTree();


	// Overrides
	// ----------------


	// Methods
	// ----------------
private:
	Node* Insert(Node* pNode, const std::string& strWord, const std::pair<short, size_t>& oWordData, Node*& pNewNode);

	Node* Remove(Node* pNode, const std::string& strWord);

	void InOrderTraversal(Node* pNode);
	void PreOrderTraversal(Node* pNode);
	void PostOrderTraversal(Node* pNode);

	void IncreaseNodesValue(Node* pNode, const std::string& strWord);

	int FindTreeHeight(Node* pNode);

public:
	Node* AddNode(const std::string& strWord, const std::pair<short, size_t>& oWordData);

	void DeleteNode(const std::string& strWord);
	void DeleteNode(Node* pNode);

	void DeleteSubTree(Node*& pNode);
	void DeleteSubTree(const std::string& strWord);

	void DeleteTree();

	Node* FindMin(Node* pNode);
	Node* FindMin();

	Node* FindMax(Node* pNode);
	Node* FindMax();

	Node*& SearchNode(const std::string& strWord);

	void PrintInOrder();
	void PrintPreOrder();
	void PrintPostOrder();

	void IncreaseNodesValue(const std::string& strWord);

	int GetHeight();


	// Members
	// ----------------
private:
	Node* m_pRootNode;
};