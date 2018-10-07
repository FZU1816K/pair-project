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

// ��������
void ParserParam(int argc, char *argv[]);

// �Զ���getline���� ����ֵΪ֮���Ƿ����ַ�
bool GetLine(ifstream &instream, string &line);

// �ַ�ͳ��
int CountChar(string input_path);

// ��Ч����ͳ��
int CountLine(string input_path);

// ��Ч��������ͳ��
int CountWord(string input_path);

// �õ���Ƶͳ��
void GetWordCountMap(string input_path);

// return a orderd vector of WordNode
vector<map<string, int>::iterator> GetFirstNWords(string file_location);

// չʾ���
void ShowResult(int characters, int words, int lines, vector<map<string, int>::iterator> first_n_words, string ouput_path);