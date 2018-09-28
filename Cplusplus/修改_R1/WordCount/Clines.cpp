#include<iostream>
#include<fstream>
#include<string>
#include "Clines.h"
using namespace std;

Line::Line() {}

Line::Line(string filein, string fileout)
{
	finname = filein;
	number = 0;
	foutname = fileout;
}

int Line::get()
{
	return number;
}

void Line::count()
{
	ifstream fin;
	if (finname == "")
	{
		printf("You must input file name first at initialization time.\n");
		return;
	}
	fin.open(finname);
	if (!fin.is_open())
	{
		cerr << "Could not open " << finname << endl;
		fin.clear();
	}
	string buffer;
	while (fin.good())
	{
		getline(fin,buffer);
		int i = buffer.size();
		if (i != 0)
			while (--i)
			{
				if (buffer[i] != ' '&& buffer[i] != '\n')
				{
					number++; break;
				}
			}
	}
	if (fin.eof()) {}
	else if (fin.fail())
		printf("Input terminated by data mismatch.\n");
	else
		printf("Input terminated for unknown reason.\n");
	fin.close();
}

void Line::show()
{
	printf("lines: %d\n", number);
}

void Line::fwrite()
{
	ofstream fout;
	fout.open(foutname, ios::out | ios::app); //׷��
	if (!fout.is_open())
	{
		cerr << "Cant't open" << foutname << endl;
		exit(EXIT_FAILURE);
	}
	fout << "lines: " << number << endl;
	fout.close();
}