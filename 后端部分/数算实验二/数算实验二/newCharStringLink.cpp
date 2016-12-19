#include "newCharStringLink.h"

CharStringLink::CharStringLink()
{
	data = NULL;
	length = 0;
}

CharStringLink::~CharStringLink()
{
	CharStringNode *p = data, *q = p;
	for (int i = 0; i < length; i++)
	{
		p = p->next;
		delete q;
		q = p;
	}
}

void CharStringLink::add(CharString & stringToAdd, int freq, int iswordend, int nodetype, int tagtype,
	CharString tagname, CharString classname)
{
	CharStringNode* newNode = new CharStringNode;
	newNode->data = stringToAdd;
	newNode->Freq = freq;
	newNode->isWordEnd = iswordend;
	newNode->NodeType = nodetype;
	newNode->tagName = tagname;
	newNode->TagType = tagtype;
	newNode->className = classname;
	if (length == 0)
	{
		data = newNode;
		data->next = data;
		data->last = data;
		length++;
	}
	else
	{
		newNode->next = data;
		newNode->last = data->last;
		data->last->next = newNode;
		data->last = newNode;
		length++;
	}
}

void CharStringLink::remove(CharString & stringToRemove)
{
	if (length == 0)
		return;
	CharStringNode *p = NULL;
	if ((p = search(stringToRemove)) == NULL)
	{
		return;
	}
	else
	{
		if (length == 1)
		{
			delete data;
			data = NULL;
			length = 0;
		}
		else
		{
			p->last->next = p->next;
			p->next->last = p->last;
			delete p;
		}
	}
}

CharStringNode* CharStringLink::search(CharString & stringToFind)
{
	if (length == 0)
		return NULL;
	CharStringNode *p = data;
	for (int i = 0; i < length; i++)
	{
		if (p->data == stringToFind)
			return p;
		else
			p = p->next;
	}
	return NULL;
}

void CharStringLink::print(wostream & outputStream = wcout)
{
	CharStringNode *p = data;
	outputStream.imbue(locale(locale(), "", LC_CTYPE));
	for (int i = 0; i < length; i++)
	{
		outputStream << p->data << L" " << p->Freq << endl;
		p = p->next;
	}
}

CharStringNode* CharStringLink::operator[](int index)
{
	if (index >(length - 1))
		return NULL;
	CharStringNode* p = data;
	for (int i = 0; i < index - 1; i++)
	{
		p = p->next;
	}
	return p;
}

int CharStringLink::getLength()
{
	return length;
}

CharStringNode* CharStringLink::getData()
{
	return data;
}