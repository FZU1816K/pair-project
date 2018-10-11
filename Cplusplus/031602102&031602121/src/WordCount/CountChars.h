#pragma once
#include <string>
#include <iostream>
#include<fstream>
#include <stdlib.h>
using namespace std;
int CountChars(char *filename)
{
	char word[1000000];
	int num=0; int k = 0;
	string a;
	ifstream in(filename);
	while (in.getline(word, 1000000))
	{   
		int nums = atoi(word);	
		a = word;
		if (nums >= 0 && nums <= 1000 && a.length()<5)k++;
		num += a.length();
		
	}
	num -= (k * 17);
	return num;
}