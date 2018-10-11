#include "pch.h"
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include "Paper.h"
#include "FileIO.h"

void FileIO::readFile(vector<Paper> &fileContent, const char *inFilePath, bool showInConsole)
{
	FILE *fp = NULL;
	fopen_s(&fp, inFilePath, "r");
	if (fp == NULL)
	{
		throw("读取文件时文件打开失败");
	}
	int _charNum = 0;
	char c = 0;
	string titleBuf, abstractBuf;
	while (true)
	{
		c = fgetc(fp);
		if (c >= '0' && c <= '9')
		{
			while ((c = fgetc(fp)) != '\n');// paper id

			while ((c = fgetc(fp)) != ' '); // "Title: "
			titleBuf.clear();
			while (c != '\n')				// 获取title内容
			{
				c = fgetc(fp);
				titleBuf += c;
				++_charNum;
			}
			transform(titleBuf.begin(), titleBuf.end(), titleBuf.begin(), tolower);

			while ((c = fgetc(fp)) != ' '); // "Abstract: "
			abstractBuf.clear();
			while (true)					// 获取abstract内容
			{
				c = fgetc(fp);
				if (c == '\n')
				{
					++_charNum;
					abstractBuf += c;
					break;
				}
				else if (c == EOF)
				{
					break;
				}
				else
				{
					++_charNum;
					abstractBuf += c;
				}
			}
			transform(abstractBuf.begin(), abstractBuf.end(), abstractBuf.begin(), tolower);

			fileContent.push_back(Paper(titleBuf, abstractBuf));
		}
		if (c == EOF)
			break;
	}
	if (fp)
	{
		fclose(fp);
	}

	//***********************************************************
	// 在控制台显示读取的字符数，用于调试
	//printf("std char number: %d\n", _charNum);
	//***********************************************************
	// 在控制台显示读取的文本内容，用于调试
	if (showInConsole)
	{
		for (unsigned int i = 0; i < fileContent.size(); i++)
		{
			printf("%d\n", i);
			printf("Title: %s", fileContent[i].title.c_str());
			printf("Abstract: %s", fileContent[i].abstract.c_str());
			if (i != fileContent.size() - 1)
				printf("\n\n");
		}
	}
	//***********************************************************
}

void FileIO::writeResult(int charNum, int wordNum, int lineNum, vector<unordered_map<string, int>::iterator> &topPhrase, const char *outFilePath, bool showInConsole)
{
	//***********************************************************
	// 输出到控制台，用于调试
	if (showInConsole)
	{
		printf("characters: %d\n", charNum);
		printf("words: %d\n", wordNum);
		printf("lines: %d\n", lineNum);
		for (unsigned int i = 0; i < topPhrase.size(); i++)
		{
			printf("<%s>: %d\n", topPhrase[i]->first.c_str(), topPhrase[i]->second);
		}
	}
	//***********************************************************
	// 输出到文件
	FILE *fp = NULL;
	fopen_s(&fp, outFilePath, "w");
	if (fp == NULL)
	{
		throw "写入文件时文件打开失败";
	}
	fprintf(fp, "characters: %d\n", charNum);
	fprintf(fp, "words: %d\n", wordNum);
	fprintf(fp, "lines: %d\n", lineNum);
	for (unsigned int i = 0; i < topPhrase.size(); i++)
	{
		fprintf(fp, "<%s>: %d\n", topPhrase[i]->first.c_str(), topPhrase[i]->second);
	}
	if (fp)
	{
		fclose(fp);
	}
}