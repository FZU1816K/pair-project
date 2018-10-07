#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <map>
#include <algorithm>
#include <vector>
#include <string>
#include <fstream>
#include <assert.h>
#include <deque>
#include "WordCount.h"

using namespace std;

#define dd(x) cout << #x << "=" << x << ", "
#define de(x) cout << #x << "=" << x << endl

/* 参数部分 */
extern int p_weight;
extern int p_length;
extern int p_number_show;
extern string p_input_path;
extern string p_output_path;

/* 非参数 */
extern bool g_has_got_map;
extern bool g_has_got_lines;
extern bool g_has_got_words;
extern bool g_has_got_characters;

extern int g_lines;
extern int g_words;
extern int g_characters;
extern map<string, int> g_word_count_map;

// 两个map<string, int>迭代器的比较函数
bool compare_bigger(map<string, int>::iterator it1, map<string, int>::iterator it2)
{
	if (it1->second == it2->second)
		return (it1->first.compare(it2->first) < 0);
	return it1->second > it2->second;
}

// 字符是否是字母
bool CharAlphaJudge(char ch)
{
	if (('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z'))
		return true;
	return false;
}

// 字符是否是字母 or 数字
bool CharAlphaNumberJudge(char ch)
{
	if (('0' <= ch && ch <= '9') || ('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z'))
		return true;
	return false;
}

// 检查word的合法性
bool WordCheck(string word)
{
	if (word.size() < 4)
		return false;

	for (int i = 0; i < 4; i++)
		if (!CharAlphaJudge(word[i])) return false;
	return true;
}

// 解析参数
void ParserParam(int argc, char *argv[])
{
	// 默认参数
	p_weight = 0;
	p_length = 1;
	p_number_show = 10;

	bool b_have_input = false;
	bool b_have_output = false;
	bool b_have_weight = false;

	try
	{
		for (int i = 1; i < argc; i++)
		{
			if (argv[i][0] == '-')
			{
				if (i + 1 == argc)
				{
					printf("参数错误：缺少参数\n");
					exit(1);
				}
				switch (argv[i][1])
				{
				case 'i':
					b_have_input = true;
					p_input_path = argv[i + 1];
					break;
				case 'o':
					b_have_output = true;
					p_output_path = argv[i + 1];
					break;
				case 'w':
					b_have_weight = true;
					p_weight = stoi(argv[i + 1]);
					break;
				case 'm':
					p_length = stoi(argv[i + 1]);
					break;
				case 'n':
					p_number_show = stoi(argv[i + 1]);
					break;
				default:
					printf("参数错误：未知参数\n");
					exit(1);
				}
				i++;
			}
		}
		if (!(b_have_input && b_have_output && b_have_weight))
		{
			printf("参数错误：缺少参数\n");
			exit(1);
		}
	}
	catch (const std::exception&)
	{
		printf("解析参数失败\n");
		exit(1);
	}
}

// 自定义getline函数 返回值为之后是否还有字符
bool GetLine(ifstream &instream, string &line)
{
	char ch;
	int count = 0;
	bool have_visible_char = false;
	char first_char = '*';
	bool is_valid_line = false;

	line.clear();

	while (instream.get(ch))
	{
		// 字符统计
		if (first_char == 'T' && count > 6) g_characters++;
		if (first_char == 'A' && count > 9) g_characters++;

		// 第一个字符如果是'T'或者'A'的话 该行有效
		if (!is_valid_line && (ch == 'T' || ch == 'A'))
		{
			first_char = ch;
			is_valid_line = true;
		}

		if (ch == '\n')
		{
			if (is_valid_line && have_visible_char)
				g_lines++;
			return true;
		}
		else if (ch == '\r')
		{
			// 忽略'\r' 在文本格式下并没有\r这个字符
			continue;
		}
		else
		{
			line += ch;
			if (first_char == 'T' && count > 6 && ch != ' ')
				have_visible_char = true;
			else if (first_char == 'A' && count > 9 && ch != ' ')
				have_visible_char = true;
		}
		count++;
	}
	// 碰上EOF
	if (is_valid_line && have_visible_char) g_lines++;

	g_has_got_characters = true;
	g_has_got_lines = true;

	return false;
}

