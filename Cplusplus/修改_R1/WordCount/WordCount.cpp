/**************��������������WordCount******************/

#include<iostream>
#include<fstream>
#include<cstdlib>
#include"Ccharacter.h" //�����ַ���������Character
#include"Cwords.h" //���㵥�ʸ�������Word ������Ԥ����
#include"Clines.h" //������������Line
#include"Swords.h" //ͳ������10�����ʼ����Ƶ����Wsort ��ֻ��Ҫ����Cword�ٽ�������Ϳ����˰ɣ�
#include"Phrase.h" //ͳ�ƴ������

/////////////////////////////////////////////////////////
int main(int argc, char * argv[])  //����windows IDEʱʹ��
////////////////////////////////////////////////////////
//int main()                             //��Ԫ����ʱʹ��
////////////////////////////////////////////////////////
{
	using namespace std;

	struct Parameter {
		string inFile; /*-i option*/
		string outFile; /*-o option*/
		int weight; /*-w option*/
		int length; /*-m option*/
		int num; /*-n option*/
	}para;

	/*Initialization*/
	para.inFile = "";
	para.outFile = "";
	para.weight = 0;
	para.length = 0;
	para.num = 0;
	/*End of initialization*/

	int flagn = 0;
	int flagm = 0;

	for (int i = 1; i < argc; i++)
	{
		string s = argv[i];
		if (s == "-i")
		{
			i++;
			para.inFile = argv[i];
		}
		else if (s == "-o")
		{
			i++;
			para.outFile = argv[i];
		}
		else if (s == "-w")
		{
			i++;
			string ww = argv[i];
			para.weight = ww[0] - '0';
		}
		else if (s == "-m")
		{
			flagm = 1;
			i++;
			string mm = argv[i];
			for (int j = 0; j < mm.length(); j++)
			{
				para.length = para.length * 10 + (mm[j] - '0');
			}
		}
		else if (s == "-n")
		{
			i++;
			flagn = 1;
			string nn = argv[i];
			for (int j = 0; j < nn.length(); j++)
			{
				para.num = para.num * 10 + (nn[j] - '0');
			}
		}
		else
		{
			cout << s << endl;
			cerr << "��Ч����" << endl;
			exit(EXIT_FAILURE);
		}
	}
	if (!flagn)
		para.num = 10;

	/********************************************************/
	//   ����ʱʹ��   //
	//std::string f = "E:/Users/lenovo/Source/repos/input.txt";
	//std::string fout = "result.txt";
//	for (int i = 0; i < 10000; i++) {
	/*********************************************************/


	/******************************************************/
	//   ����windows IDEʱʹ��  //
	if (argc == 1)   //quit if no arguments
	{
		cerr << "Usage:" << argv[0] << "filename[s]\n";
		exit(EXIT_FAILURE);
	}
	if (argc < 7)
	{
		cerr << "Input too little filenames.\n";
		exit(EXIT_FAILURE);
	}
	/*
	for (int file = 1; file < argc; file++)
	{
		string f = argv[file];
	*/
	/*********************************************************/

	/*********************************************************/
		Character cc(para.inFile,para.outFile);
		Word cw(para.inFile,para.outFile);
		Line cl(para.inFile,para.outFile);
		Wsort sw(para.inFile,para.outFile,para.weight,para.num);                           /********����*********/
		Psort ps(para.inFile, para.outFile, para.length, para.num);                         /********����*********/
																					 ////////////////////////////////////////////////
		cc.count(); //�޲ε���
		cc.show();  //�޲ε���
		cc.fwrite();//�޲ε���
		////////////////////////////////////////////////
		cw.count();
		cw.show();
		cw.fwrite();
		////////////////////////////////////////////////
		cl.count();
		cl.show();
		cl.fwrite();
		////////////////////////////////////////////////
		if (!flagm)
		{
			sw.CS();
		    sw.show();
		    sw.fwrite();
		}
		////////////////////////////////////////////////
		if (flagm)
		{
			ps.PS();
		    ps.show();
		    ps.fwrite();
		}
		
	/**********************************************************/

//	}
	return 0;
}