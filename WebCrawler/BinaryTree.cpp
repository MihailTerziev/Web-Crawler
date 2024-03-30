#include <iostream>

#include "BinaryTree.h"


BinaryTree::BinaryTree()
{
}

BinaryTree::~BinaryTree()
{
    DeleteTree();
}

Node* BinaryTree::Insert(Node* pNode, const std::string& strWord, const std::pair<short, size_t>& oWordData, Node*& pNewNode)
{
    if (pNode == nullptr)
    {
        pNewNode = new Node(strWord);
        pNewNode->oPostingMap.insert(oWordData);
        
        return pNewNode;
    }

    if (pNode->strWord > strWord)
    {
        pNode->pLeftNode = Insert(pNode->pLeftNode, strWord, oWordData, pNewNode);
    }
    else if (pNode->strWord < strWord)
    {
        pNode->pRightNode = Insert(pNode->pRightNode, strWord, oWordData, pNewNode);
    }
    else
    {
        pNewNode = pNode;
        pNewNode->oPostingMap.insert(oWordData);

        return pNode;
    }

    return pNode;
}

Node* BinaryTree::Remove(Node* pNode, const std::string& strWord)
{
    if (pNode == nullptr) 
    {
        return pNode;
    }

    if (pNode->strWord > strWord)
    {
        pNode->pLeftNode = Remove(pNode->pLeftNode, strWord);
    }
    else if (pNode->strWord < strWord)
    {
        pNode->pRightNode = Remove(pNode->pRightNode, strWord);
    }
    else 
    {
        if (pNode->pLeftNode == nullptr)
        {
            Node* pRightNode = pNode->pRightNode;

            delete pNode;
            pNode = nullptr;

            return pRightNode;
        }
        else if (pNode->pRightNode == nullptr)
        {
            Node* pLeftNode = pNode->pLeftNode;

            delete pNode;
            pNode = nullptr;

            return pLeftNode;
        }

        Node* pMinNode = FindMin(pNode->pRightNode);
        pNode->strWord = pMinNode->strWord;
        pNode->pRightNode = Remove(pNode->pRightNode, pMinNode->strWord);
    }

    return pNode;
}

Node* BinaryTree::FindMin(Node* pNode)
{
    while (pNode->pLeftNode != nullptr)
        pNode = pNode->pLeftNode;
    
    return pNode;
}

Node* BinaryTree::FindMin()
{
    return FindMin(m_pRootNode);
}

Node* BinaryTree::FindMax(Node* pNode)
{
    while (pNode->pRightNode != nullptr)
        pNode = pNode->pRightNode;

    return pNode;
}

Node* BinaryTree::FindMax()
{
    return FindMax(m_pRootNode);
}

Node* BinaryTree::AddNode(const std::string& strWord, const std::pair<short, size_t>& oWordData)
{
    Node* pNode = nullptr;
    m_pRootNode = Insert(m_pRootNode, strWord, oWordData, pNode);

    return pNode;
}

void BinaryTree::DeleteNode(const std::string& strWord)
{
    m_pRootNode = Remove(m_pRootNode, strWord);
}

void BinaryTree::DeleteNode(Node* pNode)
{
    m_pRootNode = Remove(m_pRootNode, pNode->strWord);
}

void BinaryTree::DeleteSubTree(Node*& pNode)
{
    if (pNode == nullptr)
        return;

    Node* pOriginalNode = pNode;
    pNode = nullptr;

    DeleteSubTree(pOriginalNode->pLeftNode);
    DeleteSubTree(pOriginalNode->pRightNode);

    delete pOriginalNode;
    pOriginalNode = nullptr;
}

void BinaryTree::DeleteSubTree(const std::string& strWord)
{
    Node* pSearchedNode = SearchNode(strWord);
    DeleteSubTree(pSearchedNode);
}

void BinaryTree::DeleteTree()
{
    DeleteSubTree(m_pRootNode);
}

Node*& BinaryTree::SearchNode(const std::string& strWord)
{
    Node** ppSearchedNode = &m_pRootNode;

    while (*ppSearchedNode != nullptr)
    {
        if ((*ppSearchedNode)->strWord == strWord)
        {
            break;
        }
        else if ((*ppSearchedNode)->strWord > strWord)
        {
            ppSearchedNode = &((*ppSearchedNode)->pLeftNode);
        }
        else
        {
            ppSearchedNode = &((*ppSearchedNode)->pRightNode);
        }
    }

    return *ppSearchedNode;
}

void BinaryTree::InOrderTraversal(Node* pNode) 
{
    if (pNode == nullptr)
        return;

    InOrderTraversal(pNode->pLeftNode);
    pNode->PrintInfo();
    InOrderTraversal(pNode->pRightNode);
}

void BinaryTree::PreOrderTraversal(Node* pNode) 
{
    if (pNode == nullptr)
        return;

    pNode->PrintInfo();
    PreOrderTraversal(pNode->pLeftNode);
    PreOrderTraversal(pNode->pRightNode);
}

void BinaryTree::PostOrderTraversal(Node* pNode) 
{
    if (pNode == nullptr)
        return;

    PostOrderTraversal(pNode->pLeftNode);
    PostOrderTraversal(pNode->pRightNode);
    pNode->PrintInfo();
}

void BinaryTree::IncreaseNodesValue(Node* pNode, const std::string& strWord)
{
    if (pNode == nullptr)
        return;

    pNode->strWord += strWord;

    IncreaseNodesValue(pNode->pLeftNode, strWord);
    IncreaseNodesValue(pNode->pRightNode, strWord);
}

int BinaryTree::FindTreeHeight(Node* pNode)
{
    if (pNode == nullptr)
        return 0;

    const int nLeftSubTreeHeight = FindTreeHeight(pNode->pLeftNode);
    const int nRightSubTreeHeight = FindTreeHeight(pNode->pRightNode);
    const int nTreeHeight = std::max(nLeftSubTreeHeight, nRightSubTreeHeight) + 1;

    return nTreeHeight;
}

void BinaryTree::PrintInOrder()
{
    InOrderTraversal(m_pRootNode);
    std::cout << std::endl;
}

void BinaryTree::PrintPreOrder()
{
    PreOrderTraversal(m_pRootNode);
    std::cout << std::endl;
}

void BinaryTree::PrintPostOrder()
{
    PostOrderTraversal(m_pRootNode);
    std::cout << std::endl;
}

void BinaryTree::IncreaseNodesValue(const std::string& strWord)
{
    IncreaseNodesValue(m_pRootNode, strWord);
}

int BinaryTree::GetHeight()
{
    return FindTreeHeight(m_pRootNode);
}