#include<iostream>
#include<string>
#include<fstream>
#include"init.h"
#include"CountChar.h" 
#include"CountLine.h" 
#include"CountWord.h" 
#include"WordFrequency.h"
#include"PhraseFrequency.h"

using namespace std;


int main(int argc,char **argv) {
	 
	int   flag_m = -1, flag_n = -1,flag_i=-1,flag_o=-1,flag_w=-1;
	int  m = 0, n = 0,judgevalue = 0;
	string input;
	string output;
	string buffer[20];
	for (int i = 0; i < argc; i++) {
		buffer[i] = argv[i];
		if (buffer[i] == "-i") {
			flag_i = i;
			input = argv[i + 1];
		}
		else if (buffer[i] == "-o") {
			flag_o = i;
			output = argv[i + 1];
		}
		else if (buffer[i] == "-w") {
			flag_w = i;
			judgevalue = atoi(argv[flag_w + 1]);

		}
		else if (buffer[i] == "-m") {
			flag_m = i;
			m = atoi(argv[flag_m + 1 ]) ;
		}
		else if (buffer[i] == "-n") {
			flag_n = i;
			n = atoi(argv[flag_n + 1]) ;
		}
	}
	int cnt_char=CountChar(argv[flag_i + 1]);
	int cnt_line=CountLine(argv[flag_i + 1]);
	int cnt_word=CountWord(argv[flag_i + 1]);
	ofstream fout(output, ios::app);
	fout << "characters: " << cnt_char << endl;
	fout << "words: " << cnt_word << endl;
	fout << "lines: " << cnt_line << endl;
	fout.close();
	if (flag_n == -1 && flag_m == -1) {                                        //未出现 - n 参数时，不启用自定义词频统计输出功能，默认输出10个
		int jj = 10;
		WordFrequency(input,output, judgevalue, jj);
	}	                                                                        
	if (flag_n != -1 && flag_m == -1) {                                        //未出现 - m 参数时，不启用词组词频统计功能，默认对单词进行词频统计
		int jj = n;
		WordFrequency(input,output, judgevalue, jj);
	}                                                                             
	if (flag_n != -1 && flag_m !=-1) {
		int jj = 10;
		PhraseFrequency(input, output,m,judgevalue,10 );
	} 
	if (flag_n == -1 && flag_m != -1) {
		PhraseFrequency(input, output, m, judgevalue,n);
	}
	
	return   0;
}

