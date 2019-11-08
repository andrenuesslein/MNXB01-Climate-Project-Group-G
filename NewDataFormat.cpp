#include <iostream>
#include <vector>
#include <string>
#include <sstream> 
#include <fstream>
using namespace std;

void VectorConstructor(vector<double> &vect, string &s);
void Reader(ifstream &file, vector<double> &v1, vector<double> &v2, vector<double> &v3, vector<double> &v4, vector<double> &v5);

int main(){
	//This is the way to generate the data vectors in every function.
	vector<double> year, month, day, time, temp;
	
	//Opening The File to be Read.
	ifstream f("smhi-openda_Karlstad.csv");
	if (f.fail()){
		cerr<<"Could not open file.\n";
	}
	//Extract All Data
	Reader(f, year, month, day, time, temp);
	f.close();
}


void Reader(ifstream &file, vector<double> &v1, vector<double> &v2, vector<double> &v3, vector<double> &v4, vector<double> &v5){
	string s;
	int start=0;

	while (getline(file, s, '\n')){
		if (s.find("Datum") != string::npos){ //This statement can be used to find locations where the variable in the find() field, useful for time.
			start++;
		}
		if (start>0){
			getline(file, s, '-');
				VectorConstructor(v1, s);	
			getline(file, s, '-');
				VectorConstructor(v2, s);	
			getline(file, s, ';');
				VectorConstructor(v3, s);	
			getline(file, s, ';');
				VectorConstructor(v4, s);
			getline(file, s, ';');
				VectorConstructor(v5, s);
			file.ignore(400, '\n');
		}
	}
}

void VectorConstructor(vector<double> &vect, string &s){
			double OverWriteDouble;
			stringstream VtoD(s);
			VtoD>>OverWriteDouble;
			vect.push_back(OverWriteDouble);
}