// 字符统计
int CountChar(string input_path)
{
	// 如果已经得到 就直接返回
	if (g_has_got_characters)
		return g_characters;

	// 没有得到的时候 再读取一次文件
	ifstream instream;
	instream.open(input_path, ios::in);
	assert(instream.is_open());

	g_characters = 0;

	string line;
	while (GetLine(instream, line));

	// 关闭文件
	instream.close();

	return g_characters;
}

// 有效单词总数统计
int CountWord(string input_path)
{
	// 如果已经得到 就直接返回
	if (g_has_got_words)
		return g_words;

	// 没有得到的时候 再读取一次文件
	ifstream instream;
	instream.open(input_path, ios::in);
	assert(instream.is_open());

	g_words = 0;

	// 遍历每一行 得到单词总数
	string line;
	while (true)
	{
		bool have_next_line = GetLine(instream, line);

		int line_length = line.size();
		if (line_length > 0 && (line[0] == 'T' || line[0] == 'A'))
		{
			int word_left_pos;
			int word_right_pos;
			int word_length;

			if (line[0] == 'T')
				word_left_pos = word_right_pos = 7;
			else
				word_left_pos = word_right_pos = 10;

			while (word_left_pos < line_length)
			{
				while (!CharAlphaNumberJudge(line[word_left_pos]) && word_left_pos < line_length)
					word_left_pos++;

				word_right_pos = word_left_pos;

				while (((word_right_pos + 1) < line_length) && (CharAlphaNumberJudge(line[word_right_pos + 1])))
					word_right_pos++;

				word_length = word_right_pos - word_left_pos + 1;

				if (word_length >= 4)
				{
					string word = line.substr(word_left_pos, word_length);
					if (WordCheck(word))
						g_words++;
				}
			}
		}

		// 之后没有内容 退出循环
		if (!have_next_line) break;
	}

	// 关闭文件
	instream.close();

	g_has_got_words = true;

	return g_words;
}

// 有效行数统计
int CountLine(string input_path)
{
	// 如果已经得到 就直接返回
	if (g_has_got_lines)
		return g_lines;

	// 没有得到的时候 再读取一次文件
	ifstream instream;
	instream.open(input_path, ios::in);
	assert(instream.is_open());

	g_lines = 0;

	string line;
	while (GetLine(instream, line));

	// 关闭文件
	instream.close();

	return g_lines;
}

