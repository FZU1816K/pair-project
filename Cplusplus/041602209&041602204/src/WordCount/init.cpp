#include"init.h"

int init(int argc, char **argv)
{
	/* open ttt.txt*/
	if (argv[1] == NULL) {    //�����û������
		cout << "Sorry,there is not file existd!" << endl;
		return -1;
	}
	if (argv[6] != NULL) {   //�����������ࣨ����5���������������� 
		cout << "Sorry,there are too many orders!" << endl;
		return -1;
	}
	return 0;
}