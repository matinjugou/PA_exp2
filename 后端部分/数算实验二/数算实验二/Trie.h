#ifndef TRIE_H
#define TRIE_H

#include "CharString.h"
#include <iostream>

class trieNode
{
public:
	wchar_t character;
	int isWordEnd;	//1-是前缀，2-是词语
	int freq;		//出现的频率
	trieNode* leftNode;
	trieNode* rightNode;
public:
	trieNode()
	{
		isWordEnd = false;
		leftNode = NULL;
		rightNode = NULL;
	}
	~trieNode()
	{
	}
};

class dicTree
{
private:
	trieNode* root;
public:
	dicTree();
	~dicTree();
public:
	void insertString(const CharString& stringToInsert);
	int findString(const CharString& stringToFind) const;
	trieNode* getRoot() const;
};

#endif