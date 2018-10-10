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
		if ((c >= 32 && c <= 254) || c == ' ' || c == '\t' || c == '\n')//Visible ASCII characters plus spaces, horizontal tabs, line breaks.
			++number;
		fin >> c;
	}
	if (fin.eof()) {}
	else if (fin.fail())
		printf("Input terminated by data mismatch.\n");
	else
		printf("Input terminated for unknown reason.\n");
	fin.close();
	/************/
	
	int lastnumber = 0;
	fin.open(finname);
	short int flag = 1;
	fin.seekg(0, ios::end); // Locate to end of file
	while (flag)
	{
		
		fin.seekg(-1, ios::cur); 
		c = fin.peek();
		if (c >= 32 && c <= 254)
		{
			flag = 0;
		}
		if (c == '\n')
		{
			lastnumber++;
		}
	}

	fin.close();
	if (lastnumber > 3)
	{
		number = number - (lastnumber - 3);
	}
	else if (lastnumber < 3)
	{
		number = number + (3 - lastnumber);
	}
	/******/
}

void Character::Adjust(int line)                       //Without manual annotation
{	
	int n = line / 2;
	if (n<= 10)
	{
		number = number - line / 2 * 21;
		if (number < 0) number = 0;
	}
	else if (11 <= n && n <= 100)
	{
		number = number - (n-10) * 22-210;
	}
	else if (101 <= n && n <= 1000)
	{
		number = number - (n - 100) * 23 - 1980 - 210;
	}
	else
	{
		number = number - (n - 100) * 24 - 20700 - 1980 - 210;
	}
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