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
	vector<int>a;//排序用
	int i,m,n,w,o;
	void set();//设置初值
	void get_Parameter(int argc, char *argv[]);//提取参数
};	
