#ifndef TRIE_H
#define TRIE_H

#include <unordered_map>
#include "CharString.h"
#include <iostream>


class trieNode
{
public:
	wchar_t character;
	int isWordEnd;	//1-��ǰ׺��2-�Ǵ���
	int freq;		//���ֵ�Ƶ��
	unordered_map<wchar_t, trieNode> list;
public:
	trieNode()
	{
		isWordEnd = false;
		freq = 0;
	}
	~trieNode()
	{
	}
};

class dicTree
{
private:
	trieNode root;
public:
	dicTree();
	~dicTree();
public:
	void insertString(const CharString& stringToInsert);
	int findString(const CharString& stringToFind);
	trieNode* getRoot();
};

#endif