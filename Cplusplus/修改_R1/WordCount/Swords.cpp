#include<iostream>
#include<fstream>
#include<string>
#include<map>
#include<cctype>
#include<algorithm>
#include<vector>
#include "Swords.h"
using namespace std;


Wsort::Wsort() 
{
	finname = "input.txt";
	foutname = "result.txt";
	weight = 0;
	num = 10;
}

Wsort::Wsort(string filein, string fileout,int w, int number)
{
	finname = filein;
	foutname = fileout;
	weight = w;
	num = number;
}


typedef pair<string, int> PAIR;

struct CmpByValue {
	bool operator()(const PAIR& lhs, const PAIR& rhs) {
		return lhs.second > rhs.second;
	}
};

/*************************************************/
 //Ϊ�˲��Զ�����д�ĺ�����ʵ�ʲ�����Ҫ
bool Wsort::get_empty()
{
	return word_v.empty();
}

int Wsort::get()
{
	return word_v.at(0).second;
}
/*************************************************/

void Wsort::CS()
{
	std::map<std::string, int> word_count;//������.size()�ж���������С
											 //map���ؼ�����������
	ifstream fin;
	fin.open(finname);
	if (!fin.is_open())
	{
		cerr << "Could not open " << finname << endl;
		fin.clear();
	}
	string word;
	char c;
	int flag = -1;
	fin >> noskipws; //���Ź�һ���ַ�
	while (fin.good())
	{
		fin >> c;
		if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122)) //����ĸ����
		{
			if (c >= 65 && c <= 90)
				c += 32;
			word.push_back(c);
		}
		else //�ж��ܷ���ɵ���
		{
			if (word.length() >= 4)
			{
				if ((word[0] >= 97 && word[0] <= 122) && (word[1] >= 97 && word[1] <= 122) && (word[2] >= 97 && word[2] <= 122) && (word[3] >= 97 && word[3] <= 122))
				{
					if (word == "title")
						flag = 0;
					else if (word == "abstract")
						flag = 1;
					else
					{
						if (flag == 0 && weight == 1)
						{
							word_count[word]+=10;
						}
						else
							++word_count[word];
					}
				}
			}
			word = "";
		}
	}
	if (fin.eof()) {}
	else if (fin.fail())
		printf("Input terminated by data mismatch.\n");
	else
		printf("Input terminated for unknown reason.\n");
	fin.close();

	//*********����**********//
	vector<PAIR>word_v1(word_count.begin(), word_count.end());
	sort(word_v1.begin(), word_v1.end(), CmpByValue());
	word_v = word_v1;
}


void Wsort::show()
{
	for (int i = 0; i < word_v.size() && i < num; i++)
		cout << "<" << word_v.at(i).first << ">: " << word_v.at(i).second << endl;
}

void Wsort::fwrite()
{
	ofstream fout;
	fout.open(foutname, ios::out | ios::app); //׷��
	if (!fout.is_open())
	{
		cerr << "Cant't open" << foutname << endl;
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < word_v.size() && i < num; i++)
		fout << "<" << word_v.at(i).first << ">: " << word_v.at(i).second << endl;
	fout.close();
}