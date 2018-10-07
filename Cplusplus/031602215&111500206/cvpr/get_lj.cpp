#include<get_lj.h>
#include<something.h>
vector<string> abstract(vector<string> lj)
{
	regex pattern("(<dt class=\"ptitle\"><br><a href=\")(.*)(\">)(.*)(</a></dt>)");
	smatch result;

	fstream file;
	string line; //  Read line by line
	file.open(openfile1);
	while (getline(file, line))
	{
		if (regex_match(line, result, pattern) == true) {
			lj.push_back(result[2]);
		}
	}
	cout << lj.size() << endl;
	return lj;
}