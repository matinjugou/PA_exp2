#pragma once
#include "CharString.h"
struct FileInfo
{
	int questionCount;
	int fileID;
	CharString fileName;
	CharString fileLink;
	CharString title;
	CharString author;
	CharString question;
	CharString text;
public:
	FileInfo():fileName(L""), title(L""), author(L""), question(L""), text(L""), fileLink(L""), questionCount(0), fileID(0){}
	bool operator==(const FileInfo & filetocmp)
	{
		if (fileName == filetocmp.fileName)
			if (title == filetocmp.title)
				if (author == filetocmp.author)
					if (question == filetocmp.question)
						if (text == filetocmp.text)
						{
							return true;
						}
		return false;
	}
};