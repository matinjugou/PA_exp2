#pragma once
#include "CharString.h"
struct CharStringNode
{
	CharString data;
	int Freq;
	int isWordEnd;
	CharStringNode* next;
	CharStringNode* last;
	CharString tagName;
	CharString className;
	int NodeType;		//0-���ģ�1-��ǩ
	int TagType;		//0-��ʼ��ǩ��1-������ǩ��2-�Ապϱ�ǩ
};

class CharStringLink
{
private:
	CharStringNode* data;
	int length;
public:
	CharStringLink();
	~CharStringLink();
public:
	void CharStringLink::add(CharString & stringToAdd, int freq = 0, int iswordend = 0, int nodetype = 0, int tagtype = 0,
		CharString tagname = L"", CharString classname = L"");
	void remove(CharString & stringToRemove);
	CharStringNode* search(CharString & stringToFind);
	void print(wostream & outputStream);
	CharStringNode* operator[](int index);
	int getLength();
	CharStringNode* getData();
};