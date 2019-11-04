#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

int main(){
int monthToCalculate, dayToCalculate;
ifstream f;
f.open("smhi-openda_Karlstad.csv"); //opening the file for reading
if (f.fail()){
	cout<<"Could not open file.\n";
	return(1);
}
string delm = ";";
string delim = "\n";
//Int_t date = 0;
//myReadLine.ignore(0,1951)
int i=0;
while (getline(f, delim)) 
{
	vector<string> datavec;
	datavec.push_back("Hi");
	cout << datavec[i] << endl;
	i++;
}
}
