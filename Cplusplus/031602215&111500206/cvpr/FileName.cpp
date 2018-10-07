#include<FileName.h>

string FileName(string dir)
{
	string search = "/";
	int pos = 0;
	while ((pos = dir.find(search, pos)) != string::npos) {
		dir.replace(pos, search.size(), "_");
		pos++;
	}
	return dir;
}