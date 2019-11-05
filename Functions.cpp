#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>
using namespace std;

	vector<string> split(string s, string delimiter){
		size_t start=0, end, dlen = delimiter.length();
		string token;
		vector<string> res;
		while ((end = s.find(delimiter, start)) != string::npos){
			token = s.substr(start, end - start);
			start = end + dlen;
			res.push_back(token);
		}
		res.push_back(s.substr(start));
		return res;
}

int main(){
int monthToCalculate = 1; 
int dayToCalculate = 2;
ifstream f("fakedata.csv"); //opening the file for reading
if (f.fail()){
	cout<<"Could not open file.\n";
	return(1);
}
//IGNORE
//char ch;
//	ch = f.peek();
//	if (ch == '1951'){cin.ignore(1,'1951');}
//for (int lineno = 0; f.getline(ch, 256) && lineno < 3; lineno++){
//	f.ignore(ch);
//	}

char fline[256];
char delim = '\n';
char ddel = '-';
double temp;
vector<double> temps;
int entries=0;
while (f.getline(fline, 256, delim)) 
{
vector<string> v = split(fline, ";");
for (int i = 0; i < v.size(); i++){
//cout << v[i] << " " << endl;
}
temp = atof(v[2].c_str()); //turns string into double
//cout << temp << endl;
vector<string> date = split(v[0], "-");
//cout << date[0] << " , " << date[1] << " , " << date[2] << endl;
int year;
int month;
int day;
istringstream(date[0]) >> year;
istringstream(date[1]) >> month;
istringstream(date[2]) >> day;
if (month == monthToCalculate && day == dayToCalculate){
	cout << " The temperature on " <<month<<"/"<<day << " was " << v[2] << " degrees" << endl; 
	temps.push_back(temp);
	entries++;
//	cout << temps[0] << endl;
	}
}
//cout << entries << endl;
for (int n = 0; n<temps.size(); n++){
	cout << temps[n] << endl;
	}
}

