#include<iostream>
#include<fstream>
#include<string>
#include "Ccharacter.h"
using namespace std;

Character::Character() {}

Character::Character(string filein, string fileout)
{
	finname = filein;
	number = 0;
	foutname = fileout;
}

int Character::Get()
{
	return  number;
}
void Character::Count()
{
	ifstream fin;
	fin.open(finname);
	if (!fin.is_open())
	{
		cerr << "Could not open " << finname << endl;
		fin.clear();
	}
	fin >> noskipws;
	char c;
	fin >> c;
	while (fin.good())
	{
		if ((c >= 32 && c <= 254)||c==' '||c=='\t'||c=='\n')//Visible ASCII characters plus spaces, horizontal tabs, line breaks.
			++number;
		fin >> c;
	}
	if (fin.eof()) {}
	else if (fin.fail())
		printf("Input terminated by data mismatch.\n");
	else
		printf("Input terminated for unknown reason.\n");
	fin.close();
}

void Character::Adjust(int line)                       //Without manual annotation
{
	number = number - line / 2 * 21;
}

void Character::Show()
{
	printf("characters: %d\n", number);
}

void Character::Fwrite()
{
	ofstream fout;
	fout.open(foutname, ios::out | ios::app);
	if (!fout.is_open())
	{
		cerr << "Cant't open" << foutname << endl;
		exit(EXIT_FAILURE);
	}
	fout << "characters: " << number << endl;
	fout.close();
}