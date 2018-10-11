#include "pch.h"
#include "work_2.h"
using namespace std;
int j;

Wordnode *log_list[HASH_LENGTH] = { NULL };  //��ϣɢ��ָ������
int main(int argc, char *argv[])
{

	File fnew;                 //�����ļ�ģ��
	Words wnew;                //���Ƶ���ģ��
	vector<string> file_str;
	int i,v;
	for (v = 1; v < argc; v++)
	{
		if (argv[v][0] == '-' && strlen(argv[v]) == 2)
		{
			if (argv[v][1] == 'i')
			{
				if (v + 1 < argc)
				{
					strcpy_s(fnew.file_name, argv[v + 1]);
					fnew.i_flag = 1;
					v = v + 1;
				}
			}
			else if (argv[v][1] == 'o')
			{
				if (v + 1 < argc)
				{
					strcpy_s(fnew.out_file_name, argv[v + 1]);
					fnew.o_flag = 1;
					v = v + 1;
				}
			}
			else if (argv[v][1] == 'w')
			{
				if (v + 1 < argc)
				{
					fnew.w_flag = 1;
					if (argv[v + 1][0] == '0')
						fnew.weight = 0;
					else if (argv[v + 1][0] == '1')
						fnew.weight = 1;
					else
						cout << "error for weight!" << endl;
					v = v + 1;
				}
			}
			else if (argv[v][1] == 'm')
			{
				if (v + 1 < argc)
				{
					fnew.m_flag = 1;
					fnew.count_m = atoi(argv[v + 1]);
					if (fnew.count_m == 0)
					{
						cout << "error for m!" << endl;
						return 0;
					}
					v = v + 1;
				}

			}
			else if (argv[v][1] == 'n')
			{
				if (v + 1 < argc)
				{
					fnew.n_flag = 1;
					fnew.count_n = atoi(argv[v + 1]);
					if (fnew.count_n == 0)
					{
						cout << "error for n!" << endl;
						return 0;
					}
					v = v + 1;
				}

			}
		}
	}
	if (fnew.n_flag == 0)
		fnew.count_n = 10;
	if (fnew.i_flag == 0 || fnew.o_flag == 0 || fnew.w_flag == 0)
	{
		cout << "parameters error!" << endl;
		return 0;
	}
	ifstream f;
	f.open(fnew.file_name, ios::in);		//���ļ�
	if (!f.is_open())						//����ļ��Ƿ����
	{
		cout << "can't open this file!" << endl;
		return 0;
	}
	fnew.count_chars = C_chars(f, fnew, wnew,file_str);	//�����ַ���(����)
	fnew.count_words = C_words(f, fnew,wnew, log_list ,file_str);	//���㵥����(�����ϣ�ڵ�)
	//cout << "chars = " << fnew.count_chars << "," << "lines = " << fnew.count_lines<<","<<"words = "<<fnew.count_words<<endl;
	rank_word(log_list, wnew,fnew);						//��Ƶ����
	ofstream fo;
	fo.open(fnew.out_file_name, ios::out);			//����ļ�
	if (!fo.is_open())							//����ļ��Ϸ��Լ��
	{
		cout << "can't output the file!" << endl;
		return 0;
	}
	fo << "characters: " << fnew.count_chars << "\n";	//����������
	fo << "words: " << fnew.count_words << "\n";
	fo << "lines: " << fnew.count_lines << "\n";
	for (i = 1; i <= fnew.count_n; i++)
	{
		if (wnew.count_rank[i] != 0)
		{
			fo << "<" << wnew.word_rank[i] << ">: " << wnew.count_rank[i] << "\n";
		}
		else
			break;
	}
	f.close();
	fo.close();								//�ر��ļ�
	cout << "WordCount complete!" << endl;

	return 0;

}