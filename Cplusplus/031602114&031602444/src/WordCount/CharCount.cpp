#include"pch.h"
#include"CharCount.h"
#include<iostream>
#include<string>
#include<fstream>
#include<stdlib.h>
using namespace std;

int CharCount(char *filename)						
{
	char ch_tmp;
	int ch_cnt = 0;
	int flag = -1;
	string str;
	fstream f_tmp;
	f_tmp.open(filename);
	if (!f_tmp)
	{
		cout << "Can't open file :" << filename << "\nUsage:countch filename" << endl;
		exit(0);
	}
	while (!f_tmp.eof())
	{
		getline(f_tmp, str);
		int str_len = str.length();
		if ((str[0] >= '0' && str[0] <= '9') && (str[str_len - 1] >= '0' && str[str_len - 1] <= '9'))			//将编号行排除在字符统计中
		{
			continue;
		}
		if (str_len > 7)																						//该行字符串长度大于Title长度
		{
			string no_Count_Ttl = str.substr(0, 7);
			string no_Count_Abs = str.substr(0, 10);
			if (no_Count_Ttl == "Title: ")
			{
				ch_cnt += str_len - 7;
			}
			else if (no_Count_Abs == "Abstract: ")
			{
				ch_cnt += str_len - 10;
			}
			else								//该行是没有Title: 也没有Abstract: 的有效行；
			{
				ch_cnt += str_len;
			}
			if (str_len != 1024)				//若该行1024全满，则最后没有换行符；否则最后会有一个换行符；
			{
				ch_cnt++;
			}
		}
		else									//该行字符串长度小于7，可能是空行或者只有几个短单词总长小于7；
		{
			if (str_len == 0)
			{
				continue;
			}
			else
			{
				ch_cnt += str_len + 1;
			}
		}
	}
	f_tmp.close();
	return ch_cnt - 1;
}