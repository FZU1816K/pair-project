#include "stdafx.h"

int main(int args,char* argv[])
{
	int p=1 ;
	int pp = 0;
	int cizulen = 1;
	/*
	m （2 ≤ m ≤ 10）个由分隔符隔开的单词组成一个词组，词组只存在于同一个字段中，
	即不能跨越 Title、Abstract 组成词组
	使用词组词频统计功能时，不再统计单词词频，
	而是统计词组词频，但不影响单词总数统计
	*/
	int diy = 10;//默认输出前十
	int weight = 0;//参数与数字 0|1 搭配使用，
	//用于表示是否采用不同权重：0 表示属于 Title、Abstract 的单词权重相同均为 1
    char* ipath=NULL;
	char* opath = NULL;
	while (argv[p] != NULL) {
		//printf("%d:%s\n", p,argv[p]);
		if (argv[p][0]!= '-') {
			//printf("%c\n", argv[p][0]);
			printf("错误输入格式\n");
			return -1;
		}
		else if(argv[p][1]=='i'){
			if (argv[p + 1] == NULL) {
				printf("缺少输入路径\n");
				return -1;
			}
			ipath = argv[p + 1];
			p=p+2;
			continue;
		}
		else if (argv[p][1] == 'o') {
			if (argv[p + 1] == NULL) {
				printf("缺少输出路径\n");
				return -1;
			}
			opath = argv[p + 1];
			p = p + 2;
			continue;
		}
		else if (argv[p][1] == 'n') {
			if (argv[p + 1] == NULL) {
				break;
			}
			if (isdigit(argv[p + 1][0]) == NULL) {
				p++;
			}
			else {
				diy = atoi(argv[p + 1]);
				p = p + 2;
			}
			continue;
		}
		else if (argv[p][1] == 'm') {
			if (argv[p + 1]== NULL) {
				break;
			}
			if (isdigit(argv[p + 1][0]) == NULL) {
				p++;
			}
			else {
				if (atoi(argv[p + 1]) < 2 || atoi(argv[p + 1]) > 10){
					printf("错误词组长度");
					return -1;
				}
				cizulen = atoi(argv[p + 1]);
				p = p + 2;
			}
			continue;
		}
		else if (argv[p][1] == 'w') {
			if (argv[p + 1] == NULL || (atoi(argv[p + 1])!=1 && atoi(argv[p + 1])!=0)) {
				printf("错误权重\n");
				return -1;
			}
			weight = atoi(argv[p + 1]);
			p = p + 2;
			continue;
		}
		else {
			printf("错误参数\n");
			return -1;
		}
	}
	//printf("cizulen:%d weight:%d diy:%d ipath:%s opath:%s\n", cizulen, weight, diy, ipath, opath);
	vector<pair<string, int>> tVector;
	ofstream fout(opath);
	ifstream input;
	input.open(ipath);
	if (input.fail())
	{
		cout << "文件不存在！" << endl;
		return 3;
	}
	input.close();

	int characters,words;
	//输出统计字符数
	characters = character(ipath);
	fout << "characters: " << characters << endl;
	//输出统计单词数
	words = word(ipath);
	fout << "words: " << words << endl;
	int lines = line(ipath);
	fout << "lines: " << lines << endl;
	//输出统计前十词频
	tVector=WordsFrequency(ipath,weight,cizulen);
	for (int i = 0; i<tVector.size(); i++)
	{
		if (i == diy)
			break;
		fout << "<" << tVector[i].first << ">" << ": " << tVector[i].second << endl;
	}
	fout.close();
	return 0;
}