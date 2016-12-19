#include "hashtable.h"

void hashTable::insertString(const CharString & stringToInsert)
{
	std::unordered_map<CharString, int, StrHash, StrCompare>::const_iterator got = StrMap.find(stringToInsert);
	if (got != StrMap.end())
	{
		wordsList[got->second]->freq++;
	}
	else
	{
		wordsList.add(stringToInsert);
		StrMap[stringToInsert] = wordsList.getLength() - 1;
	}
}

int hashTable::findString(const CharString & stringToFind) const
{
	std::unordered_map<CharString, int, StrHash, StrCompare>::const_iterator got = StrMap.find(stringToFind);
	if (got != StrMap.end())
	{
	}
	else
	{
	}
}
