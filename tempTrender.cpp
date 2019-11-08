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

void tempTrender::tempPerDay(double YearToRead, double Hour){
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
		if ( year.at(i) == YearToRead && time.at(i) == Hour){
			hist->SetBinContent(bin, temp.at(i));
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

void tempTrender::Seasons(double Hour){
	//This is the way to generate the data vectors in every function.
	vector<double> year, month, day, time, temp;

	//Opening The File to be Read.
	ifstream f("datasets/smhi-openda_Karlstad.csv");
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

void tempTrender::VectorConstructor(vector<double> &vect, string &s){
			double OverWriteDouble=0.0;
			stringstream VtoD(s);
			VtoD>>OverWriteDouble;
			vect.push_back(OverWriteDouble);
}


void tempTrender::Reader(ifstream &file, vector<double> &v1, vector<double> &v2, vector<double> &v3, vector<double> &v4, vector<double> &v5){
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


