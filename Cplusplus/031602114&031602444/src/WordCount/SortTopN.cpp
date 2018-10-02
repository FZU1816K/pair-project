#include"SortTopN.h"
#include"pch.h"
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#include<fstream>
#include<string>
#include<string.h>
#include<vector>
#include<map>
#include<cstdlib>
#pragma warning(disable: 4018)
#pragma warning(disable: 4477)
using namespace std;

void SortTopN(int N, map<string, int> &m0, vector<pair<string, int>>& x)
{
	vector<pair<string, int>> v(m0.begin(), m0.end());
	for (int i = 0; i < m0.size(); i++)
	{
		if (i == N) break;
		int max = 0;
		string maxword;
		int enflag = 0;
		for (vector<pair<string, int>>::iterator vec = v.begin(); vec != v.end(); vec++)
		{
			if (vec->second > max)
			{
				max = vec->second;//存下当前最大数单词
				maxword = vec->first;
			}
			else if (vec->second == max)//字典序
			{
				if (vec->first < maxword)
				{
					max = vec->second;//存下当前最大数单词
					maxword = vec->first;
				}
			}
		}

		if (max) x.push_back(make_pair(maxword, max));

		for (vector<pair<string, int>>::iterator vec = v.begin(); vec != v.end(); vec++)
		{
			if (vec->first == maxword)
			{
				vec->second = -1;
				break;
			}

		}
	}
}


void Display(vector<pair<string, int>>& x, ofstream &out_file)
{
	int vecflag = 0;

	for (vector<pair<string, int>>::iterator vec = x.begin(); vec != x.end(); vec++)
	{
		out_file << "<"<<vec->first<<">: " << vec->second << endl;
		vecflag++;
		//if (vecflag == N) break;
	}

}
