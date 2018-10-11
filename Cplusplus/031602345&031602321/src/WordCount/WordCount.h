#pragma once
#include <stdio.h>
#include <iostream>
#include <map>
#include <algorithm>
#include <vector>
#include <string>
#include <fstream>
#include <assert.h>

using namespace std;

// 解析参数
void ParserParam(int argc, char *argv[]);

// 自定义getline函数 返回值为之后是否还有字符
bool GetLine(ifstream &instream, string &line);

// 字符统计
int CountChar(string input_path);

// 有效行数统计
int CountLine(string input_path);

// 有效单词总数统计
int CountWord(string input_path);

// 得到词频统计
void GetWordCountMap(string input_path, int word_group_length = 1);

// return a orderd vector of WordNode
vector<map<string, int>::iterator> GetFirstNWords(string file_location, int word_group_length = 1, int number_show = 10);

// 展示结果
void ShowResult(int characters, int words, int lines, vector<map<string, int>::iterator> first_n_words, string ouput_path);

// 初始化
void Init();

// 手动设置weight group_length的参数 用于测试
void SetParam(int weight, int group_length);