#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include<vector>
#include <algorithm>
#include <queue>
using namespace std;
#define MAX_LENGTH   100
#define HASH_LENGTH	   5639

struct File
{
	char out_file_name[MAX_LENGTH];	//输出文件名
	char file_name[MAX_LENGTH];		//文件名
	int m_flag;
	int n_flag;
	int i_flag;
	int o_flag;
	int w_flag;
	int count_m;
	int count_n;
	int weight;
	int count_chars;				//总字符数
	int count_words;				//总单词数
	int count_lines;				//总行数
	File()			
	{								//构造函数初始化
		out_file_name[0] = '\0';
		file_name[0] = '\0';
		count_chars = 0;
		count_words = 0;
		count_lines = 0;
		m_flag = 0;
		n_flag = 0;
		i_flag = 0;
		o_flag = 0;
		w_flag = 0;
		count_m = 0;
		count_n = 0;
		weight = -1;
	}
};

struct Words
{
	string all_string;				//文件内容
	int count_rank[105] = {0};				//词频排名
	string word_rank[105] = {""};			//词频对应词
	Words()
	{								//构造函数初始化
		all_string = "";
		for (int i = 0; i < 105; i++)
		{
			count_rank[i] = 0;
			word_rank[i] = "";
		}
	}
};
struct Wordnode
{
	string word;					//哈希节点构造
	int count= 1;
	struct Wordnode *next=NULL;
};

int C_chars(istream &fl, File &fn, Words &wn, vector <string> &str_lines);		//统计字符数
int C_words(istream &fl, File &fn,Words &wn, Wordnode **l,  vector <string> &str_lines);	//统计单词数
int hash_index(string word_str);					//哈希值计算
void hash_insert(Wordnode **l, string word_str, int weight_flag);	//开散列插入哈希节点
void rank_word(Wordnode **l, Words &nw,File &fl);			//词频排名