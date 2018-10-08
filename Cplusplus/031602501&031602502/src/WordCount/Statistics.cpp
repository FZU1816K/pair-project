#include "pch.h"
#include <iostream>
using namespace std;
#include <vector>
#include <string>
#include <stdio.h>
#include <unordered_map>
#include <algorithm>
#include "Paper.h"
#include <list>
#include "Statistics.h"

Statistics::Statistics(vector<Paper> &fileContent, bool useTitleWeight, int phraseLen)
	:m_fileContent(fileContent),
	m_charNum(0), m_wordNum(0), m_lineNum(0), m_calculated(false),
	m_useTitleWeight(useTitleWeight), m_phraseLen(phraseLen){}

int Statistics::getCharNumber()			// 获取字符个数
{
	if (!m_calculated)					// 判断是否进行过统计功能，若已统计过，则直接返回结果，避免重复计算
		calcAll();						// 对于get方法均如此
	return m_charNum;
}

int Statistics::getWordNumber()			// 获取单词个数
{
	if (!m_calculated)
		calcAll();
	return m_wordNum;
}

int Statistics::getLineNumber()			// 获取获取行数
{
	if (!m_calculated)
		calcAll();
	return m_lineNum;
}

vector<unordered_map<string, int>::iterator> &Statistics::getTopPhrase(int topNum)//获取最高频的n个词组
{
	if (!m_calculated)
		calcAll();
	topNum = min(topNum, int(m_phraseMap.size()));
	for (int i = 0; i < topNum; i++)
	{
		unordered_map<string, int>::iterator maxit = m_phraseMap.begin();
		for (unordered_map<string, int>::iterator it = m_phraseMap.begin(); it != m_phraseMap.end(); it++)
		{
			if (it->second > maxit->second || it->second == maxit->second && it->first < maxit->first)
			{
				maxit = it;
			}
		}
		m_topPhrase.push_back(maxit);
		maxit->second = -maxit->second;
	}
	for (unsigned int i = 0; i < m_topPhrase.size(); i++)
	{
		m_topPhrase[i]->second = -m_topPhrase[i]->second;
	}
	return m_topPhrase;
}

unordered_map<string, int> Statistics::_getAllPhrase()	// 获取所有词组，用于调试
{
	return m_phraseMap;
}

bool Statistics::isLetter(char &c)						//判断给定字符是否为字母
{
	return c >= 'a' && c <= 'z';
}

bool Statistics::isNumber(char &c)						//判断给定字符是否为数字
{
	return c >= '0' && c <= '9';
}

void Statistics::calcString(string &str, int weight)	// 对给定字符串执行统计功能
{
	unsigned int i = 0;
	char c;
	string wordBuf = "";								// 单词缓存
	list<string> phraseBuf;								// 词组缓存队列
	string separatorBuf = "";							// 分隔符缓存
	bool isLine = false;

	while (i < str.size())
	{
		c = str[i];
		if (c > 32)
		{
			isLine = true;
		}
		if (isLetter(c))								// 如果是字母，向后找到分隔符为止
		{
			wordBuf.clear();
			wordBuf += c;
			i++;
			while (i < str.size() && ((isLetter(str[i])) || (isNumber(str[i])))) //向后找到分隔符为止
			{
				wordBuf += str[i];
				i++;
			}
			if (wordBuf.size() >= 4 && isLetter(wordBuf[0]) && isLetter(wordBuf[1]) && isLetter(wordBuf[2]) && isLetter(wordBuf[3]))
			{
				m_wordNum++;
				phraseBuf.push_back(separatorBuf);		// 将分隔符压入词组缓存
				phraseBuf.push_back(wordBuf);			// 将单词压入词组缓存
				separatorBuf.clear();
				wordBuf.clear();
				if (int(phraseBuf.size()) == m_phraseLen * 2)//压入时，单词、分隔符成对压入，所以是2倍
				{
					phraseBuf.pop_front();				// 弹出分隔符。
					string thisPhrase;
					for (list<string>::iterator it = phraseBuf.begin(); it != phraseBuf.end(); it++)
					{									// 遍历词组缓存队列，取出词组
						thisPhrase += *it;
					}
					m_phraseMap[thisPhrase] += weight;	// 在map中进行个数统计
					phraseBuf.pop_front();				// 弹出单词
				}
			}
			else
			{
				phraseBuf.clear();
				separatorBuf.clear();
			}
		}
		else if (isNumber(c))							// 如果是数字，清空缓存，向后找到分隔符为止
		{
			phraseBuf.clear();
			separatorBuf.clear();
			for (i++; i < str.size() && ((isLetter(str[i])) || (isNumber(str[i]))); i++);
		}
		else
		{												// 如果是分隔符
			separatorBuf += c;
			i++;
		}
	}
	if (isLine)
	{
		m_lineNum++;
	}
}

void Statistics::calcAll()								// 对给定的所有文本内容fileContent执行统计功能
{
	for (unsigned int i = 0; i < m_fileContent.size(); i++)
	{
		calcString(m_fileContent[i].title, m_useTitleWeight ? 10 : 1);
		calcString(m_fileContent[i].abstract, 1);
		
		m_charNum += int(m_fileContent[i].title.size()) + int(m_fileContent[i].abstract.size());
	}
	m_calculated = true;								// 已经执行过统计功能，将标记置为true
}
