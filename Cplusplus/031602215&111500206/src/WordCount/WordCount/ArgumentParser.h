#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

/*
* Function name: stringIsNum / stringIsPositiveInteger
* Description:
*	Test if a string meets the requirement
* Return:
*   stringIsNum return true of false
*   stringIsPositiveInteger will also return the integer if str is a positive integer.
*/
bool stringIsNum(string str);

int stringIsPositiveInteger(string str);

/*
* Function name: Parse_Args
* Description:
*	Parse the command line argument.
* Parameter:
*	@argc: command line argument
*	@argv: command line argument
* Return:
*	@int: 0 if parse correctly, otherwise negetive values and display information.
*/
int Parse_Args(int argc, char **argv);