// 得到词(组)频统计
void GetWordCountMap(string input_path)
{
	// 在得到词(组)频字典的过程中 可以顺路统计出字符数、有效行数
	g_lines = 0;
	g_characters = 0;
	g_word_count_map.clear();

	ifstream instream;
	instream.open(input_path, ios::in);
	assert(instream.is_open());

	string line;

	int cnt = 1;

	while (true)
	{
		// printf("正在处理第%d行\n", cnt);

		bool have_next_line = GetLine(instream, line);

		// de(line);

		int line_length = line.size();
		if (line_length > 0 && (line[0] == 'T' || line[0] == 'A'))
		{
			bool b_in_queue = false;
			int words_in_queue = 0;
			int pos = (line[0] == 'T') ? 7 : 10;

			deque<char> deque;
			deque.clear();

			while (pos < line_length)
			{
				if (b_in_queue)
				{
					if (CharAlphaNumberJudge(line[pos]))
					{
						int word_length;
						int word_left_pos = pos;
						int word_right_pos = pos;

						// 寻找本单词的右侧边界(本单词不一定合法)
						while (((word_right_pos + 1) < line_length) && (CharAlphaNumberJudge(line[word_right_pos + 1])))
							word_right_pos++;
						word_length = word_right_pos - word_left_pos + 1;

						string word = line.substr(word_left_pos, word_length);
						if (WordCheck(word))
						{
							// 本单词合法
							g_words++;

							// 队列中单词总数已到达词组长度
							if (words_in_queue == p_length)
							{
								// 从前面弹出第一个单词
								while (deque.size() > 0 && CharAlphaNumberJudge(deque.front()))
									deque.pop_front();

								words_in_queue--;

								// 从前面弹出分隔符(如果有的话)
								while (deque.size() > 0 && !CharAlphaNumberJudge(deque.front()))
									deque.pop_front();
							}

							words_in_queue++;
							for (size_t i = 0; i < word.size(); i++)
								deque.push_back(word[i]);

							if (words_in_queue == p_length)
							{
								string word;
								while (!deque.empty())
								{
									word += deque.front();
									deque.pop_front();
								}

								// 转为小写
									transform(word.begin(), word.end(), word.begin(), ::tolower);

								// cout << word << endl;

								if (g_word_count_map.count(word) == 0)
									g_word_count_map[word] = 1;
								else g_word_count_map[word] += 1;

								for (size_t i = 0; i < word.size(); i++)
								{
									deque.push_back(word[i]);
								}
							}
						}
						else
						{
							// 本单词不合法 清空队列 并设置b_in_queue为false
							deque.clear();
							words_in_queue = 0;
							b_in_queue = false;
						}

						pos = word_right_pos;
					}
					else
					{
						deque.push_back(line[pos]);
					}
				}
				else
				{
					bool have_next_valid_word = false;
					int word_length;
					int word_left_pos = pos;
					int word_right_pos = pos;

					// 发现下一个合法单词
					while (word_left_pos < line_length)
					{
						while (!CharAlphaNumberJudge(line[word_left_pos]) && word_left_pos < line_length)
							word_left_pos++;
						word_right_pos = word_left_pos;
						while (((word_right_pos + 1) < line_length) && (CharAlphaNumberJudge(line[word_right_pos + 1])))
							word_right_pos++;
						word_length = word_right_pos - word_left_pos + 1;

						if (word_length >= 4)
						{
							string word = line.substr(word_left_pos, word_length);

							// 发现的单词是合法的
							if (WordCheck(word))
							{
								g_words++;

								b_in_queue = true;
								have_next_valid_word = true;
								// 将发现的单词放入队列中
								for (size_t i = 0; i < word.size(); i++)
									deque.push_back(word[i]);
								words_in_queue = 1;

								if (words_in_queue == p_length)
								{
									string word;
									while (!deque.empty())
									{
										word += deque.front();
										deque.pop_front();
									}

									// 转为小写
									transform(word.begin(), word.end(), word.begin(), ::tolower);

									// cout << word << endl;

									if (g_word_count_map.count(word) == 0)
										g_word_count_map[word] = 1;
									else g_word_count_map[word] += 1;

									for (size_t i = 0; i < word.size(); i++)
									{
										deque.push_back(word[i]);
									}
								}

								break;
							}
						}

						word_left_pos = word_right_pos + 1;
					}

					pos = word_right_pos;
				}
				pos++;
			}
		}
		cnt++;
		if (!have_next_line) break;
	}

	g_has_got_words = true;
	g_has_got_map = true;
}

// return a orderd vector of WordNode
vector<map<string, int>::iterator> GetFirstNWords(string file_location)
{
	if (g_has_got_map == false)
		GetWordCountMap(file_location);

	vector<map<string, int>::iterator> word_node_vectors;
	vector<map<string, int>::iterator> first_n_words;

	map<string, int>::iterator it = g_word_count_map.begin();

	for (; it != g_word_count_map.end(); it++)
		word_node_vectors.push_back(it);

	int length = word_node_vectors.size();
	int num_show_node = p_number_show;

	// 使用sort的话 产生的是O(N*Log(N))的复杂度 直接选的复杂度O(N*n)
	for (int step = 0; step < num_show_node; step++)
	{
		int max_node_id = step;
		map<string, int>::iterator max_node = word_node_vectors[step];
		for (int i = step + 1; i < length; i++)
		{
			if (compare_bigger(word_node_vectors[i], max_node))
			{
				max_node = word_node_vectors[i];
				max_node_id = i;
			}
		}
		swap(word_node_vectors[step], word_node_vectors[max_node_id]);
	}

	// 修改了一处BUG,应该只返回前n个词，旧版本改来改去最后疏忽了这一点
	for (int i = 0; i < num_show_node; i++)
		first_n_words.push_back(word_node_vectors[i]);

	return first_n_words;
}

// 展示结果
void ShowResult(int characters, int words, int lines, vector<map<string, int>::iterator> first_n_words, string output_path)
{
	ofstream outstream;
	outstream.open(output_path);
	outstream << "characters: " << characters << endl;
	outstream << "words: " << words << endl;
	outstream << "lines: " << lines << endl;

	int length = first_n_words.size();
	for (int i = 0; i < length; i++)
	{
		outstream << '<' << first_n_words[i]->first << '>' << ": " << first_n_words[i]->second << endl;
	}

	outstream.close();
}