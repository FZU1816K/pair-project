#include <string>
#include <fstream>
#include <unordered_map>
#include <vector>
#pragma once

using namespace std;

class InputFile
{
public:
	InputFile(string inputPath, int _phraseLength, int _weight, int _sortNum);
	~InputFile(); 
	int getCrtNum();									//返回字符数
	int getLineNum();									//返回行数
	int getWordNum();									//返回单词总数

	/*测试用*/
	vector<pair<string, int>> getOrderWord();

private:
	/*命令行参数*/
	int weight;											//Title单词权重（-w）
	int phraseLength;									//设定词组长度（-m）
	int sortNum;										//设定输出单词数量（-n）
	
	/*InputFile类成员信息*/
	int crtNum;
	int lineNum;
	int wordNum;
	vector<pair<string, int>> orderWord;				//按序存放词组的容器

	/*InputFile类内部变量*/
	bool hasCount;										//判断是否统计过单词数
	bool hasOpenFile;
	ifstream inputFile;
	unordered_map<string, int> phraseMap;				//存放文件中符合要求的词组
	unordered_map<string, int>::iterator itor;

	/*InputFile类内部接口函数*/
	void readFile();									//遍历文件，同时统计字符数、有效行数、词组数及其词频
	void sortPair();									//将文件中单词按要求排序
};

