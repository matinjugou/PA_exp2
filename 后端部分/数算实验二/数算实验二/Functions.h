#pragma once
#include "Stack.h"
#include "CharString.h"
#include "newCharStringLink.h"
#include "newTrie.h"
#include "FileInfo.h"
#include "AVL.h"
#include "FileChain.h"
#include <Windows.h>
#include <string>
#include <fstream>

using namespace std;

struct DirInfo
{
	char** fileNames;
	int filesNum;
};

void work(int type);

void getFiles(DirInfo* dir);

FileInfo extractInfo(const char* fileName);

void initDictionary(char* fileName, dicTree & newDicTree);

void divideWords(const CharString& fileText,dicTree* Dic, CharStringLink & ansLink);

void addToAVLTree(AVLTree<FileChain> & tree, CharStringLink* divideResult, FileInfo* file);