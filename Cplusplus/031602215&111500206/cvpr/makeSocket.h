#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS
#include <Ws2tcpip.h>
#include "winsock2.h"  
#include <string>  
#include <iostream>  
#include <fstream>  
#include <vector>  
#include<tchar.h>
#include<locale>
#include<codecvt>
#include <time.h>  
#include <queue>  
#include <hash_set>  
#include <sstream>
#include <fstream>
#include <map>
#include <set>
#include <limits>
#include <regex>
#include <get_lj.h>

using namespace std;



int makeSocket(string host, int port);