#pragma once
/******************计算input.txt单词组各有多少个并输出前十个**********************/
#ifndef PHRASE_H_
#define PHRASE_H_
#include<map>
#include<vector>
#include<string>

typedef std::pair<std::string, int> PAIR;

class Psort
{
private:
	std::string finname; //读取的文件名，需要从外部获取
	std::string foutname;
	std::vector<PAIR>phrase_v;  //存词组的，暂时将词组也存成string
	int len;  //传进来的参数，表示词组包含的单词长度
	int num;  //输出的词组数量

public:

	Psort(std::string filein, std::string fileout, int length, int number);
	Psort();
	/*************************************************/
	bool get_empty();  //为了测试而额外写的函数，实际并不需要
	int get();
	/*************************************************/
	void fwrite(); //写入reault.txt
	void PS();  //计算词组频数并排序
	void show();  //显示词组数
};

#endif
