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
	int countLines(string u); //ͳ������
	int countChars(string u); //ͳ���ַ���
	int countWords(string u);//ͳ�Ƶ�����
	void countDanci(string u, string v, int w);//���ص���
	void count(string u, string v, int m, int w);//���غϷ����鼰���Ƶ��δ����
	void TitleAndAbstract(string filename);//��ȡtitle�ַ���abstract�ַ�
	void print(string outfile, string str, int n);//������ļ�
	string get_abstract();
	string get_title();


};
