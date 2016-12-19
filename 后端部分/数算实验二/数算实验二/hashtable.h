#pragma once
#include <unordered_map>
#include "CharStringLink.h"
#include <iostream>

unsigned int countHash(const wchar_t* str)
{
	unsigned int hash = 1315423911;
	while (*str)
	{
		hash ^= ((hash << 5) + (*str++) + (hash >> 2));
	}
	return (hash & 0x7FFFFFFF);
}

class StrHash
{
public:
	size_t operator()(const CharString& str)const
	{
		return countHash(str.getData());
	}
};

class StrCompare
{
public:
	bool operator()(const CharString & a, const CharString & b)const
	{
		return wcscmp(a.getData(), b.getData());
	}
};

class hashTable
{
private:
	CharStringLink wordsList;
	unordered_map<CharString, int, StrHash, StrCompare> StrMap;
public:
	hashTable(){}
	~hashTable(){}
public:
	void insertString(const CharString & stringToInsert);
	int findString(const CharString& stringToFind) const;

};
