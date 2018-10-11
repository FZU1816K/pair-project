#pragma once
#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<string>
#include<algorithm>


/***************************************************************************************
**	功能：计算有效行数(排除序号)
**	输入参数：所被测试的文件名
**	返回变量：返回int整型变量，为所测试文件中有效行数量
**	算法：按行读取，空白行不计入行数
**	附加说明：编号行的排除，仅针对每行字符串首位和末尾均为数字便判定其为编号行
****************************************************************************************/
int LineCount(char *filename);
