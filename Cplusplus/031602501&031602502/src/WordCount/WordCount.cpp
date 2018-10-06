#include "pch.h"
#include <iostream>
#include <string>
#include <windows.h>
#include <string.h>
#include <vector>
#include <unordered_map>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include "ArgProcessing.h"
#include "FileIO.h"
#include "Statistics.h"
using namespace std;

// 显示文件内容到控制台
#define DIS_FILE_CONTENT_TO_CONSOLE false

// 显示结果到控制台
#define DIS_RESULT_TO_CONSOLE true

int main(int argc, char *argv[])
{
	try {
		ArgProcessing arg(argc, argv);
		vector<Paper> fileContent;
		FileIO::readFile(fileContent, arg.getArgiInFilePath(), DIS_FILE_CONTENT_TO_CONSOLE);
		Statistics st(fileContent, arg.getArgwUseTitleWeight(), arg.getArgmPhraseLen());
		int charNum = st.getCharNumber();
		int wordNum = st.getWordNumber();
		int lineNum = st.getLineNumber();
		vector<unordered_map<string, int>::iterator> &topPhrase = st.getTopPhrase(arg.getArgnTopNum());
		FileIO::writeResult(charNum, wordNum, lineNum, topPhrase, arg.getArgoOutFilePath(), DIS_RESULT_TO_CONSOLE);

	}
	catch (const char *err)
	{
		printf("%s\n", err);
	}

	//system("pause");
	return 0;
}
