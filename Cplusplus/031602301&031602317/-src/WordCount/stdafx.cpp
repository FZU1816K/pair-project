#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <string>
using namespace std;
struct cube
{
	char wordtype[1000];
	int lenth;
	int frequency = 0;
};
int min(int a, int b)
{
	if (a >= b)
	{
		return b;
	}
	else return a;
}
cube type[600000];
int main(int argc, char*argv[])
{
	string fileinname;
	//char fileinname[100];
	string fileoutname;
	int i, j, k, p, q;
	int number = 10;
	int weight = 0;
	int group = 1;
	for (i = 1; i < argc; i++)
	{
		if (strcmp(argv[i], "-i") == 0)
		{
			i++;
			fileinname = argv[i];
		
			
		}//自定义输入，-i后接输入文本名 
		if (strcmp(argv[i], "-m") == 0)
		{
			i++;
			group = argv[i][0] - 48;
			
		}//-m后接自定义词组长
		if (strcmp(argv[i], "-n") == 0)
		{
			i++;
			number = 0;
			int sum;
			for (q = 0; q < strlen(argv[i]); q++)
			{
				sum = argv[i][q] - 48;
				for (p = 1; p <= strlen(argv[i]) - q - 1; p++)
				{
					sum = sum * 10;
				}
				number = number + sum;
			}
			
		} //自定义词频 
		if (strcmp(argv[i], "-w") == 0)
		{
			i++;
			if (argv[i][0] - 48 == 1)
			{
				weight = 1;
			}
			if (argv[i][0] - 48 == 0)
			{
				weight = 0;
			}
			
		}//权重定义 
		if (strcmp(argv[i], "-o") == 0)
		{
			i++;
			fileoutname = argv[i];
			//memcpy(fileoutname, argv[i], strlen(argv[i]));
			
		}//自定义输出，-o后接输出文本名 
	}
	//cout<<"请输入测试文本地址：";
	//cin>>fileinname;
	//cout<<"请输入词频统计个数："; 
	//cin>>number; 
   // cout<<"请选择权重方式：";
	//cin>>weight; 
	//cout<<"请选择词组长度：";
	//cin>>group;

	string line;
	int add = 1;
	int lines = 0;
	int lineses = 0;
	int characters = 0;
	int words = 0;

	char testword[1000];
	int flag = 0, temp = 0, ptr = 0, tra = 0,dra=0;
	int kind = 0;
	int flagalter = 0, replace = 0;

	ifstream infile(fileinname);
	//cout << argv[2];
	if (infile)
	{
		while (getline(infile, line))
		{
			lines++;
			if (lines % 5 == 2)//title行内 
			{
				lineses++;
				if (weight == 1)
				{
					add = 10;
				}
				characters = characters + line.size() - 6;
				line[line.size()] = ' ';
				for (i = 7; i <= line.size(); i++)
				{
					ptr = 0;
					if (line[i] >= 'A'&&line[i] <= 'Z')
					{
						line[i] = line[i] + 32;
					}
					if (line[i] >= 'a'&&line[i] <= 'z'&&flag <= 3)
					{
						testword[flagalter + flag] = line[i];
						flag++;
						ptr = 1;
					}
					if ((line[i]<'a' || line[i]>'z') && flag <= 3)
					{
						flag = 0;
						flagalter = 0;
						tra = 0;
					}
					if (flag >= 4 && (line[i] >= '0'&&line[i] <= '9' || line[i] >= 'a'&&line[i] <= 'z') && ptr == 0)
					{
						testword[flagalter + flag] = line[i];
						flag++;
					}
					if (flag >= 4 && (line[i]<'0' || line[i]>'9'&&line[i]<'a' || line[i]>'z') && ptr == 0)
					{
						words++;
						tra++;
						if (tra == 1 && tra != group)
						{
							replace = i;
						}
						if (tra < group)
						{
							testword[flagalter + flag] = line[i];
							flag++;
							flagalter = flag + flagalter;
							flag = 0;
						}
						if (tra == group)
						{
							flag = flagalter + flag;
							for (p = 1; p <= kind; p++)
							{
								if (flag != type[p].lenth)
								{
									continue;
								}
								for (j = 0; j < flag; j++)
								{
									if (testword[j] != type[p].wordtype[j])
									{
										p++;
										j = 0;
										break;
									}
									if (j == flag - 1)
									{
										type[p].frequency = type[p].frequency + add;
										p = kind;
										temp = 1;
										break;
									}
								}
							}
							if (temp == 0)
							{
								kind++;
								for (k = 0; k < flag; k++)
								{
									type[kind].wordtype[k] = testword[k];
								}
								type[kind].lenth = flag;
								type[kind].frequency = type[kind].frequency + add;
							}
							if (group != 1)
							{
								i = replace;
								words = words - group + 1;
							}
							tra = 0;
							flag = 0;
							temp = 0;
							flagalter = 0;
						}
					}
				}
			}
			if (lines % 5 == 3)//abstract行内 
			{
				lineses++;
				add = 1;
				characters = characters + line.size() - 9;
				line[line.size()] = ' ';
				for (i = 10; i <= line.size() ; i++)
				{
					ptr = 0;
					if (line[i] >= 'A'&&line[i] <= 'Z')
					{
						line[i] = line[i] + 32;
					}
					if (line[i] >= 'a'&&line[i] <= 'z'&&flag <= 3)
					{
						testword[flagalter + flag] = line[i];
						flag++;
						ptr = 1;
					}
					if ((line[i]<'a' || line[i]>'z') && flag <= 3)
					{
						flag = 0;
						flagalter = 0;
						tra = 0;
					}
					if (flag >= 4 && (line[i] >= '0'&&line[i] <= '9' || line[i] >= 'a'&&line[i] <= 'z') && ptr == 0)
					{
						testword[flagalter + flag] = line[i];
						flag++;
					}
					if (flag >= 4 && (line[i]<'0' || line[i]>'9'&&line[i]<'a' || line[i]>'z') && ptr == 0)
					{
						words++;
						tra++;
						if (tra == 1 && tra != group)
						{
							replace = i;
						}
						if (tra < group)
						{
							testword[flagalter + flag] = line[i];
							flag++;
							flagalter = flag + flagalter;
							flag = 0;
						}
						if (tra == group)
						{
							flag = flagalter + flag;
							for (p = 1; p <= kind; p++)
							{
								if (flag != type[p].lenth)
								{
									continue;
								}
								for (j = 0; j < flag; j++)
								{
									if (testword[j] != type[p].wordtype[j])
									{
										p++;
										j = 0;
										break;
									}
									if (j == flag - 1)
									{
										type[p].frequency = type[p].frequency + add;
										p = kind;
										temp = 1;
										break;
									}
								}
							}
							if (temp == 0)
							{
								kind++;
								for (k = 0; k < flag; k++)
								{
									type[kind].wordtype[k] = testword[k];
								}
								type[kind].lenth = flag;
								type[kind].frequency = type[kind].frequency + add;
							}
							if (group != 1)
							{
								i = replace;
								words = words - group + 1;
							}
							tra = 0;
							flag = 0;
							temp = 0;
							flagalter = 0;
						}
					}
				}
			}
		}
	}
	else
	{
		cout << "文件不存在" << endl;
	}
	infile.close();

	int print[100];
	int pront[100];
	int l = 0;
	tra = 0;
	int max = 0;
	int len = 100000;
	for (i = 1; i <= number; i++)
	{
		for (j = 1; j <= kind; j++)
		{
			if (type[j].frequency == max)
			{
				for (k = 0; k < min(type[j].lenth, len); k++)
				{
					if (type[j].wordtype[k] < type[tra].wordtype[k])
					{
						tra = j;
						len = type[j].lenth;
						break;
					}
					if (type[j].wordtype[k] > type[tra].wordtype[k])
					{
						break;
					}
					if (k == min(type[j].lenth, len) - 1)
					{
						if (type[j].lenth < len)
						{
							tra = j;
							len = type[j].lenth;
						}
					}
				}
			}
			if (type[j].frequency > max)
			{
				max = type[j].frequency;
				tra = j;
			}
		}
		print[i] = type[tra].frequency;
		pront[i] = tra;
		type[tra].frequency = 0;
		len = 100000;
		max = 0;
	}
	ofstream outfile(fileoutname);
	outfile << "characters: " << characters << endl;
	outfile << "words: " << words << endl;
	outfile << "lines: " << lineses << endl;
	for (i = 1; i <= number; i++)
	{
		outfile << "<" << type[pront[i]].wordtype << ">:" << " " << print[i] << endl;
	}

	return 0;
}