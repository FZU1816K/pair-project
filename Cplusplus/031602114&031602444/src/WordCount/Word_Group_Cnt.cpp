#include"pch.h"
#include"Word_Group_Cnt.h"
#include<iostream>
#include<string>
#include<stdlib.h>
#include<map>
#include<fstream>
#include<algorithm>
#include<queue>

using namespace std;

/*一个string字符串输入到函数，若是符合规范的单词返回小写形式正确单词，空串返回空串，不合法单词返回"no"；*/
string Is_Word(string word)													
{
	int lenth = word.length();
	string true_word = "";
	string null_word = "";
	string fal_word = "no";
	if ((lenth > 0 && lenth < 4) || (lenth >= 4 && (!Is_Engch(word[0]) || !Is_Engch(word[1]) || !Is_Engch(word[2]) || !Is_Engch(word[3]))))
	{
		return fal_word;
	}
	else if (lenth == 0)
	{
		return null_word;
	}
	else
	{
		for (int j = 0; j < lenth; j++)
		{
			true_word += tolower(word[j]);
		}
		return true_word;
	}
}

/*判断是否是英文字母*/
bool Is_Engch(char ch)					//字符是a~z或A~Z之间的英文字母
{
	if ((ch >= 'a'&&ch <= 'z') || (ch >= 'A'&&ch <= 'Z'))
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*判断是否是数字*/
bool Is_Num(char ch)					//字符是0~9之间的数字
{
	if (ch >= '1'&& ch <= '9')
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*统计指定长度的合法单词量形成的词组词频*/
void Word_Group_Cnt(int word_Group_Len, string str, map <string, int > &group_Map,int ttl_Abs)
{
	string word_Now = "";
	string word_Group = "";
	int lenth = str.length();
	queue <int> que;
	for (int i = 0; i < lenth; i++)
	{
		if (Is_Num(str[i]) || Is_Engch(str[i]) && i != lenth - 1)
		{
			word_Now += str[i];
			continue;
		}
		else if (Is_Num(str[i]) || Is_Engch(str[i]) && i == lenth - 1)
		{
			word_Now += str[i];
			word_Now = Is_Word(word_Now);
			int word_Len = word_Now.length();
			if (word_Len >= 4)
			{
				word_Group += word_Now;
				if (que.size() == word_Group_Len - 1)
				{
  					group_Map[word_Group] += ttl_Abs;
				}
				else if (que.size() > word_Group_Len - 1)
				{
					word_Group = word_Group.substr(que.front());
					group_Map[word_Group] += ttl_Abs;
				}
			}
			else if (word_Len >= 0 && word_Len < 4)
			{
				continue;
			}

		}
		else
		{
			word_Now = Is_Word(word_Now);
			int word_Len = word_Now.length();
			if (word_Len >= 4)
			{
				word_Group += word_Now;
				if (que.size() < word_Group_Len - 1)
				{
					word_Group += str[i];
					word_Len += 1;
					while (!Is_Num(str[i + 1]) && !Is_Engch(str[i + 1]) && i + 1 < lenth)
					{
						word_Group += str[i + 1];
						word_Len += 1;
						i += 1;
					}
					que.push(word_Len);
					word_Now = "";
				}
				else if (que.size() == word_Group_Len - 1)
				{
					group_Map[word_Group] += ttl_Abs;
					word_Group += str[i];
					word_Len += 1;
					while (!Is_Num(str[i + 1]) && !Is_Engch(str[i + 1]) && i + 1 < lenth)
					{
						word_Group += str[i + 1];
						word_Len += 1;
						i += 1;
					}
					que.push(word_Len);
					word_Now = "";
				}
				else if (que.size() > word_Group_Len - 1)
				{
					word_Group = word_Group.substr(que.front());
					group_Map[word_Group] += ttl_Abs;
					que.pop();
					word_Group += str[i];
					word_Len += 1;
					while (!Is_Num(str[i + 1]) && !Is_Engch(str[i + 1]) && i + 1 < lenth)
					{
						word_Group += str[i + 1];
						word_Len += 1;
						i += 1;
					}
					que.push(word_Len);
					word_Now = "";
				}
			}
			else if (word_Len > 0 && word_Len < 4)
			{
				while (que.empty() != 1)
				{
					que.pop();
				}
				word_Now = "";
				word_Group = "";
			}
			else if (word_Len == 0)
			{
				continue;
			}												//是否要判断在输入到函数中
		}
	}
}

/*将每一个Title字段和Abstract字段分割进行词组词频统计*/
void Cut_Ttl_Abs(int word_Group_Len, char* filename, map<string, int> &group_Map, int weight_Type)
{
	fstream f_Tmp;
	string title_Str = "";
	string abs_Str = "";
	int group_Len = 2;
	int ttl_Weight = 0;
	if (weight_Type == 0)
	{
		ttl_Weight = 1;
	}
	else if (weight_Type == 1)
	{
		ttl_Weight = 10;
	}
	f_Tmp.open(filename);
	while (!f_Tmp.eof())
	{
		string str;
		getline(f_Tmp, str);
		int str_len = str.length();
		if ((str[0] >= '0' && str[0] <= '9') && (str[str_len - 1] >= '0' && str[str_len - 1] <= '9'))			//将编号行排除在字符统计中
		{
			continue;
		}
		if (str_len >= 10)
		{
			string if_Ttl = str.substr(0, 7);
			string if_Abs = str.substr(0, 10);
			if (if_Ttl == "Title: ")
			{
				title_Str += str.substr(7);															//将Title截下来之后的字符串；
				Word_Group_Cnt(word_Group_Len, title_Str, group_Map, ttl_Weight);					//将Title字段中的字符串进行词组截取以及词频统计
				title_Str = "";
			}
			else if (if_Abs == "Abstract: ")
			{
				if (str_len == 1024)
				{
					abs_Str += str.substr(10);
					continue;
				}
				else
				{
					abs_Str += str.substr(10);
					Word_Group_Cnt(word_Group_Len, abs_Str, group_Map, 1);
					abs_Str = "";
				}
			}
			else
			{
				if (str_len == 1024)
				{
					abs_Str += str;
					continue;
				}
				else
				{
					abs_Str += str;
					Word_Group_Cnt(word_Group_Len, abs_Str, group_Map, 1);
					abs_Str = "";
				}
			}
		}
		else if (str_len < 7)
		{
			abs_Str += str;
			Word_Group_Cnt(word_Group_Len, abs_Str, group_Map, 1);
			abs_Str = "";
		}
		else
		{
			string if_Ttl = str.substr(0, 7);
			if (if_Ttl == "Title: ")
			{
				title_Str += str.substr(7);														//将Title截下来之后的字符串；
				Word_Group_Cnt(word_Group_Len, title_Str, group_Map, ttl_Weight);				//将Title字段中的字符串进行词组截取以及词频统计
				title_Str = "";
			}
			else
			{
				abs_Str += str;
				Word_Group_Cnt(word_Group_Len, abs_Str, group_Map, 1);
				abs_Str = "";
			}
		}
	}
}