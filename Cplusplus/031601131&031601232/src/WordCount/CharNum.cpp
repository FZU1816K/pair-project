#include "CharNum.h"
#include<fstream>
#include<iostream>

int CharNum(char * filename)
{
	int count = 0;
	char ch;
	FILE *file;
	int huiche = 0;
	fopen_s(&file,filename, "rt");
	while ((ch = fgetc(file)) != EOF) {
		if (ch >= -1 && ch <= 255) {


			if (ch == '\n')
			{
				huiche++;
				if (huiche % 5 == 1)
				{
					while ((ch = fgetc(file)) != ' ');

					count -= 2;
				}
				if (huiche % 5 == 2)
				{
					while ((ch = fgetc(file)) != ' ');
				}
				if (huiche % 5 == 3 || huiche % 5 == 4)
					count--;
			}
			count++;
		}
	}
	fclose(file);
	return count;

	
}