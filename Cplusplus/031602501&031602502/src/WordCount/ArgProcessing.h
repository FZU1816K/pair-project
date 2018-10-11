#pragma once
#include "pch.h"
#include <iostream>
using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

class ArgProcessing
{
public:
	ArgProcessing(int &argc, char *argv[]);	// 构造  对参数进行处理
	const char *getArgiInFilePath();		// 获取-i后的参数	输入文件路径
	const char *getArgoOutFilePath();		// 获取-o后的参数	输出文件路径 
	bool getArgwUseTitleWeight();			// 获取-w参数		是否使用标题10倍权重
	int getArgmPhraseLen();					// 获取-m参数		短语长度
	int getArgnTopNum();					// 获取-n参数		结果所需单词数
private:
	int m_argc;								// argc
	char **m_argv;							// argv
	const char *m_inFilePath;				// -i		输入文件路径
	const char *m_outFilePath;				// -o		输出文件路径
	bool m_useTitleWeight;					// -w		是否使用标题10倍权重
	int m_phraseLen;						// -m		短语长度
	int m_topNum;							// -n		结果所需单词数
};

//void ArgProcessingTest(int argc, char *argv[])//专门用于ArgProcessing类的测试函数。传入参数，打印结果到控制台。
//{
//	printf("ArgProcessing test start\n");
//	try
//	{
//		ArgProcessing ap(argc, argv);
//		printf("-i inFilePath:     %s\n", ap.getArgiInFilePath());							//const char *
//		printf("-o outFilePath:    %s\n", ap.getArgoOutFilePath());							//const char *
//		printf("-w useTitleWeight: %s\n", ap.getArgwUseTitleWeight() ? "true" : "false");	//bool
//		printf("-m phraseLen:      %d\n", ap.getArgmPhraseLen());							//int
//		printf("-n topNum:         %d\n", ap.getArgnTopNum());								//int
//	}
//	catch (const char *err)
//	{
//		printf("%s\n", err);
//	}
//	printf("ArgProcessing test end\n");
//}
