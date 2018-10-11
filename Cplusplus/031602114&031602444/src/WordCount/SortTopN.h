#pragma once
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#include<fstream>
#include<string>
#include<string.h>
#include<vector>
#include<map>
#include<cstdlib>

using namespace std;

/******************************自定义词频统计输出**************************************/

/***************************************************************************************
**	功能：词频排序
**	输入参数：所需排序的词的数量，词所被存储的map容器，进行排序的辅助vector容器
**	返回变量：空返回函数，在函数内部对map、vector容器改变并存储
**	算法：
**	附加说明：
****************************************************************************************/
void SortTopN(int N, map<string, int> &m0, vector<pair<string, int>>& x);



/***************************************************************************************
**	功能：将vector容器中的内容输出
**	输入参数：辅助vector容器，输出流变量名
**	返回变量：空返回函数，在函数内部将vector容器中的内容输出到文件中
**	算法：
**	附加说明：
****************************************************************************************/
void Display(vector<pair<string, int>>& x, ofstream &out_file);

