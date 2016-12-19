#include <stdio.h>
#include <time.h>
#include "stdafx.h"
#include "Functions.h"
#include "Stack.cpp"
#include "AVL.h"
#include "AVL.cpp"
#include "FileChain.h"
#include <io.h>
#define MAX_FILE_NUM 1000

using namespace std;

void qsort(int low, int high, int* quene1, int* quene2)
{
	if (low >= high)
		return;
	int i = low;
	int j = high;
	int mid = quene1[i];
	int mid2 = quene2[i];
	while (i < j)
	{
		while (i < j && quene1[j] <= mid)
			j--;
		quene1[i] = quene1[j];
		quene2[i] = quene2[j];
		while (i < j && quene1[i] >= mid)
			i++;
		quene1[j] = quene1[i];
		quene2[j] = quene2[i];
	}
	quene1[i] = mid;
	quene2[i] = mid2;
	qsort(i + 1, high, quene1, quene2);
	qsort(low, j - 1, quene1, quene2);
}

FileInfo extractInfo(const char* fileName)
{
	FileInfo fileInformation;
	fileInformation.author = L"";
	fileInformation.question = L"";
	fileInformation.text = L"";
	fileInformation.title = L"";
	string textLine = "";
	CharString FileText = L"";
	char tmpFileName[100];
	sprintf_s(tmpFileName, 100, "input\\%s", fileName);
	ifstream inputFile(tmpFileName);
	while (getline(inputFile, textLine))
	{
		CharString tmpString;
		tmpString = textLine.c_str();
		FileText = FileText + tmpString;
	}
	inputFile.close();
	inputFile.clear();

	CharStringLink textLink;
	int i = 0;
	while (i < FileText.getLength())
	{
		CharString tmpString;
		if (FileText[i] == L'<')
		{
			int pos = FileText.indexOf(L">", i);
			tmpString = FileText.substring(i, pos);
			CharString tmpTagName = L"";
			CharString tmpClassName = L"";
			int tagtype;
			
			if (tmpString.indexOf(L"</", 0) != -1)
			{
				tagtype = 1;
				tmpTagName = tmpString.substring(2, tmpString.getLength() - 2);
			}
			else
			{
				tagtype = 0;
				int spacePos = tmpString.indexOf(L" ", 0);
				if (spacePos != -1)
				{
					tmpTagName = tmpString.substring(1, spacePos - 1);
				}
				else
				{
					tmpTagName = tmpString.substring(1, tmpString.getLength() - 2);
				}
			}
			int classPos = tmpString.indexOf(L"class", 0);
			if (classPos != -1 && classPos != 1 &&
				(tmpString[classPos - 1] == L' ' || tmpString[classPos - 1] == L'\"')
				&& (tmpString[classPos + 5] == L' ' || tmpString[classPos + 5] == L'='))
			{
				int classNameStart = tmpString.indexOf(L"\"", classPos) + 1;
				int classNameEnd = tmpString.indexOf(L"\"", classNameStart) - 1;
				tmpClassName = tmpString.substring(classNameStart, classNameEnd);
			}
			textLink.add(tmpString, 0, 0, 1, tagtype, tmpTagName, tmpClassName);
			i = pos + 1;
		}
		else
		{
			int pos = FileText.indexOf(L"<", i);
			tmpString = FileText.substring(i, pos - 1);
			i = pos;
			textLink.add(tmpString);
		}
	}
	CharStringNode *p = textLink.getData();
	int length = textLink.getLength();
	int k = 0;
	while (k < length)
	{
		if (p->NodeType == 1 && p->TagType == 0)
		{
			if (p->className == L"author")
			{
				CharString tempTagName = p->tagName;
				CharString tmpText = L"";
				int count = 1;
				while (count != 0)
				{
					p = p->next;
					k++;
					if (p->NodeType == 0)
						tmpText = tmpText + p->data;
					else
					{
						if (p->tagName == tempTagName)
						{
							if (p->TagType == 0)
								count++;
							else
								count--;
						}
					}
				}
				while (!((tmpText.getData()[tmpText.getLength() - 1] >= 19968 && tmpText.getData()[tmpText.getLength() - 1] <= 40869)
					|| (tmpText.getData()[tmpText.getLength() - 1] >= 65 && tmpText.getData()[tmpText.getLength() - 1] <= 90)
					|| (tmpText.getData()[tmpText.getLength() - 1] >= 97 && tmpText.getData()[tmpText.getLength() - 1] <= 122)
					))
					tmpText = tmpText.substring(0, tmpText.getLength() - 2);
				if (fileInformation.questionCount > 1)
					fileInformation.author = fileInformation.author + L"\\";
				fileInformation.author = fileInformation.author + tmpText;
				p = p->next;
				k++;
			}
			else if (p->className == L"headline-title")
			{
				CharString tempTagName = p->tagName;
				CharString tmpText = L"";
				int count = 1;
				while (count != 0)
				{
					p = p->next;
					k++;
					if (p->NodeType == 0)
						tmpText = tmpText + p->data;
					else
					{
						if (p->tagName == tempTagName)
						{
							if (p->TagType == 0)
								count++;
							else
								count--;
						}
					}
				}
				fileInformation.title = fileInformation.title + tmpText;
				p = p->next;
				k++;
			}
			else if (p->className == L"question-title")
			{
				fileInformation.questionCount++;
				CharString tempTagName = p->tagName;
				CharString tmpText = L"";
				int count = 1;
				while (count != 0)
				{
					p = p->next;
					k++;
					if (p->NodeType == 0)
						tmpText = tmpText + p->data;
					else
					{
						if (p->tagName == tempTagName)
						{
							if (p->TagType == 0)
								count++;
							else
								count--;
						}
					}
				}
				if (fileInformation.questionCount > 1)
					fileInformation.question = fileInformation.question + L"\\";
				fileInformation.question = fileInformation.question + tmpText;
				p = p->next;
				k++;
			}
			else if (p->className == L"view-more")
			{
				p = p->next;
				k++;
				CharString tmpText = L"";
				int tempPos = p->data.indexOf(L"href=", 0);
				tempPos = p->data.indexOf(L"\"", tempPos);
				tmpText = p->data.substring(tempPos + 1, p->data.getLength() - 3);
				if (fileInformation.questionCount > 1)
					fileInformation.fileLink = fileInformation.fileLink + L"\\";
				fileInformation.fileLink = fileInformation.fileLink + tmpText;
				p = p->next;
				k++;
			}
			else if (p->className == L"content")
			{
				CharString tempTagName = p->tagName;
				CharString tmpText = L"";
				int count = 1;
				while (count != 0)
				{
					p = p->next;
					k++;
					if (p->NodeType == 0)
						tmpText = tmpText + p->data;
					else
					{
						if (p->tagName == tempTagName)
						{
							if (p->TagType == 0)
								count++;
							else
								count--;
						}
						else if (p->tagName == L"p" && p->TagType == 1)
							tmpText = tmpText + L"\n";
					}
				}
				CharString tmpString = L"客官，这篇文章有意思吗";
				if (tmpText.indexOf(tmpString, 0) == -1)
				{
					if (fileInformation.questionCount > 1)
						fileInformation.text = fileInformation.text + L"\\";
					fileInformation.text = fileInformation.text + tmpText;
				}
				p = p->next;
				k++;
			}
			else
			{
				p = p->next;
				k++;
			}
		}
		else
		{
			p = p->next;
			k++;
		}
	}
	if (fileInformation.fileLink.getLength() == 0)
	{
		CharStringNode* p = textLink.getData();
		int i = 0;
		while (i < textLink.getLength())
		{
			if (p->className == L"view-more")
			{
				p = p->next;
				i++;
				CharString tmpText = L"";
				int tempPos = p->data.indexOf(L"href=", 0);
				tempPos = p->data.indexOf(L"\"", tempPos);
				tmpText = p->data.substring(tempPos + 1, p->data.getLength() - 3);
				if (fileInformation.questionCount > 1)
					fileInformation.fileLink = fileInformation.fileLink + L"\\";
				fileInformation.fileLink = fileInformation.fileLink + tmpText;
				p = p->next;
				i++;
			}
			else
			{
				p = p->next;
				i++;
			}
		}
	}

	return fileInformation;
}

