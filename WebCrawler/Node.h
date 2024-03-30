#pragma once

#include <string>
#include <map>


class Node 
{
    // Constants
    // ----------------


    // Constructor / Destructor
    // ----------------
public:
    Node(const std::string& strNewWord);
    virtual ~Node();


    // Overrides
    // ----------------


    // Methods
    // ----------------
public:
    void PrintInfo();


    // Members
    // ----------------
public:
    std::string strWord;
    std::map<short, size_t> oPostingMap;

    Node* pLeftNode;
    Node* pRightNode;
};