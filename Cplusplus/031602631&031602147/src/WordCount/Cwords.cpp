#include<iostream>
#include<fstream>
#include<string>
#include "Cwords.h"
using namespace std;

Word::Word() {}


Word::Word(string filein, string fileout)
{
	finname = filein;
	foutname = fileout;
	number = 0;
}

int Word::Get()
{
	return number;
}

void Word::Count()
{
	ifstream fin;
	fin.open(finname);
	if (!fin.is_open())
	{
		cerr << "Could not open " << finname << endl;
		fin.clear();
	}
	string word;
	char c;
	short int matchflag = 0;                           //Match the number of title and abstract,just like stack
	fin >> noskipws;
	while (fin.good())
	{
		fin >> c;
		if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122))  //Is number or letter
		{
			if (c >= 65 && c <= 90)
				c += 32;
			word.push_back(c);
		}
		else                                                                        //Judge can be a word or not
		{
			if (word.length() >= 4)
			{
				if ((word[0] >= 97 && word[0] <= 122) && (word[1] >= 97 && word[1] <= 122) && (word[2] >= 97 && word[2] <= 122) && (word[3] >= 97 && word[3] <= 122))
				{
					if (word == "title")
					{
						matchflag = 1;
					}
					else if (word == "abstract")
					{
						if (matchflag)          //Is 'Abstract' 
						{
							matchflag = 0;
						}
						else                    //Is 'abstract'
						{
							number++;
						}
					}
					else
					{
						number++;
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
}

void Word::Show()
{
	printf("words: %d\n", number);
}

void Word::Fwrite()
{
	ofstream fout;
	fout.open(foutname, ios::out | ios::app);
	if (!fout.is_open())
	{
		cerr << "Cant't open" << foutname << endl;
		exit(EXIT_FAILURE);
	}
	fout << "words: " << number << endl;
	fout.close();
}