#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <map>
#include <algorithm>
#include <vector>
#include <string>
#include <fstream>
#include <assert.h>
#include "WordCount.h"

using namespace std;

#define dd(x) cout << #x << "=" << x << ", "
#define de(x) cout << #x << "=" << x << endl

/* 参数部分 */
int p_weight;
int p_number_show;
int p_group_length;
string p_input_path;
string p_output_path;

/* 非参数 */
bool g_has_got_map;
bool g_has_got_lines;
bool g_has_got_words;
bool g_has_got_characters;

int g_lines;
int g_words;
int g_characters;
map<string, int> g_word_count_map;

int main(int argc, char *argv[])
{
	//关闭输入同步
	std::ios::sync_with_stdio(false);

	ParserParam(argc, argv);
	printf("参数调整部分\n");
	de(p_input_path);
	de(p_output_path);
	de(p_weight);
	de(p_group_length);
	de(p_number_show);

	g_has_got_map = false;
	g_has_got_lines = false;
	g_has_got_words = false;
	g_characters = 0;
	g_lines = 0;
	g_words = 0;
	g_word_count_map.clear();

	GetWordCountMap(p_input_path, p_group_length);

	int characters = CountChar(p_input_path);
	int words = CountWord(p_input_path);
	int lines = CountLine(p_input_path);
	vector<map<string, int>::iterator> first_n_words = GetFirstNWords(p_input_path, p_group_length, p_number_show);

	ShowResult(characters, words, lines, first_n_words, p_output_path);
}
