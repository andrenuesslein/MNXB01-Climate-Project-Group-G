//This is the implementation file
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <TF1.h> // 1d function class
#include <TH1.h> // 1d histogram classes
#include <TGraph.h> //Graphing Classes
#include <TStyle.h>  // style object
#include <TMath.h>   // math functions
#include <TCanvas.h> // canvas object
#include "tempTrender.h"

using namespace std;


tempTrender::tempTrender(string filePath){
	cout << "The user supplied " << filePath << " as the path to the data file." << endl;
	FilePath = filePath;
}


void tempTrender::tempOnDay(int monthToCalculate, int dayToCalculate){
	//This is the way to generate the data vectors in every function.
	vector<double> year, month, day, time, temp;
	
	//Opening The File to be Read.
	ifstream f(FilePath.c_str());
	if (f.fail()){
		cerr<<"Could not open file.\n";
	}
	//Extract All Data
	Reader(f, year, month, day, time, temp);
	f.close();
	//Histogram that will contain the data from the csv files.
	TH1D* hist = new TH1D("Histogram","Temperature On a Day Throughout the Years; Temperature[#circC]; Entries", 300, -20,40);
	
	//Pruning the Data
	for (size_t i= 0;  i<month.size() ; i++){
		if (month.at(i) == monthToCalculate && day.at(i) == dayToCalculate){
					hist->Fill(temp.at(i)); 
					i++;
			}
		}

	TCanvas* c1 = new TCanvas("c1", "Temperature on a Given Day Throughout the Years", 900, 600);
	//double mean = hist->GetMean();
	//double stdev = hist->GetRMS();
	
	//Set color and the minimum at 0
	hist->SetFillColor(kBlue);
	hist->SetMinimum(0);
	//Fit it with a Gaussian
	hist->Fit("gaus");
	
	//Show Mean of fot and data (and other stuff)
	gStyle->SetOptStat(1111);
	gStyle->SetOptFit(1111);

	//Draw it and save it
	hist->Draw();	
	c1->SaveAs("TempOnDay.jpg");	
}

void tempTrender::tempPerDay(double Year, double Hour){
	//This is the way to generate the data vectors in every function.
	vector<double> year, month, day, time, temp;
	//Opening The File to be Read.
	ifstream f(FilePath.c_str());
	if (f.fail()){
		cerr<<"Could not open file.\n";
	}
	//Extract All Data
	Reader(f, year, month, day, time, temp);
	f.close();
	//TempPerDay
	TH1D* hist = new TH1D("Histogram","Temperature Throughout a Year; Day of the year; Temperature[#circC]", 357, 0, 356);	
	int bin=0;
	for (size_t i= 0;  i<time.size() ; i++){
		if ( year.at(i) == Year && time.at(i) == Hour){
			hist->SetBinContent(bin, temp.at(i));
			hist->SetBinError(bin, sqrt(abs(temp.at(i))));
			bin++;
		}
	}	
	TCanvas* b1 = new TCanvas("b1", "Temperature Throughout one year", 900, 600);
	//Set color
	hist->SetFillColor(kBlue);
	// Set ROOT drawing styles
	gStyle->SetOptStat(1111);
	gStyle->SetOptFit(1111);
	//Draw it and save it
	hist->Draw();	
	b1->SaveAs("TempThroughoutYear.jpg");
	
}

void tempTrender::hotCold(){
	vector<double> year, month, day, time, temp;
	//Opening The File to be Read.
	ifstream f(FilePath.c_str());
	if (f.fail()){
		cerr<<"Could not open file.\n";
	}
	//Extract All Data
	Reader(f, year, month, day, time, temp);
	f.close();
		
	//TH1D* hist = new TH1D("Histogram","Hottest Temperature in a Year; Day of the year; Temperature[#circC]", 357, 0, 356);	
	// This is the function
	vector< vector<double> > Data;
    
    ofstream myfile("LunchTempMatrix.txt");
    if (myfile.fail()){
		cerr<<"Could not open file.\n";
	}
	
    size_t Year = year.at(0); //Year we start from
    size_t LastYear =year.at(year.size()-1);
	for (Year;  Year<LastYear ; Year++){
		vector <double> Yrs;
		for (size_t k=0; k<temp.size(); k++){
			if (year.at(k) == Year && time.at(k) == 12.){
			Yrs.push_back(temp.at(k));
			myfile << temp.at(k) << ",";
			}
		}
		Data.push_back(Yrs);
		myfile << "\n";
	}
	
	myfile.close();
	
	//Once the above is working, we need to find minimum and maximum
	
}

void tempTrender::Seasons(double Hour){
	//This is the way to generate the data vectors in every function.
	vector<double> year, month, day, time, temp;
	
	//Opening The File to be Read.
	ifstream f(FilePath.c_str());
	if (f.fail()){
		cerr<<"Could not open file.\n";
	}
	//Extract All Data
	Reader(f, year, month, day, time, temp);
	f.close();
	//Seasons
	TCanvas* Seasons = new TCanvas("Seasons","Temperature fluctuations over time.");
	vector<double> t, TatHr;//time and Temp. at Hour
	double days;
	for (size_t i= 0;  i<time.size() ; i++){
		if ( time.at(i) == Hour){
			t.push_back(days);
			TatHr.push_back(temp.at(i));
			days++;	
		}
	}
	TGraph* Graph= new TGraph(days, &t[0], &TatHr[0]);
	Graph->SetTitle("Temperature over Time; Time (Days);Temperature[#circC]");
	Graph->Draw();		
}


void tempTrender::Reader(ifstream &file, vector<double> &v1, vector<double> &v2, vector<double> &v3, vector<double> &v4, vector<double> &v5){
	string s, date="-", semi=";";
	int start=0, i=0;

	while (getline(file, s, '\n')){
		if (start>0){
			split(v1, s, date);
			split(v2, s, date);
			split(v3, s, semi);
			split(v4, s, semi);
			split(v5, s, semi);
		}
		
		if (s.find("Datum") != string::npos){ //This statement can be used to find locations where the variable in the find() field, useful for time.
			start++;
		}
	}
}

			
void tempTrender::split(vector<double> &vect, string &s, string &delimiter){
		size_t start=0, end, dlen = delimiter.length();
		double var;
		string token;
		if ((end = s.find(delimiter, start )) != string::npos){
			token = s.substr(start, end - start);
			stringstream SD(token);
			SD>>var;
			start = end + dlen;
			vect.push_back(var);
			s = s.substr(start);
		}
}


