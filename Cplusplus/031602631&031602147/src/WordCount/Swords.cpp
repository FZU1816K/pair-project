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
bool Wsort::Get_Empty()
{
	return word_v.empty();
}

int Wsort::Get()
{
	return word_v.at(0).second;
}
/*************************************************/

void Wsort::CS()
{
	std::map<std::string, int> word_count;
	ifstream fin;
	fin.open(finname);
	if (!fin.is_open())
	{
		cerr << "Could not open " << finname << endl;
		fin.clear();
	}
	string word;
	char c;
	short int flag = -1;                       //Is title or abstract
	short int matchflag = 0;                   //Match the number of title and abstract,just like stack
	fin >> noskipws;
	while (fin.good())
	{
		fin >> c;
		if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122)) //Is number or letter
		{
			if (c >= 65 && c <= 90)
				c += 32;
			word.push_back(c);
		}
		else                                                                       //Judge can be a word or not
		{
			if (word.length() >= 4)
			{
				if ((word[0] >= 97 && word[0] <= 122) && (word[1] >= 97 && word[1] <= 122) && (word[2] >= 97 && word[2] <= 122) && (word[3] >= 97 && word[3] <= 122))
				{
					if (word == "title")
					{
						flag = 0;
						matchflag = 1;
					}
					else if (word == "abstract")
					{
						if (matchflag)              //Is 'Abstract' 
						{
							matchflag = 0;
							flag = 1;
						}
						else                        //Is 'abstract', in 'Abstract'
						{
							if (flag == 0 && weight == 1)
							{
								word_count[word] += 10;
							}
							else
								++word_count[word];
						}
					}
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

	//*********SORT**********//
	vector<PAIR>word_v1(word_count.begin(), word_count.end());
	sort(word_v1.begin(), word_v1.end(), CmpByValue());
	word_v = word_v1;
}


void Wsort::Show()
{
	for (int i = 0; i < word_v.size() && i < num; i++)
		cout << "<" << word_v.at(i).first << ">: " << word_v.at(i).second << endl;
}

void Wsort::Fwrite()
{
	ofstream fout;
	fout.open(foutname, ios::out | ios::app);
	if (!fout.is_open())
	{
		cerr << "Cant't open" << foutname << endl;
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < word_v.size() && i < num; i++)
		fout << "<" << word_v.at(i).first << ">: " << word_v.at(i).second << endl;
	fout.close();
}