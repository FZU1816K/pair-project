#include"pch.h"
#include"LineCount.h"
#include"Word_Group_Cnt.h"
using namespace std;

int LineCount(char *filename)
{
	int line_cnt = 0;
	int num_Line = 0;
	int flag = 0;
	string str;
	char ch_tmp;
	fstream f_tmp;
	f_tmp.open(filename);
	if (!f_tmp)
	{
		cout << "Can't open file :" << filename << "\nUsage:countch filename" << endl;
		exit(0);
	}
	while (f_tmp.get(ch_tmp))
	{
		if (ch_tmp != ' ' && ch_tmp != '\t' && ch_tmp != '\n')
		{
			flag = 1;
		}
		else if (ch_tmp == '\n'&&flag == 1)
		{
			line_cnt++;
			flag = 0;
		}
	}
	if (flag == 1)
	{
		line_cnt++;
	}
	f_tmp.close();
	f_tmp.open(filename);
	while (!f_tmp.eof())
	{
		getline(f_tmp, str);
		flag = 0;
		int lenth = str.length();
		for (int i = 0; i < lenth; i++)
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
			num_Line++;
		}
	}
	return line_cnt - num_Line;
}