void initDictionary(char * fileName, dicTree & newDicTree)
{
	string words;
	ifstream inputDic(fileName);
	while (getline(inputDic, words))
	{
		CharString tmpString;
		tmpString = words.c_str();
		if (tmpString[0] == wchar_t(65279))
		{
			tmpString.substring(1, tmpString.getLength() - 1);
			tmpString = tmpString.substring(1, tmpString.getLength() - 1);
		}
		newDicTree.insertString(tmpString);
	}
	inputDic.close();
}

void divideWords(const CharString & fileText, dicTree* Dic, CharStringLink & ansLink)
{
	if (fileText.getLength() == 0)
		return;
	CharString textPart1 = L"";
	dicTree foundWords;
	int strBegin = 0;
	int strEnd = 0;
	int tmpEnd = 0;
	textPart1 = fileText.substring(strBegin, strEnd);

	int findResult;
	while (true)
	{
		findResult = Dic->findString(textPart1);
		if (findResult != 0)
		{
			if (findResult == 2)
			{
				strEnd = tmpEnd;
			}
			tmpEnd++;
			textPart1 = fileText.substring(strBegin, tmpEnd);
			while ((tmpEnd < fileText.getLength()) && ((findResult = Dic->findString(textPart1)) != 0))
			{
				if (findResult == 2)
					strEnd = tmpEnd;
				tmpEnd++;
				if (tmpEnd >= (fileText.getLength()))
					break;
				textPart1 = fileText.substring(strBegin, tmpEnd);
			}
			textPart1 = fileText.substring(strBegin, strEnd);
			foundWords.insertString(textPart1);
		}
		strBegin = strEnd + 1;
		strEnd = strBegin;
		tmpEnd = strBegin;
		if (strBegin > (fileText.getLength() - 1))
			break;
		textPart1 = fileText.substring(strBegin, strEnd);
	}

	struct recordNode
	{
		trieNode* curNode;
		CharString curString;
	};

	Stack<recordNode> ansStack;

	recordNode startNode;
	startNode.curNode = foundWords.getRoot();
	startNode.curString = L"";
	ansStack.push(startNode);
	while (!ansStack.isEmpty())
	{
		recordNode topNode = ansStack.top();
		ansStack.pop();
		if (topNode.curNode->isWordEnd == 2)
		{
			CharString tmpString;
			tmpString = topNode.curString + topNode.curNode->character;
			ansLink.add(tmpString, topNode.curNode->freq, topNode.curNode->isWordEnd);
		}

		unordered_map<wchar_t, trieNode>::iterator it;
		for (it = topNode.curNode->list.begin(); it != topNode.curNode->list.end(); it++)
		{
			recordNode tmpNode;
			tmpNode.curNode = &it->second;
			tmpNode.curString = topNode.curString + topNode.curNode->character;
			ansStack.push(tmpNode);
		}
	}
}

