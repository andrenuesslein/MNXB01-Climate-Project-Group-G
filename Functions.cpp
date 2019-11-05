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

//char ig = 'Tidsutsnitt:\n';
//f.ignore(256, ig);
char fline[256];
//char delm = ';';
//string delim = "\n";
char delim = '\n';
char ddel = '-';

while (f.getline(fline, 256, delim)) 
{
vector<string> v = split(fline, ";");
for (int i = 0; i < v.size(); i++){
//cout << v[i] << " " << endl;
}
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
	}
}


//for (int n=0; n <v.size(); n++){
//	date.at(n) = atoi(v.at(n))
//	cout << date[0] << endl;
//}	
//if (date[1] = monthToCalculate){
//cout << date[1] << endl;
//}
//for plotting:
//for (int i=0; i<n; i++){
//x[i] = v[0];
//y[i] = v[1];
//}	
//cout << x[n] << endl;	

}

