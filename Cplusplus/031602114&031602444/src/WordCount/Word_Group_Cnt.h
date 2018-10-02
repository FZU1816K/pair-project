#pragma once
#pragma once
#include<iostream>
#include<string>
#include<map>
#include<stdlib.h>
using namespace std;


/***************************************************************************************
**	功能：对只含字母数字的string串判定是否为有效合法单词
**	输入参数：被判定的只含字母数字string串
**	返回变量：返回string型变量，若为合法单词，返回其小写形式；若为不合法单词，返回"no"；若为空串，返回空串；
**	算法：暂无
**	附加说明：只能对只含字母数字的string串进行判别
****************************************************************************************/
string Is_Word(string word);



/***************************************************************************************
**	功能：判定字符是否为英文字母
**	输入参数：被判定的单个字符
**	返回变量：返回bool变量，若是英文字母，返回true；否则，返回false；
**	算法：暂无
**	附加说明：暂无
****************************************************************************************/
bool Is_Engch(char ch);



/***************************************************************************************
**	功能：判定字符是否为数字
**	输入参数：被判定的单个字符
**	返回变量：返回bool变量，若是数字，返回true；否则，返回false；
**	算法：暂无
**	附加说明：暂无；
****************************************************************************************/
bool Is_Num(char ch);



/***************************************************************************************
**	功能：将整个论文列表中的Title和Abstract字段分开进行词组词频统计
**	输入参数：形成词组的合法单词个数，所被测试的文件名，存储词组的map容器，权重类别
**	返回变量：空返回函数，在函数内部将Title字段和Abstract字段分开并统计词组词频
**	算法：暂无
**	附加说明：暂无
****************************************************************************************/
void Cut_Ttl_Abs(int word_Group_Len, char* filename, map<string, int>& group_Map, int weight_Type);



/***************************************************************************************
**	功能：对string串进行词组词频统计，对合法单词切割并连接统计
**	输入参数：形成词组的合法单词个数，string类长串字段，存储词组的map容器，字段类别（Title或Abstract）
**	返回变量：空返回函数，在函数内部将string字段内容切割并组合存入map容器
**	算法：暂无
**	附加说明：暂无
****************************************************************************************/
void Word_Group_Cnt(int word_Group_Len, string str, map <string, int >& group_Map, int ttl_Abs);
