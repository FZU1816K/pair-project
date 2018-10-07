#pragma once
#include<iostream>
using namespace std;
#include<map>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>

class Statistics
{
public:
	vector<int>a;//排序用
	map<string, int> word;//记录统计的单词或词组的词频
	map<string, int> trecord;//记录标题中的词频
	map<string, int> arecord;//记录摘要中的词频
	void set(ifstream& in, int w, int m);//进行统计
	void display(ofstream& out,int temp);//输出统计结果
	int characters(ifstream& in);//统计字符数
	int lines(ifstream& in);//统计行数
	int	nw_words(ifstream& in);//统计无权重单词
	int	w_words(ifstream& in);//统计权重单词
	int	nw_phrase(ifstream& in,int m);//统计无权重词组
	int	w_phrase(ifstream& in,int m);//统计权重词组
private:
	int cnum;//字符数
	int wnum;//单词数
	int lnum;//行数
};
