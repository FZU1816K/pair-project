#include "pch.h"
#include "ArgProcessing.h"
#include <iostream>
using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ArgProcessing::ArgProcessing(int &argc, char *argv[])		// 构造  对参数进行处理
	:m_argc(argc), m_argv(argv),
	m_inFilePath("input.txt"), m_outFilePath("result.txt"),
	m_useTitleWeight(false), m_phraseLen(1), m_topNum(10)
{
	if (m_argc == 1)										//直接启动，使用默认配置，方便调试
	{
		// -i input.txt -o result.txt -w 0
	}
	else if (m_argc > 11 || m_argc < 7 || m_argc % 2 == 0)	//参数个数错误
	{
		throw "参数个数错误";
	}
	else
	{
		bool has_i = false, has_o = false, has_w = false, has_m = false, has_n = false;
		for (int i = 1; i < m_argc; i += 2)
		{
			if (strcmp(m_argv[i], "-i") == 0)
			{
				if (has_i)
					throw  "-i 参数重复";
				has_i = true;
				m_inFilePath = m_argv[i + 1];
			}
			else if (strcmp(m_argv[i], "-o") == 0)
			{
				if (has_o)
					throw "-o 参数重复";
				has_o = true;
				m_outFilePath = m_argv[i + 1];
			}
			else if (strcmp(m_argv[i], "-w") == 0)
			{
				if (has_w)
					throw "-w 参数重复";
				if (strlen(m_argv[i + 1]) == 1 && m_argv[i + 1][0] == '0')
				{
					has_w = true;
					m_useTitleWeight = false;
				}
				else if (strlen(m_argv[i + 1]) == 1 && m_argv[i + 1][0] == '1')
				{
					has_w = true;
					m_useTitleWeight = true;
				}
				else
				{
					throw "-w 后参数错误";
				}
			}
			else if (strcmp(m_argv[i], "-m") == 0)
			{
				if (has_m)
					throw "-m 参数重复";
				has_m = true;
				int len = strlen(m_argv[i + 1]);
				for (int j = 0; j < len; j++)
				{
					if (m_argv[i + 1][j] > '9' || m_argv[i + 1][j] < '0')
					{
						throw "-m 后参数错误";
					}
				}
				m_phraseLen = atoi(m_argv[i + 1]);
			}
			else if (strcmp(m_argv[i], "-n") == 0)
			{
				if (has_n)
					throw "-n 参数错误";
				has_n = true;
				int len = strlen(m_argv[i + 1]);
				for (int j = 0; j < len; j++)
				{
					if (m_argv[i + 1][j] > '9' || m_argv[i + 1][j] < '0')
					{
						throw "-n 后参数错误";
					}
				}
				m_topNum = atoi(m_argv[i + 1]);
			}
			else // -不允许的参数
			{
				throw "使用了除-i -o -w -m -n 外的参数 (使用了不允许的参数)";
			}
		}
		if (!has_i || !has_o || !has_w)// -i -o -w 不全
		{
			throw "-i -o -w 不全";
		}
	}
}

const char *ArgProcessing::getArgiInFilePath()		// 获取-i后的参数	输入文件路径
{
	return m_inFilePath;
}

const char *ArgProcessing::getArgoOutFilePath()		// 获取-o后的参数	输出文件路径
{
	return m_outFilePath;
}

bool ArgProcessing::getArgwUseTitleWeight()			// 获取-w参数		是否使用标题10倍权重
{
	return m_useTitleWeight;
}

int ArgProcessing::getArgmPhraseLen()				// 获取-m参数		短语长度
{
	return m_phraseLen;
}

int ArgProcessing::getArgnTopNum()					// 获取-n参数		结果所需单词数
{
	return m_topNum;
}
