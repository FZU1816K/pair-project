#pragma once
#include<iostream>
using namespace std;
#include<map>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>

class File
{
public:
	ifstream infile;
	ofstream outfile;
	vector<int>a;//排序用
	int f_open = 0;
	void open(char *in_file,char *out_file);//打开输入输出文件
	void close();//关闭输入输出文件
	void output(int cnum,int wnum,int lnum, map<string, int> word,int temp);//将统计信息写入输出文件
};