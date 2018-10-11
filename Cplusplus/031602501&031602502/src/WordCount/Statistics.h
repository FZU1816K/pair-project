#pragma once
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

class Statistics
{
public:
	Statistics(vector<Paper> &fileContent, bool useTitleWeight, int phraseLen);
	int getCharNumber();						// 获取字符个数
	int getWordNumber();						// 获取单词个数
	int getLineNumber();						// 获取获取行数
	vector<unordered_map<string, int>::iterator> &getTopPhrase(int topNum);//获取最高频的n个词组
	unordered_map<string, int> _getAllPhrase();	// 获取所有词组，用于调试
private:
	inline bool isLetter(char &c);				// 判断给定字符是否为字母
	inline bool isNumber(char &c);				// 判断给定字符是否为数字
	void calcString(string &str, int weight);	// 对给定字符串执行统计功能
	void calcAll();								// 对给定的所有文本内容fileContent执行统计功能
												// 对于上述的2个方法，不用手动调用。在使用get方法时，会自动调用
	vector<Paper> &m_fileContent;				// 所有文本内容
	unordered_map<string, int> m_phraseMap;		// 所有词组
	vector<unordered_map<string, int>::iterator> m_topPhrase;// 最高频的n个词组 
	int m_charNum;								// 字符个数
	int m_wordNum;								// 单词个数
	int m_lineNum;								// 行数
	bool m_calculated;							// 是否已进行过统计功能，避免重复计算
	bool m_useTitleWeight;						// 是否使用10倍标题权重
	int m_phraseLen;							// 短语长度
};