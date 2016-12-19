#pragma once

#include "FileInfo.h"
#include <iostream>
#include <io.h>

using namespace std;

class FileNode
{
public:
	int fileID;
	int keyWordsFreq;
	FileInfo* fileInfo;
	FileNode* next;
public:
	FileNode():fileInfo(NULL), fileID(-1), keyWordsFreq(0), next(NULL){}
	~FileNode(){}
public:
	void setFile(FileInfo* fileinfo, int fileid, int keywordsfreq);
};

class FileChain
{
public:
	int fileCount;
	CharString words;
	FileNode* root;
public:
	FileChain():root(NULL), words(L""){}
	~FileChain()
	{
		FileNode *p = root, *q = p;
		while (p != NULL)
		{
			q = p;
			p = p->next;
			delete q;
		}
	}
public:
	void addFile(FileInfo* fileinfo, int keywordsfreq);
	FileNode* searchFile(FileInfo fileinfo);
	void remove(int fileID);
	void edit(int fileID, FileInfo newfileinfo);
	bool operator==(const FileChain & filechaintocmp);
	bool operator<(const FileChain & filechaintocmp);
	bool operator>(const FileChain & filechaintocmp);
	void printChain();
	void printChain(wostream & outputstream);
};