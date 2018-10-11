#include "pch.h"
#include "work_2.h"
bool Letter_test(char &chr_test)
{
	return chr_test <= 'z' && chr_test>='a';	//×ÖÄ¸ÅĞ¶Ï
}

void reset_string(string &str)
{
	str = "";
}

bool Number_test(char &chr_test)
{
	return chr_test <= '9' && chr_test >= '0';	//Êı×ÖÅĞ¶Ï
}


int C_chars(istream &fl, File &fn, Words &wn,vector <string> &str_lines)
{
	int count_chr = 0,i;
	string buffer_line;
	string lower_letter_str;
	char chr;					//µ¥×Ö·ûÅĞ¶Ï
	while (1)
	{
		chr = fl.get();
		count_chr++;
		if (chr == EOF)
		{
			count_chr -= 1;		//±ÜÃâ½áÎ²×Ö·û
			if (buffer_line.size() > 0)
			{
				transform(buffer_line.begin(), buffer_line.end(), buffer_line.begin(), ::tolower);	//Ğ¡Ğ´×ÖÄ¸×ª»»
				str_lines.push_back(buffer_line);
			}break;
		}
		buffer_line += chr;
		if (buffer_line[0] == '\n'&&buffer_line.size() == 1)
		{
			count_chr = count_chr - 1;
		}
		if (chr == '\n')
		{
			buffer_line = buffer_line.substr(0, buffer_line.size() - 1);
			transform(buffer_line.begin(), buffer_line.end(), buffer_line.begin(), ::tolower);		//Ğ¡Ğ´×ÖÄ¸×ª»»
			if (!(buffer_line[0] <= '9'&&buffer_line[0] >= '0'))
			{
				str_lines.push_back(buffer_line);
			}
			else
			{
				count_chr = count_chr - buffer_line.size() - 1;
				//cout <<buffer_line[0]<<"  "<< buffer_line.size() << endl;
			}
			

			reset_string(buffer_line);																//ÖØÖÃĞÂĞĞ
		}
	}
	fn.count_chars = count_chr;
	return count_chr;
}




