//This is the implementation file
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


//We can pass by pointers within here and set the year/month/day/etc for each dataset
//Alternatively create a function that will 
tempTrender::tempTrender(string filePath) {
	cout << "The user supplied " << filePath << " as the path to the data file." << endl;
	FilePath = filePath;
}


void tempTrender::tempOnDay(int monthToCalculate, int dayToCalculate){
	
	//Create Vectors to contain all data.
	vector<double> year, month, day, time, temp;
	//Indexing value for the constructed vectors.
	int i=0, start=0;
	//Creating a value which will continually be overwritten by the string value
	double OverWriteDouble=0.0;
	
	//Opening The File to be Read.
	ifstream f(FilePath.c_str());
	if (f.fail()){
		cerr<<"Could not open file.\n";
	}
	
	//Histogram that will contain the data from the csv files.
	TH1D* hist = new TH1D("Histogram","Temperature On a Day Throughout the Years; Temperature[#circC]; Entries", 300, -20,40);
	
	//Pruning the Data
	while (getline(f, s, '\n')){
		if (s.find("Datum") != std::string::npos){
			start++;
		}
		if (start>0){
			getline(f, s, '-');
				VectorConstructor(year, s);	
			getline(f, s, '-');
				VectorConstructor(month, s);	
			getline(f, s, ';');
				VectorConstructor(day, s);	
			getline(f, s, ';');
				VectorConstructor(time, s);
			getline(f, s, ';');
				VectorConstructor(temp, s);
			f.ignore(400, '\n');
			if (month.at(i) == monthToCalculate && day.at(i) == dayToCalculate){
					hist->Fill(temp.at(i)); 
			}
			i++;
		}
	}
	f.close();
	TCanvas* c1 = new TCanvas("c1", "Temperature on a Given Day Throughout the Years", 900, 600);
	//double mean = hist->GetMean();
	//double stdev = hist->GetRMS();
	
	//Set color and the minimum at 0
	hist->SetFillColor(kBlue);
	hist->SetMinimum(0);
	//Fit it with a Gaussian
	hist->Fit("gaus");

	//Draw it and save it
	hist->Draw();	
	c1->SaveAs("TempOnDay.jpg");	
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


void tempTrender::VectorConstructor(vector<double> &vect, string &s){
			double OverWriteDouble=0.0;
			stringstream VtoD(s);
			VtoD>>OverWriteDouble;
			vect.push_back(OverWriteDouble);
}


