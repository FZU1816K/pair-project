#include"init.h"

int init(int argc, char **argv)
{
	/* open ttt.txt*/
	if (argv[1] == NULL) {    //命令窗口没有输入
		cout << "Sorry,there is not file existd!" << endl;
		return -1;
	}
	if (argv[6] != NULL) {   //命令窗口输入过多（超过5个），不符合题意 
		cout << "Sorry,there are too many orders!" << endl;
		return -1;
	}
	return 0;
}