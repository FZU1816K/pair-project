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
	vector<int>a;//������
	int f_open = 0;
	void open(char *in_file,char *out_file);//����������ļ�
	void close();//�ر���������ļ�
	void output(int cnum,int wnum,int lnum, map<string, int> word,int temp);//��ͳ����Ϣд������ļ�
};