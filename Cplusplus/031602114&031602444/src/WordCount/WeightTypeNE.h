#pragma once
#include<istream>
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#include<fstream>
#include<string>
#include<string.h>
#include<vector>
#include<map>
using namespace std;

/***************************************************************************************
**	功能：加入权重的词频统计
**	输入参数：所被测试的文件名，存储单词的map容器，权重类别
**	返回变量：空返回函数，在函数中对map容器进行改变并存储
**	算法：
**	附加说明：
****************************************************************************************/
void WeightTypeNE(char* filem, map<string, int> &m0, int W);
