#pragma once
#include<iostream>
using namespace std;
#include<map>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>

class Parameter
{
public:
	vector<int>a;//������
	int i,m,n,w,o;
	void set();//���ó�ֵ
	void get_Parameter(int argc, char *argv[]);//��ȡ����
};	
