
#include "stdafx.h"
#include "FileChain.h"

void FileChain::addFile(FileInfo* fileinfo, int keywordsfreq)
{
	if (root == NULL)
	{
		root = new FileNode;
		root->setFile(fileinfo, 1, keywordsfreq);
		fileCount = 1;
	}
	else
	{
		FileNode *p = root;
		while (p->next != NULL)
		{
			p = p->next;
		}
		FileNode *q = new FileNode;
		fileCount++;
		q->setFile(fileinfo, fileCount, keywordsfreq);
		p->next = q;
	}
}

void FileNode::setFile(FileInfo* fileinfo, int fileid, int keywordsfreq)
{
	fileInfo = fileinfo;
	keyWordsFreq = keywordsfreq;
	fileID = fileid;
}

FileNode* FileChain::searchFile(FileInfo fileinfo)
{
	FileNode* p = root;
	while (p != NULL)
	{
		if (*p->fileInfo == fileinfo)
			return p;
		p = p->next;
	}
	return NULL;
}

void FileChain::remove(int fileID)
{
	FileNode* p = root, *q = root;
	for (int i = 0; i < fileCount; i++)
	{
		if (p == NULL)
			return;
		if (p->fileID == fileID)
		{
			q->next = p->next;
			delete p;
			return;
		}
		q = p;
		p = p->next;
	}
}

void FileChain::edit(int fileID, FileInfo newfileinfo)
{
	FileNode* p = root;
	for (int i = 0; i < fileCount; i++)
	{
		if (p == NULL)
			return;
		if (p->fileID == fileID)
		{
			*p->fileInfo = newfileinfo;
			return;
		}
		p = p->next;
	}
}

bool FileChain::operator==(const FileChain & filechaintocmp)
{
	if (words == filechaintocmp.words)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool FileChain::operator<(const FileChain & filechaintocmp)
{
	if (words < filechaintocmp.words)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool FileChain::operator>(const FileChain & filechaintocmp)
{
	if (words > filechaintocmp.words)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void FileChain::printChain()
{
	FileNode* p = root;
	wcout.imbue(locale(locale(), "", LC_CTYPE));
	while (p != NULL)
	{
		wcout << p->fileInfo->fileID << L"|+|+" << p->keyWordsFreq
			<< L"|+|+" << p->fileInfo->fileName
			<< L"|-|-";
		p = p->next;
	}
	wcout << endl << endl;
}

void FileChain::printChain(wostream & outputstream)
{
	FileNode* p = root;
	outputstream.imbue(locale(locale(), "", LC_CTYPE));
	while (p != NULL)
	{
		outputstream << L"(" << p->fileInfo->fileID << L","<< p->keyWordsFreq
			<< L")";
		p = p->next;
	}
	outputstream << endl;
}
