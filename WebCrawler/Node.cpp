#include <iostream>

#include "Node.h"


Node::Node(const std::string& strNewWord)
	: strWord(strNewWord), pLeftNode(nullptr), pRightNode(nullptr)
{
}

Node::~Node()
{
}

void Node::PrintInfo()
{
	std::cout << strWord << ' ';

	size_t szIndex = 0;
	const size_t szPostingMapSize = oPostingMap.size();
;
	for (std::map<short, size_t>::const_iterator oIterator = oPostingMap.begin(); oIterator != oPostingMap.end(); oIterator++)
	{
		std::cout << 'd' << oIterator->first << '/' << oIterator->second;

		if (szIndex != szPostingMapSize - 1)
			std::cout << ", ";

		szIndex++;
	}

	std::cout << '\n' << std::endl;
}