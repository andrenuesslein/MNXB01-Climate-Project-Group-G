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

void delete_lines(const char *file_name, int n){
	
	ifstream is(file_name);
	ofstream ofs;
	ofs.open("temp.csv", ofstream::out);
	char c;
	int line_no=1;
	while (is.get(c)){
		if(c == '\n'){
		line_no++;}
		if (line_no > n){
		ofs << c;}
		}
//		cout << line_no << endl;
		ofs.close();
		is.close();
		remove(file_name);
		rename("temp.csv", file_name);
	}

int main(){
delete_lines("smhi-openda_Karlstad_1.csv", 12);
int monthToCalculate = 1; 
int dayToCalculate = 2;
ifstream f("smhi-openda_Karlstad_1.csv"); //opening the file for reading
if (f.fail()){
	cout<<"Could not open file.\n";
	return(1);
}
f.ignore(256, '\n');
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

