#include "LineNum.h"
int LineNum(char * filename)
{
	FILE *file;
	fopen_s(&file,filename, "rt");
	int count = 0;
	char ch;
	int flag = 0;
	int huiche = 0;

	for (; (ch = fgetc(file)) != EOF;) {
		if(ch=='\n')
		{	huiche++;
		
			if (huiche % 5 == 1)
			{
				while ((ch = fgetc(file)) != ' ');
				
			}
			if (huiche % 5 == 2)
			{
				while ((ch = fgetc(file)) != ' ');
			
			}
			ch = '\n';
		}
		//isspace
		if (flag == 0 && isascii(ch)) {
			flag = 1;
		}
	
		if (flag == 1 && ch == '\n') {
			
			if (huiche % 5 == 2 || huiche % 5 == 3)
			{
				count++;
				
			}

			flag = 0;
			
		}
	}
	if (flag == 1) {
	
		count++;
	}
	fclose(file);
	return count;
}
