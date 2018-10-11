#include "stdafx.h"
#include "File.h"
using namespace std;

bool cmp(int a, int b)
{
	return a > b;
}
void File::open(char *in_file, char *out_file)//����������ļ�
{
	infile.open(in_file, ios::in);
	outfile.open(out_file, ios::out);
	if (infile.fail()&& outfile.fail())
	{
		f_open = 3;
		cout << "��������ļ��򿪴���" << endl;
		exit(1);
	}
	if (infile.fail())
	{
		f_open = 1;
		cout << "�����ļ��򿪴���" << endl;
		exit(1);
	}
	if (outfile.fail())
	{
		f_open=2;
		cout << "����ļ��򿪴���" << endl;
		exit(1);
	}
}
void File::close()//�ر���������ļ�
{
	infile.close();
	outfile.close();
}
void File::output(int cnum, int wnum, int lnum, map<string, int> word,int temp)//��ͳ����Ϣд������ļ�
{
	int n = 0;
	int t;
	int num = 0;
	//int test = 0;
	if (temp < 0)
	{
		n = 10;
	}
	else
	{
		n = temp;
	}
	//cout << "n=" << n << endl;
	outfile << "characters: " << cnum << endl;
	//cout << "characters: " << cnum << endl;
	outfile << "words: " << wnum << endl;
	//cout << "words: " << wnum << endl;
	outfile << "lines: " << lnum << endl;
	//cout << "lines: " << lnum << endl;
	map<string, int>::iterator it;
	for (it = word.begin(); it != word.end(); it++)
	{
		t = (*it).second;
		a.push_back(t);
		num++;
		//test=test+ (*it).second;
	}
	//cout << test<<endl;
	sort(a.begin(), a.end(), cmp);
	for (int i = 0; i < num && i < n; i++)//�޸Ĳ���
	{
		t = a[i];
		for (it = word.begin(); it != word.end(); it++)
		{
			if ((*it).second == t)
			{
				outfile << "<" << (*it).first << ">: " << t << endl;
				//cout << "<" << (*it).first << ">: " << t << endl;
				(*it).second = 0;
				break;
			}
		}
	}
}
