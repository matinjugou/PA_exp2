#ifndef CHARSTRINGLINK_H
#define CHARSTRINGLINK_H

#include "CharString.h"

struct CharStringNode
{
	CharString* data;
	CharStringNode* next;
	CharStringNode* last;
	CharString tagName;
	CharString className;
	int NodeType;		//0-���ģ�1-��ǩ
	int TagType;		//0-��ʼ��ǩ��1-������ǩ��2-�Ապϱ�ǩ
	int freq;
	int isWordEnd;
};

class CharStringLink
{
private:
	int length;
	CharStringNode* data;
public:
	CharStringLink();
	~CharStringLink();
public:
	CharStringNode* getData();
	void add(CharString* stringToAdd);
	void add(const CharString & stringToAdd);
	void CharStringLink::add(CharString * stringToAdd, int frequency);
	void CharStringLink::add(const CharString  & stringToAdd, int frequency);
	void remove(CharString* stringToRemove);
	CharString* search(CharString* stringToFind);
	void print();
	void print(wostream & outputStream);
	CharStringNode* operator[](int index) const;
	int getLength();
};

#endif
