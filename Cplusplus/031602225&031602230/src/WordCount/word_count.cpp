#include "pch.h"
#include<iostream>
#include<sstream>
#include<string>
#include<queue>
#include<stdio.h>
#include<fstream>
#include"word_count.h"
using namespace std;

struct wo {
	char word[500];
	int count;
};
priority_queue<wo> tmp;//���ȶ���
bool operator< (wo a, wo b)//�Զ�������
{
	//������ͬ�ĵ��ʰ��ֵ�����
	if (a.count == b.count)
	{
		int i = -1;

		do {
			i++;
		} while (a.word[i] == b.word[i]);

		return a.word[i] > b.word[i];

	}
	//����Ƶ������	
	else return a.count < b.count;
}

int MyCount::countLines(string u)
{
	int lines = 0;
	int flag = 0;
	int n = u.length();

	for (int i = 0; i < n; i++)
	{


		if (u[i] >= 33 && u[i] <= 126)//��ʾ��������Ч��
		{
			flag = 1;
		}
		if (u[i] == 10 && flag == 1)//����������Ч�У����ұ�����1�����з�ʱ��������1
		{
			lines++;
			flag = 0;
		}
	}
	if (flag == 1)//���һ�����û�л��з���Ҳ��1
		lines++;
	return lines;
}

int MyCount::countChars(string u)
{
	int a;
	a = u.length();
	return a;
}

int MyCount::countWords(string u)
{

	char temp[100];
	int k, flag;
	int words = 0;

	int n = u.length();
	for (int i = 0; i < n; i++)
	{

		//�ж��Ƿ�Ϊ����
		if ((u[i] >= 'a'&&u[i] <= 'z') || (u[i] >= 'A'&&u[i] <= 'Z'))
		{
			k = 0;
			flag = 0;
			while ((u[i] >= 'a'&&u[i] <= 'z') || (u[i] >= 'A'&&u[i] <= 'Z') || (u[i] >= '0'&&u[i] <= '9'))
			{
				temp[k++] = u[i];
				i++;
			}
			temp[k++] = '\0';
			for (int j = 0; j < 4; j++)
			{
				if ((temp[j] >= '0'&&temp[j] <= '9') || temp[j] == '\0')
				{
					flag = 1;//�ж��Ƿ���ϵ��ʹ淶
					break;
				}
			}
			if (flag == 0)
			{
				words++;
			}
		}
		else continue;
	}
	return words;
}

