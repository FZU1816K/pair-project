#include<iostream>
#include<queue>
#include<fstream>
#include<cctype>
#include<algorithm>
#include "Phrase.h"
using namespace std;


Psort::Psort()
{
	finname = "input.txt";
	foutname = "result.txt";
	len = 2;
	num = 10;
}

Psort::Psort(string filein, string fileout, int length, int number)
{
	finname = filein;
	foutname = fileout;
	len = length;
	num = number;
}

typedef pair<string, int> PAIR;

struct CmpByValue {
	bool operator()(const PAIR& lhs, const PAIR& rhs) {
		return lhs.second > rhs.second;
	}
};

/*************************************************/
bool Psort::Get_Empty()
{
	return phrase_v.empty();
}

int Psort::Get()
{
	return phrase_v.at(0).second;
}
/*************************************************/

struct  PWord {
	string pw;
	short int f;      //Is letter£º1£»Is separator£º0 ; Is break point£º-1£» 
};

void Psort::PS()
{
	ifstream fin;
	fin.open(finname);
	if (!fin.is_open())
	{
		cerr << "Could not open " << finname << endl;
		fin.clear();
	}
    queue<PWord> phrase_t;                     //phrase of Title
	queue<PWord> phrase_a;                     //phrase of Abstract
	short int flag = -1;                       //Is title or abstract
	short int matchflag = 0;                   //Match the number of title and abstract,just like stack
	short int wordflag = 0;                    //The word before the separator is word or not  
	PWord word;                                //character
	word.f = 1;
	PWord separator;                           //separator
	separator.f = 0;
	PWord f;                                   //break point
	f.pw = "\0";
	f.f = -1;
	char c;
	fin >> noskipws;

	while (fin.good())
	{
		fin >> c;
		if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		{
			if (c >= 65 && c <= 90)
				c += 32;
			word.pw.push_back(c);

			//Judge separator, and join into phrase queue
			if (wordflag == 1 && separator.pw.length()>0)
			{
				if (flag == 0)
					phrase_t.push(separator);
				else if (flag == 1)
					phrase_a.push(separator);
			}
			separator.pw = "";
		}
		else
		{
			if (c != 13 && c != 10)
			{
				separator.pw.push_back(c);
			}

			//Judge word, and join into word queue
			if (word.pw.length() >= 4)
			{
				/**********************Is word******************************/
				if ((word.pw[0] >= 97 && word.pw[0] <= 122) && (word.pw[1] >= 97 && word.pw[1] <= 122) && (word.pw[2] >= 97 && word.pw[2] <= 122) && (word.pw[3] >= 97 && word.pw[3] <= 122))
				{
					if (word.pw == "title")
					{
						matchflag = 1;
						wordflag = 0;
						flag = 0;
						phrase_a.push(f);
					}
					else if (word.pw == "abstract")
					{
						if (matchflag)         //Is 'Abstract' 
						{
							matchflag = 0;
							wordflag = 0;
							flag = 1;
							phrase_t.push(f);
						}
						else                   //Is 'abstract'
						{
							wordflag = 1;
							if (flag == 0)
								phrase_t.push(word);
							else if (flag == 1)
								phrase_a.push(word);
						}
					}
					else
					{
						wordflag = 1;
						if (flag == 0)
							phrase_t.push(word);
						else if (flag == 1)
							phrase_a.push(word);
					}
				}
				else
				{
					if (flag == 0)
						phrase_t.push(f);
					else if (flag == 1)
						phrase_a.push(f);
					wordflag = 0;
				}
			}
			else if (word.pw.length() == 0)
			{

			}
			else
			{
				if (flag == 0)
					phrase_t.push(f);
				else if (flag == 1)
					phrase_a.push(f);
				wordflag = 0;
			}
			word.pw = "";
		}
	}
	if (fin.eof()) {}
	else if (fin.fail())
		printf("Input terminated by data mismatch.\n");
	else
		printf("Input terminated for unknown reason.\n");
	fin.close();


	//*****************For phrase************************//
	std::map<std::string, size_t> phrase_count;
	string P;
	P = "";      //Story phrase temporary

	///////////////////////////title////////////////////////////////
	short int start = 0;
	string::size_type p = NULL;

	short int flags = 0;
	while (!phrase_t.empty())
	{

		if (start == 1)
		{
			if (!flags)
			{
				P = P.substr(p);
			}
			PWord sign = phrase_t.front();
			phrase_t.pop();
			if (sign.f == -1)
			{
				start = 0;
				continue;
			}
			else if (sign.f == 1)
			{
				if ((P[P.size()] >= 48 && P[P.size()] <= 57) || (P[P.size()] >= 65 && P[P.size()] <= 90) || (P[P.size()] >= 97 && P[P.size()] <= 122))
				{
					P.append(" " + sign.pw);
				}
				else
				{
					P.append(sign.pw);
				}
				bool flagi = 1;
				for (int i = 0; i < P.size(); i++)
				{
					if (flagi)
					{
						if ((P[i] >= 48 && P[i] <= 57) || (P[i] >= 65 && P[i] <= 90) || (P[i] >= 97 && P[i] <= 122))
							continue;
						else
							flagi = 0;
					}
					else
					{
						if ((P[i] >= 65 && P[i] <= 90) || (P[i] >= 97 && P[i] <= 122))
						{
							p = i;
							break;
						}
						else
							continue;
					}
				}
				++phrase_count[P];
				flags = 0;
			}
			else //(sign.flag==0)
			{
				flags = 1;
				P.append(sign.pw);
			}
		}
		else
		{
			P = "";
			short int l = len;
			short int flagl = 0;
			flag = 1;
			while (l)
			{
				if (phrase_t.empty())
				{
					flag = 0;
					break;
				}
				PWord sign = phrase_t.front();
				phrase_t.pop();
				if (sign.f == -1)
				{
					flag = 0;
					flagl = 0;
					break;
				}
				else if (sign.f == 1)
				{
					if (flagl)
					{
						P.append(" " + sign.pw);
					}
					else
					{
						flagl = 1;
						P.append(sign.pw);
					}
					l--;
				}
				else //(sign.flag==0)
				{
					if (flagl)
					{
						flagl = 0;
						P.append(sign.pw);
					}
				}
			}
			if (flag)
			{
				++phrase_count[P];
				flags = 0;
				start = 1;
				bool flagi = 1;
				for (int i = 0; i < P.size(); i++)
				{
					if (flagi)
					{
						if ((P[i] >= 48 && P[i] <= 57) || (P[i] >= 65 && P[i] <= 90) || (P[i] >= 97 && P[i] <= 122))
							continue;
						else
							flagi = 0;
					}
					else
					{
						if ((P[i] >= 65 && P[i] <= 90) || (P[i] >= 97 && P[i] <= 122))
						{
							p = i;
							break;
						}
						else
							continue;
					}
				}
			}
		}
	}

	/////////////////////////abstract/////////////////////////////////
	start = 0;
	p = NULL;
	P = "";
	flags = 0;

	while (!phrase_a.empty())
	{
		
		if (start == 1)
		{
			if (!flags)
			{
				P = P.substr(p);
			}
			PWord sign = phrase_a.front();
			phrase_a.pop();
			if (sign.f == -1)
			{
				start = 0;
				continue;
			}
			else if (sign.f == 1)
			{
				if((P[P.size()] >= 48 && P[P.size()] <= 57) || (P[P.size()] >= 65 && P[P.size()] <= 90) || (P[P.size()] >= 97 && P[P.size()] <= 122))
				{
					P.append(" " + sign.pw);
				}
				else 
				{
					P.append(sign.pw);
				}
				bool flagi = 1;
				for (int i = 0; i < P.size(); i++)
				{
					if (flagi)
					{
						if ((P[i] >= 48 && P[i] <= 57) || (P[i] >= 65 && P[i] <= 90) || (P[i] >= 97 && P[i] <= 122))
							continue;
						else
							flagi = 0;
					}
					else
					{
						if ((P[i] >= 65 && P[i] <= 90) || (P[i] >= 97 && P[i] <= 122))
						{
							p = i;
							break;
						}
						else
							continue;
					}
				}
				++phrase_count[P];
				flags = 0;
			}
			else //(sign.flag==0)
			{
				flags = 1;
				P.append(sign.pw);
			}
		}
		else
		{
			P = "";
			short int l = len;
			short int flagl = 0;
			flag = 1;
			while (l)
			{
				if (phrase_a.empty())
				{
					flag = 0;
					break;
				}
				PWord sign = phrase_a.front();
				phrase_a.pop();
				if (sign.f == -1)
				{
					flag = 0;
					flagl = 0;
					break;
				}
				else if (sign.f == 1) 
				{
					if (flagl)
					{
						P.append(" " + sign.pw);
					}
					else
					{
						flagl = 1;
						P.append(sign.pw);
					}
					l--;
				}
				else //(sign.flag==0)
				{
					if (flagl)
					{
						flagl = 0;
						P.append(sign.pw);
					}
				}
			}
			if (flag)
			{
				++phrase_count[P];
				flags = 0;
				start = 1;
				bool flagi = 1;
				for (int i = 0; i < P.size(); i++)
				{
					if (flagi)
					{
						if ((P[i] >= 48 && P[i] <= 57) || (P[i] >= 65 && P[i] <= 90) || (P[i] >= 97 && P[i] <= 122))
							continue;
						else
							flagi = 0;
					}
					else
					{
						if ((P[i] >= 65 && P[i] <= 90) || (P[i] >= 97 && P[i] <= 122))
						{
							p = i;
							break;
						}
						else
							continue;
					}
				}
			}
		}
	}

	//*********Sort**********//
	vector<PAIR>phrase_v1(phrase_count.begin(), phrase_count.end());
	sort(phrase_v1.begin(), phrase_v1.end(), CmpByValue());
	phrase_v = phrase_v1;
}


void Psort::Show()
{
	for (int i = 0; i < phrase_v.size() && i < num; i++)
		cout << "<" << phrase_v.at(i).first << ">: " << phrase_v.at(i).second << endl;
}

void Psort::Fwrite()
{
	ofstream fout;
	fout.open(foutname, ios::out | ios::app);
	if (!fout.is_open())
	{
		cerr << "Cant't open" << foutname << endl;
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < phrase_v.size() && i < num; i++)
		fout << "<" << phrase_v.at(i).first << ">: " << phrase_v.at(i).second << endl;
	fout.close();
}