void addToAVLTree(AVLTree<FileChain>& tree, CharStringLink * divideresult, FileInfo* file)
{
	CharStringNode * p = divideresult->getData(), *root = divideresult->getData();
	FileChain tempFileChainNode;
	TreeNode<FileChain>* pFileNode = NULL;
	do
	{
		tempFileChainNode.words = p->data;
		tree.insert(tempFileChainNode);
		pFileNode = tree.search(tempFileChainNode);
		pFileNode->data.addFile(file, p->Freq);
		p = p->next;
	} while (p != root);
}

void getFiles(DirInfo* dir)
{
	intptr_t hFile = 0;
	struct _finddata_t fileInfo;
	const char *toSearch = "input\\*.html";
	hFile = _findfirst(toSearch, &fileInfo);
	if (hFile != -1)
	{
		dir->fileNames[dir->filesNum] = new char[128];
		strcpy_s(dir->fileNames[dir->filesNum], 128, fileInfo.name);
		dir->filesNum++;
		while (!_findnext(hFile, &fileInfo))
		{
			dir->fileNames[dir->filesNum] = new char[128];
			strcpy_s(dir->fileNames[dir->filesNum], 128, fileInfo.name);
			dir->filesNum++;
		}
		_findclose(hFile);
	}
}

void work(int type)
{
	wcin.imbue(locale(locale(), "", LC_CTYPE));
	wcout.imbue(locale(locale(), "", LC_CTYPE));
	DirInfo *dir = new DirInfo;
	wofstream outputFile;
	AVLTree<FileChain> avlSearchTree;
	outputFile.imbue(locale(locale(), "", LC_CTYPE));
	dir->fileNames = new char*[MAX_FILE_NUM];
	dir->filesNum = 0;
	getFiles(dir);
	dicTree Dictionary;
	initDictionary("词库.dic", Dictionary);
	system("md output");
	cout << endl << endl;
	FileInfo* fileQuene = new FileInfo[dir->filesNum];
	
	char outputFileInfo[100];
	char outputFileTxt[100];
	char outputFileName[100];
	char outputFileInfoName[100];
	for (int i = 0; i < dir->filesNum; i++)
	{
		CharStringLink divideResult;
		fileQuene[i] = extractInfo(dir->fileNames[i]);
		fileQuene[i].fileID = i;

		divideWords(fileQuene[i].text, &Dictionary, divideResult);


		addToAVLTree(avlSearchTree, &divideResult, &fileQuene[i]);

		cout << int(double(i) / dir->filesNum * 100) << endl << endl;

		strncpy_s(outputFileName, 100, dir->fileNames[i], strlen(dir->fileNames[i]) - 5);
		sprintf_s(outputFileInfo, 100, "%s%s%s", "output\\", outputFileName, ".info");
		sprintf_s(outputFileInfoName, 100, "%s%s", outputFileName, ".info");
		CharString tempOutputFileName(outputFileName, 1);
		fileQuene[i].fileName = tempOutputFileName;
		sprintf_s(outputFileTxt, 100, "%s%s%s", "output\\", outputFileName, ".txt");
		outputFile.open(outputFileInfo, ios::out|ios::trunc);
		outputFile << fileQuene[i].title << endl << fileQuene[i].fileLink << endl << fileQuene[i].question << endl << fileQuene[i].author << endl << fileQuene[i].text;
		outputFile.close();
		outputFile.open(outputFileTxt, ios::out|ios::trunc);
		if (divideResult.getLength() > 0)
			divideResult.print(outputFile);
		outputFile.close();

	}
	wcout << L"Engine_is_ready" << endl << endl;
	wofstream logfile;
	logfile.open("result.txt", ios::trunc|ios::out);
	logfile.imbue(locale(locale(), "", LC_CTYPE));
	ifstream queryfile;
	if (type == 0)
		queryfile.open("query.txt", ios::in);

	string buffer;
	char bufferChar[100];
	while (1)
	{
		if (type == 1)
			getline(cin, buffer);
		else
		{
			if (queryfile.eof())
			{
				wcout << L"Server_is_done" << endl;
				break;
			}
			getline(queryfile, buffer);
		}
		strcpy_s(bufferChar, 100, buffer.c_str());
		CharString searchString(bufferChar, 1);

		logfile << searchString << L" ";
		if (searchString == L":exit")
		{
			wcout << L"Server_is_done" << endl << endl;
			break;
		}
		TreeNode<FileChain>* ans;
		FileChain tempChainForSearch;
		int pos = searchString.indexOf(L" ", 0);
		if (pos == -1)
		{
			tempChainForSearch.words = searchString;
			ans = avlSearchTree.search(tempChainForSearch); 
			if (ans != NULL)
			{
				wcout << searchString << L"|-|-";
				ans->data.printChain();
				ans->data.printChain(logfile);
			}
			else
			{
				wcout << L"没有找到相关信息" << endl << endl;
				logfile << L"没有找到相关信息" << endl;
			}
		}
		else
		{
			CharString searchKeyWords = searchString;
			CharString list[100];
			int count = 0;
			while (pos > 0)
			{
				list[count] = searchString.substring(0, pos - 1);
				searchString = searchString.substring(pos + 1, searchString.getLength());
				pos = searchString.indexOf(L" ", 0);
				count++;
			}
			list[count] = searchString;
			count++;
			int wordsTotFreq[MAX_FILE_NUM];
			int wordsTotType[MAX_FILE_NUM];
			int fileIndex[MAX_FILE_NUM];
			memset(wordsTotFreq, 0, sizeof(int) * MAX_FILE_NUM);
			memset(wordsTotType, 0, sizeof(int) * MAX_FILE_NUM);
			for (int i = 0; i < 1000; i++)
				fileIndex[i] = i;

			for (int i = 0; i < count; i++)
			{
				tempChainForSearch.words = list[i];
				ans = avlSearchTree.search(tempChainForSearch);
				if (ans != NULL)
				{
					FileNode *p = ans->data.root;
					for (int j = 0; j < ans->data.fileCount; j++)
					{
						wordsTotFreq[p->fileInfo->fileID] += p->keyWordsFreq;
						wordsTotType[p->fileInfo->fileID]++;
						p = p->next;
					}
				}
			}
			qsort(0, MAX_FILE_NUM - 1, wordsTotType, fileIndex);
			bool isnoneRes = true;
			for (int i = 0; i < MAX_FILE_NUM; i++)
			{
				if (wordsTotFreq[fileIndex[i]] != 0)
				{
					if (isnoneRes)
					{
						wcout << searchKeyWords << L"|-|-";
						isnoneRes = false;
					}
					wcout << fileQuene[fileIndex[i]].fileID << L"|+|+" << wordsTotFreq[fileIndex[i]] << L"|+|+" << fileQuene[fileIndex[i]].fileName
						<< L"|-|-";
					logfile << L"(" << fileQuene[fileIndex[i]].fileID << L"," << wordsTotFreq[fileIndex[i]]
						<< L")";
				}
			}
			if (isnoneRes)
			{
				wcout << L"没有找到相关信息";
				logfile << L"没有找到相关信息";
			}
			wcout << endl << endl;
			logfile << endl;
		}
	}
	logfile.close();

	for (int i = 0; i < dir->filesNum; i++)
	{
		delete[] dir->fileNames[i];
	}
	delete[] dir->fileNames;
	delete[] fileQuene;
	delete dir;
	return;
}