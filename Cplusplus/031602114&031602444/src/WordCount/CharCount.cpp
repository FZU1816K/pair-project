#include"pch.h"
#include"CharCount.h"
#include"Word_Group_Cnt.h"
#include<iostream>
#include<string>
#include<fstream>
#include<stdlib.h>
using namespace std;

int CharCount(char *filename)						
{
	char ch_tmp;
	int ch_cnt = 0;
	int flag = 0;
	int num_Line = 0;						//编号行数；
	int num_Ch = 0;							//编号行的编号字符总数；
	string str;
	fstream f_tmp;
	f_tmp.open(filename);
	if (!f_tmp)
	{
		cout << "Can't open file :" << filename << "\nUsage:countch filename" << endl;
		exit(0);
	}
	while (f_tmp.get(ch_tmp))
	{
		ch_cnt++;							//先统计所有字符数；
	}
	f_tmp.close();
//	cout << ch_cnt << endl;
	f_tmp.open(filename);
	while (!f_tmp.eof())
	{
		getline(f_tmp, str);
		flag = 0;
		int str_len = str.length();
		for (int i = 0; i < str_len; i++)
		{
			if (!Is_Num(str[i]))
			{
				flag = 0;
				break;
			}
			else
			{
				flag = 1;
			}
		}
		if (flag == 1)
		{
//			cout << str << endl;
			num_Line++;
			num_Ch += str_len;				//编号行的长度；
			num_Ch += 3;					//每遇到一个编号行会多计算三个换行符；
		}
	}
	f_tmp.close();
	ch_cnt = ch_cnt - 17 * num_Line - num_Ch;
	return ch_cnt + 2;
}