void MyCount::count(string u, string v, int m, int w)
{
	wo *cizu = new wo[1000000];//��̬����ṹ������
	wo temp_cizu;
	int t = 0;
	//ɨ��Title
	string *ci = new string[1000000];

	int k = 0;
	int le = u.length();
	for (int i = 0; i < le; i++)//�������еĴʺ��ַ�
	{

		if ((u[i] >= 'a'&&u[i] <= 'z') || (u[i] >= 'A'&&u[i] <= 'Z') || (u[i] >= '0'&&u[i] <= '9'))//��һ������ĸ������
		{

			while ((u[i] >= 'a'&&u[i] <= 'z') || (u[i] >= 'A'&&u[i] <= 'Z') || (u[i] >= '0'&&u[i] <= '9'))
			{
				if (u[i] >= 'A'&&u[i] <= 'Z')
					u[i] += 32;
				ci[k] += u[i];
				i++;
			}
			while (!(u[i] >= 'a'&&u[i] <= 'z') && !(u[i] >= 'A'&&u[i] <= 'Z') && !(u[i] >= '0'&&u[i] <= '9') && u[i] != '\n'&&i < le)
			{
				ci[k] += u[i];
				i++;
			}
			if (u[i] == '\n')ci[++k] = '\n';//���з�������

			i--;
			k++;
		}
		else continue;
	}

	for (int i = 0; i < k; i++)
	{
		int flag1 = 0;
		int flag2 = 0;

		for (int j = 0; j < 4; j++)
		{
			if (!(ci[i][j] >= 'a'&& ci[i][j] <= 'z'))
			{
				flag2 = 1;//�жϵ�һ���Ƿ���ϵ��ʹ淶
				break;
			}
		}

		if (flag2 == 0)//��һ������
		{
			strcpy_s(temp_cizu.word, 500,ci[i].c_str()); //
			temp_cizu.count = 1;
			if (w == 1)temp_cizu.count += 9;
			for (int j = 1; j < m; j++)
			{
				int flag3 = 0;
				for (int f = 0; f < 4; f++)
				{
					if (!(ci[i + j][f] >= 'a'&& ci[i + j][f] <= 'z'))
					{
						flag3 = 1;//�жϺ󼸸��Ƿ���ϵ��ʹ淶
						i = i + j;
						break;
					}
				}

				if (flag3 == 0)//�󼸸����Ϸ�
					strcat_s(temp_cizu.word, 500, ci[i + j].c_str());//
				else { flag1 = 1; break; }
			}


			if (flag1 == 0) //����
			{
				int a = strlen(temp_cizu.word) - 1;//ȥ����β�ķ���

				while (!(temp_cizu.word[a] >= 'a'&&temp_cizu.word[a] <= 'z') && !(temp_cizu.word[a] >= '0'&&temp_cizu.word[a] <= '9'))
				{

					temp_cizu.word[a]='\0';//
					a--;
				}

				int h, j = t;
				for (h = 0; h < j; h++)//��ͬ�Ĵʸ����ۼ�
				{
					if (strcmp(temp_cizu.word,cizu[h].word) == 0)//

					{
						cizu[h].count++;
						if (w == 1)cizu[h].count += 9;
						break;
					}
				}

				if (t == 0 || h == j)//�´������µĿռ�
				{
					cizu[t] = temp_cizu;
					t++;
				}
			}
			else continue;
		}
		else continue;
	}

	//ɨ��Abstract
	string *ci2 = new string[1000000];

	int kk = 0;
	int le2 = v.length();
	for (int i = 0; i < le2; i++)//�������еĴʺ��ַ�
	{

		if ((v[i] >= 'a'&&v[i] <= 'z') || (v[i] >= 'A'&&v[i] <= 'Z') || (v[i] >= '0'&&v[i] <= '9'))//��һ������ĸ������
		{

			while ((v[i] >= 'a'&&v[i] <= 'z') || (v[i] >= 'A'&&v[i] <= 'Z') || (v[i] >= '0'&&v[i] <= '9'))
			{
				if (v[i] >= 'A'&&v[i] <= 'Z')
					v[i] += 32;

				ci2[kk] += v[i];
				i++;
			}
			while (!(v[i] >= 'a'&&v[i] <= 'z') && !(v[i] >= 'A'&&v[i] <= 'Z') && !(v[i] >= '0'&&v[i] <= '9') && v[i] != '\n'&&i < le2)
			{
				ci2[kk] += v[i];
				i++;
			}
			if (v[i] == '\n')ci2[++kk] = '\n';//���з�������

			i--;
			kk++;
		}
		else continue;
	}

	for (int i = 0; i < kk; i++)
	{
		int flag1 = 0;
		int flag2 = 0;

		for (int j = 0; j < 4; j++)
		{
			if (!(ci2[i][j] >= 'a'&& ci2[i][j] <= 'z'))
			{
				flag2 = 1;//�жϵ�һ���Ƿ���ϵ��ʹ淶
				break;
			}
		}

		if (flag2 == 0)//��һ������
		{
			strcpy_s(temp_cizu.word, 500, ci2[i].c_str());
			temp_cizu.count = 1;

			for (int j = 1; j < m; j++)
			{
				int flag3 = 0;
				for (int f = 0; f < 4; f++)
				{
					if (!(ci2[i + j][f] >= 'a'&& ci2[i + j][f] <= 'z'))
					{
						flag3 = 1;//�жϺ󼸸��Ƿ���ϵ��ʹ淶
						i = i + j;
						break;
					}
				}

				if (flag3 == 0)//�󼸸����Ϸ�
				     strcat_s(temp_cizu.word, 500, ci2[i + j].c_str());//
				else { flag1 = 1; break; }
			}

			if (flag1 == 0) //����
			{
				int a = strlen(temp_cizu.word)  - 1;//ȥ����β�ķ���

				while (!(temp_cizu.word[a] >= 'a'&&temp_cizu.word[a] <= 'z') && !(temp_cizu.word[a] >= '0'&&temp_cizu.word[a] <= '9'))
				{

					temp_cizu.word[a] = '\0';//
					a--;
				}

				int h, j = t;
				for (h = 0; h < j; h++)//��ͬ�Ĵʸ����ۼ�
				{
					if (strcmp(temp_cizu.word, cizu[h].word) == 0) 

					{
						cizu[h].count++;

						break;
					}


				}

				if (t == 0 || h == j)//�´������µĿռ�

				{
					cizu[t] = temp_cizu;

					t++;
				}
			}
			else continue;
		}
		else continue;
	}


	//�������ȶ���

	for (int i = 0; i < t; i++)
	{
		tmp.push(cizu[i]);
	}

}

void MyCount::TitleAndAbstract(string filename)
{
	char ch;
	ifstream fin;
	fin.open(filename);//���ļ�

	if (!fin)
	{
		cout << "can not open file" << endl;
	}

	while (!fin.eof())
	{
		ch = fin.get();
		if (ch == '\n')
		{
			ch = fin.get();
			if (ch == 'T')
			{
				for (int i = 0; i <= 6; i++)
					ch = fin.get();

				while (ch != '\n')
				{
					title_str += ch;
					ch = fin.get();
				}
				title_str += ch;
			}
		
		}
		if (ch == '\n')
		{
			ch = fin.get();
			if (ch == 'A')
			{
				for (int i = 0; i < 10; i++)
					ch = fin.get();

				while (ch != '\n' && !fin.eof())
				{
					abstract_str += ch;
					ch = fin.get();
				}
				if (ch == '\n')
					abstract_str += ch;
			}

		}

	}
	fin.close();
}
string MyCount::get_abstract()
{
	return abstract_str;
}

string MyCount::get_title()
{
	return title_str;
}

void MyCount::print(string outfile, string str, int n)//������ļ�
{
	int x = 0;
	ofstream outf;
	outf.open(outfile);

	outf << "characters: " << countChars(str) << endl;
	outf << "words: " << countWords(str) << endl;
	outf << "lines: " << countLines(str) << endl;

	while (!tmp.empty() && x < n)//���ǰn������
	{
		outf << "<" << tmp.top().word << ">: " << tmp.top().count << endl;
		tmp.pop();
		x++;
	}
	outf.close();
}