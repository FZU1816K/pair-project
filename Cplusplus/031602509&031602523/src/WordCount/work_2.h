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
	char out_file_name[MAX_LENGTH];	//����ļ���
	char file_name[MAX_LENGTH];		//�ļ���
	int m_flag;
	int n_flag;
	int i_flag;
	int o_flag;
	int w_flag;
	int count_m;
	int count_n;
	int weight;
	int count_chars;				//���ַ���
	int count_words;				//�ܵ�����
	int count_lines;				//������
	File()			
	{								//���캯����ʼ��
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
	string all_string;				//�ļ�����
	int count_rank[105] = {0};				//��Ƶ����
	string word_rank[105] = {""};			//��Ƶ��Ӧ��
	Words()
	{								//���캯����ʼ��
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
	string word;					//��ϣ�ڵ㹹��
	int count= 1;
	struct Wordnode *next=NULL;
};

int C_chars(istream &fl, File &fn, Words &wn, vector <string> &str_lines);		//ͳ���ַ���
int C_words(istream &fl, File &fn,Words &wn, Wordnode **l,  vector <string> &str_lines);	//ͳ�Ƶ�����
int hash_index(string word_str);					//��ϣֵ����
void hash_insert(Wordnode **l, string word_str, int weight_flag);	//��ɢ�в����ϣ�ڵ�
void rank_word(Wordnode **l, Words &nw,File &fl);			//��Ƶ����