// WordCount.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include<stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "CharNum.h"
#include "LineNum.h"
#include"WordNum.h"
#include "Word_Fre.h"
using namespace std;

//int argc, char *argv[]
int main()
{	
	int n = 10;
	int word_m = 2;
	int word_w = 1;
	int i = 1;
	/*
	printf("%d\n", m);
	while (argv[i] != NULL)
	{
		printf("%d\n", m);
		printf("%s\n", argv[i]);
		if (argv[i]=="-m")
		{
			printf("%d\n", n);
			m = atoi(argv[i + 1]);
			printf("%d", m);

		}
		if (argv[i]== "-n")
		{
			n = atoi(argv[i + 1]);
			cout << "n为" << n << endl;
		}
		i++;
	}
	*/

/*	if (argv[1] == NULL)
	{

		printf("please input file!\n");
		return -1;

	}
	std::fstream file;
	file.open(argv[1]);
	if (!file) {

		printf("the file cannot open or no exist!\n");
		return -1;
	}

	file.close();*/
	
	char filename[100] = "D:\\input.txt";
	FILE * stream;
	freopen_s(&stream, "result.txt", "w", stderr);
	int Char_Number = CharNum(filename);
	int Lines_Number = LineNum(filename);
	int Words_Number = WordNum(filename);

	fprintf(stream, "characters: %d\n", Char_Number);
	fprintf(stream, "words: %d\n", Words_Number-Lines_Number);
	fprintf(stream, "lines: %d\n", Lines_Number);


	Word_Fre(filename, word_w,word_m,n);			//Word frequency statistics

	
	

	return 0;
}
