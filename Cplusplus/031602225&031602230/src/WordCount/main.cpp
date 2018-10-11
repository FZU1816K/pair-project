#include "pch.h"
#include<iostream>
#include<sstream>
#include<string>
#include<queue>
#include<stdio.h>
#include<fstream>
#include"word_count.h"
using namespace std;


int main(int argc, char** argv)
{
	stringstream ss;
	string input_filename, output_filename;
	int weight = 0;
	int m = 1, n = 10;
	for (int i = 1; i < argc; i++)
	{
		string s;
		s = argv[i];
		if (s == "-i")input_filename = argv[i + 1];
		if (s == "-o")output_filename = argv[i + 1];
		if (s == "-m")
		{
			s = argv[i + 1];
			stringstream ss(s);
			ss >> m;
		}
		if (s == "-n")
		{
			s = argv[i + 1];
			stringstream ss(s);
			ss >> n;
		}
		if (s == "-w")
		{
			s = argv[i + 1];
			stringstream ss(s);
			ss >> weight;
		}
	}
	MyCount mycount;
	mycount.TitleAndAbstract(input_filename);
	string title_str = mycount.get_title();
	string abstract_str = mycount.get_abstract();
	string mystr = title_str + abstract_str;
	mycount.count(title_str, abstract_str, m, weight);
	mycount.print(output_filename, mystr, n);


	return 0;

}
