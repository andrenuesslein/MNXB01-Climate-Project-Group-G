#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <TF1.h> // 1d function class
#include <TH1.h> // 1d histogram classes
#include <TStyle.h>  // style object
#include <TMath.h>   // math functions
#include <TCanvas.h> // canvas object
#include "tempTrender.h"

using namespace std;

//This is the implementation file

tempTrender::tempTrender(string filePath) {
	cout << "The user supplied " << filePath << " as the path to the data file." << endl;
	cout << "You should probably store this information in a member variable of the class. Good luck with the project! :)" << endl;
}

void tempTrender::tempOnDay(int monthToCalculate, int dayToCalculate){



delete_lines("smhi-openda_Karlstad_1.csv", 12);
ifstream f("smhi-openda_Karlstad_1.csv"); //opening the file for reading
if (f.fail()){
	cout<<"Could not open file.\n";
}

TH1D* hist = new TH1D("Histogram","Temperature On a Day Throughout the Years; Temperature[#circC]; Entries", 300, -20,40);

f.ignore(256, '\n');
char fline[256];
char delim = '\n';
char ddel = '-';
double temp;
vector<double> temps;
while (f.getline(fline, 256, delim)) 
{
vector<string> v = split(fline, ";");
temp = atof(v.at(2).c_str()); //turns string into double

vector<string> date = split(v.at(0), "-");
int year;
int month;
int day;
istringstream(date[0]) >> year;
istringstream(date[1]) >> month;
istringstream(date[2]) >> day;
if (month == monthToCalculate && day == dayToCalculate){
	temps.push_back(temp);
	hist->Fill(temp); //Going to become redundant as we make a function to take a vector and fill a histogram.
	}
}
f.close();

TCanvas* c1 = new TCanvas("c1", "Temperature on a Day Throughout the Years", 900, 600);
double mean = hist->GetMean();
double stdev = hist->GetRMS();

hist->SetFillColor(kRed);
hist->SetMinimum(0);

hist->Draw();	
c1->SaveAs("TempOnDayHist.jpg");	
}

vector<std::string> tempTrender::split(string s, string delimiter){
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

void tempTrender::delete_lines(const char *file_name, int n){
	
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

