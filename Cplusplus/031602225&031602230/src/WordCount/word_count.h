#pragma once
#include "pch.h"
#include<iostream>
#include<sstream>
#include<string>
#include<queue>
#include<stdio.h>
#include<fstream>

using namespace std;

class MyCount
{
public:
	string title_str;
	string abstract_str;
	int countLines(string u); //统计行数
	int countChars(string u); //统计字符数
	int countWords(string u);//统计单词数
	void countDanci(string u, string v, int w);//返回单词
	void count(string u, string v, int m, int w);//返回合法词组及其词频（未排序）
	void TitleAndAbstract(string filename);//提取title字符和abstract字符
	void print(string outfile, string str, int n);//输出到文件
	string get_abstract();
	string get_title();


};
