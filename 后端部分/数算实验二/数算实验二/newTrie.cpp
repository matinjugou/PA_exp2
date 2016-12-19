
#include "stdafx.h"
#include "newTrie.h"
#include "Stack.h"
#include "Stack.cpp"
dicTree::dicTree()
{
	root.freq = 0;
	root.isWordEnd = 1;
	root.character = L'\0';
}

dicTree::~dicTree()
{
}

void dicTree::insertString(const CharString & stringToInsert)
{
	trieNode* curNode = &root;
	int i = 0;
	trieNode tmpNode;
	while (i < stringToInsert.getLength())
	{
		std::unordered_map<wchar_t, trieNode>::iterator got = curNode->list.find(stringToInsert[i]);
		if (got == curNode->list.end())
		{
			tmpNode.character = stringToInsert[i];
			tmpNode.isWordEnd = 1;
			tmpNode.freq = 0;
			curNode->list.insert({ stringToInsert[i], tmpNode });
			curNode = &curNode->list[stringToInsert[i]];
			i++;
		}
		else
		{
			i++;
			curNode = &got->second;
		}
		if (i == stringToInsert.getLength())
		{
			curNode->isWordEnd = 2;
			curNode->freq++;
		}
	}
}


int dicTree::findString(const CharString & stringToFind)
{
	trieNode* curNode = &root;
	int i = 0;
	if (stringToFind.getLength() == 0)
		return 0;
	while (i < stringToFind.getLength())
	{
		std::unordered_map<wchar_t, trieNode>::iterator got = curNode->list.find(stringToFind[i]);
		if (got == curNode->list.end())
			return 0;
		else
		{
			i++;
			curNode = &got->second;
		}
	}
	return curNode->isWordEnd;
}

trieNode* dicTree::getRoot()
{
	return &root;
}
