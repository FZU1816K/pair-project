#include "ParaJudge.h"
#include <sstream>
#include <iostream>


ParaJudge::ParaJudge()
{
	weight = 0;
	phraseLength = 1;
	sortNum = 10;
}

ParaJudge::~ParaJudge()
{
}

void ParaJudge::judgePara_w(int num)
{
	if (num != 0 && num != 1)
	{
		cerr << "-wָ���������" << endl;
		exit(1);
	}
	weight = num;
}

void ParaJudge::judgePara_m(int num)
{
	if (num < 2 || num > 10)
	{
		cerr << "-mָ���������" << endl;
		exit(1);
	}
	phraseLength = num;
}

void ParaJudge::judgePara_n(int num)
{
	if (num < 0 || num > 100)
	{
		cerr << "-nָ���������" << endl;
		exit(1);
	}
	sortNum = num;
}

void ParaJudge::paraJudge(int &argc, char *argv[])
{
	bool has_i = false;
	bool has_o = false;
	bool has_w = false;
	bool has_m = false;
	bool has_n = false;

	string temp;
	stringstream stream;
	int num;

	if (argc % 2 == 0 || argc < 7)
	{
		cerr << "�����в�����ʽ����" << endl;
		exit(1);
	}

	for (int i = 1; i < argc; i += 2)
	{
		temp = argv[i + 1];
		if (!strcmp("-i", argv[i]))
		{
			if (has_i)
			{
				cerr << "�ظ�����-iָ��" << endl;
				exit(1);
			}
			has_i = true;
			input = temp;
		}
		else if (!strcmp("-o", argv[i]))
		{
			if (has_o)
			{
				cerr << "�ظ�����-oָ��" << endl;
				exit(1);
			}
			has_o = true;
			output = temp;
		}
		else if (!strcmp("-w", argv[i]))
		{
			if (has_w)
			{
				cerr << "�ظ�����-wָ��" << endl;
				exit(1);
			}
			has_w = true;
			stream << temp;
			stream >> num;
			stream.clear();
			judgePara_w(num);
		}
		else if (!strcmp("-m", argv[i]))
		{
			if (has_m)
			{
				cerr << "�ظ�����-mָ��" << endl;
				exit(1);
			}
			has_m = true;
			stream << temp;
			stream >> num;
			stream.clear();
			judgePara_m(num);
		}
		else if (!strcmp("-n", argv[i]))
		{
			if (has_n)
			{
				cerr << "�ظ�����-nָ��" << endl;
				exit(1);
			}
			has_n = true;
			stream << temp;
			stream >> num;
			stream.clear();
			judgePara_n(num);
		}
		else
		{
			cerr << "ָ�����" << endl;
			exit(1);
		}
	}

	if (!has_i || !has_o || !has_w)
	{
		cerr << "�����в�����ʽ����" << endl;
		exit(1);
	}
}

string ParaJudge::getInput()
{
	return input;
}

string ParaJudge::getOutput()
{
	return output;
}

int ParaJudge::getWeight()
{
	return weight;
}

int ParaJudge::getPhraseLength()
{
	return phraseLength;
}

int ParaJudge::getSortNum()
{
	return sortNum;
}