#include <string>
#include <vector>

using namespace std;

class PhraseCmp
{
public:
	bool operator()(pair<string, int> &a, pair<string, int> &b) 
	{
		if (a.second != b.second) return a.second > b.second;
		else return a.first < b.first;
	}
};