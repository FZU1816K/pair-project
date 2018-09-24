#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

bool stringIsNum(string str);
/*
* Function name: Parse_Args
* Description:
*	Parse the command line argument.
* Parameter:
*	@argc: command line argument
*	@argv: command line argument
* Return:
*	@int: 0 if parse correctly, otherwise -1 and display information.
*/
int Parse_Args(int argc, char **argv);
