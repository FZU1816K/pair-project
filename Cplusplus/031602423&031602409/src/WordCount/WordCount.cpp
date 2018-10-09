#include "stdafx.h"

int main(int args,char* argv[])
{
	int p=1 ;
	int pp = 0;
	int cizulen = 1;
	/*
	m ��2 �� m �� 10�����ɷָ��������ĵ������һ�����飬����ֻ������ͬһ���ֶ��У�
	�����ܿ�Խ Title��Abstract ��ɴ���
	ʹ�ô����Ƶͳ�ƹ���ʱ������ͳ�Ƶ��ʴ�Ƶ��
	����ͳ�ƴ����Ƶ������Ӱ�쵥������ͳ��
	*/
	int diy = 10;//Ĭ�����ǰʮ
	int weight = 0;//���������� 0|1 ����ʹ�ã�
	//���ڱ�ʾ�Ƿ���ò�ͬȨ�أ�0 ��ʾ���� Title��Abstract �ĵ���Ȩ����ͬ��Ϊ 1
    char* ipath=NULL;
	char* opath = NULL;
	while (argv[p] != NULL) {
		//printf("%d:%s\n", p,argv[p]);
		if (argv[p][0]!= '-') {
			//printf("%c\n", argv[p][0]);
			printf("���������ʽ\n");
			return -1;
		}
		else if(argv[p][1]=='i'){
			if (argv[p + 1] == NULL) {
				printf("ȱ������·��\n");
				return -1;
			}
			ipath = argv[p + 1];
			p=p+2;
			continue;
		}
		else if (argv[p][1] == 'o') {
			if (argv[p + 1] == NULL) {
				printf("ȱ�����·��\n");
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
					printf("������鳤��");
					return -1;
				}
				cizulen = atoi(argv[p + 1]);
				p = p + 2;
			}
			continue;
		}
		else if (argv[p][1] == 'w') {
			if (argv[p + 1] == NULL || (atoi(argv[p + 1])!=1 && atoi(argv[p + 1])!=0)) {
				printf("����Ȩ��\n");
				return -1;
			}
			weight = atoi(argv[p + 1]);
			p = p + 2;
			continue;
		}
		else {
			printf("�������\n");
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
		cout << "�ļ������ڣ�" << endl;
		return 3;
	}
	input.close();

	int characters,words;
	//���ͳ���ַ���
	characters = character(ipath);
	fout << "characters: " << characters << endl;
	//���ͳ�Ƶ�����
	words = word(ipath);
	fout << "words: " << words << endl;
	int lines = line(ipath);
	fout << "lines: " << lines << endl;
	//���ͳ��ǰʮ��Ƶ
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