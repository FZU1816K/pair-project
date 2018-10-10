#include"Word_Fre.h"


typedef pair<string, int> PAIR;
struct CmpByValue {
	bool operator()(const PAIR& lhs, const PAIR& rhs) {
		return lhs.second > rhs.second;
	}
};

int Word_Fre(char * filename,char * outfile,int w,int m,int n)
{	
	map<string, int> Word_Num_map;
	int i;
		
		int word_group;
		word_group = m;
		
	int quanzhong = 1;  
	char ch;
	FILE *file;
	fopen_s(&file, filename, "rt");
	int flag = 0;			// state of DFA   in 0 1 2 3 4
	int huiche = 0;
	string word;
		string word_array[20];
		int wn = 0; 
		int re_word_num = m;

	for (; (ch = fgetc(file)) != EOF;)				//Determine the word and insert map
	{
		if (ch == '\n')//换行初始化。
		{
			wn = 0;
			re_word_num = m;
		}
		if (w == 1)    //赋值权重
		{
			if (ch == '\n')
			{
				huiche++;
				if (huiche % 5 == 1)
				{
					while ((ch = fgetc(file)) != ':');
					quanzhong = 10;
				}
				if (huiche % 5 == 2)
				{
					while ((ch = fgetc(file)) != ':');
					quanzhong = 1;
				}
			}
			
		}	
		if ('A' <= ch && ch <= 'Z')
			ch = ch + 32;
		if (flag == 0) {
			if (ch >= 'a'&&ch <= 'z') { flag = 1;	word = word + ch; }
			else if (ch >= '0'&&ch <= '9') { wn = 0;	re_word_num=m; }
		}
		else if (flag == 1) {
			if (ch >= 'a'&&ch <= 'z') { flag = 2;	word = word + ch; }
			else { flag = 0; word = ""; wn = 0;	re_word_num = m;}
		}
		else if (flag == 2) {
			if (ch >= 'a'&&ch <= 'z') { flag = 3;	word = word + ch; }
			else { flag = 0; word = ""; wn = 0;	re_word_num = m;}
		}
		else if (flag == 3) {
			if (ch >= 'a'&&ch <= 'z') { flag = 4;	word = word + ch; }
			else { flag = 0; word = ""; wn = 0;	re_word_num = m;}
		}
		else if (flag == 4) {
			if (ch >= 'a'&&ch <= 'z' || (ch >= '0'&&ch <= '9')) { word = word + ch; }
			else {
				word_array[wn % 20] = word;
				wn++;
				re_word_num--;
				word = "";
				if (re_word_num == 0)
				{
					for (int j = m; j > 1; j--)
						word = word + word_array[(wn - j) % 20]+" ";
					word = word + word_array[(wn - 1) % 20];
					Word_Num_map[word] = Word_Num_map[word] + quanzhong;
					re_word_num = 1;
				}
				word = "";
				flag = 0;
			
			}
		}
	}

	if (flag == 4) {
		re_word_num--;
		word_array[wn % 20] = word;
		wn++;
		if (re_word_num == 0)
		{
			for (int j = m; j > 1; j--)
				word = word + word_array[(wn - j) % 30] + " ";
			word = word + word_array[(wn - 1) % 30];
			Word_Num_map[word] = Word_Num_map[word] + quanzhong;
		}
	
	}

	vector <PAIR> Word_Num_vec(Word_Num_map.begin(), Word_Num_map.end());
	sort(Word_Num_vec.begin(), Word_Num_vec.end(), CmpByValue());
		


	FILE * stream;
	freopen_s(&stream, outfile, "a", stderr);
	
	if(Word_Num_vec.size()<n)
		for (int i = 0; i != Word_Num_vec.size(); ++i) {
			const char *ss = Word_Num_vec[i].first.c_str();
			//cout << ss << ":" << Word_Num_vec[i].second << endl;
			fprintf(stream, "<%s>: %d\n", ss, Word_Num_vec[i].second);
			
			//outfile <<"<"<< ss << ">"<<":" << Word_Num_vec[i].second << endl;);
		}
	else
		for (int i = 0; i != n; ++i) {
			const char *ss = Word_Num_vec[i].first.c_str();
			fprintf(stream, "<%s>: %d\n", ss, Word_Num_vec[i].second);

		}
	Word_Num_vec.clear();
	
	fclose(file);
	return 0;
}
