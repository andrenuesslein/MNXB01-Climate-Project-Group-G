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

//What does this function do?
void tempTrender::tempOnDay(int monthToCalculate, int dayToCalculate){
{
	int integer;
	
	ifstream myFile("smhi-openda_Karlstad.csv");

	if (!myFile.is_open())
	{
		cout << "File is open" << endl;
	}

	vector<string> year(430000);
	vector<string> month(430000);
	vector<string> day(430000);
	vector<string> time(430000);
	vector<string> temp(430000);
	vector<string> test(10);
	vector<int> x(10);
	int vectorSize= 430000;
	int counter = 0;
	int m=0;
	
	TH1D* hist = new TH1D("Histogram","Temperature On a Day Throughout the Years; Temperature[#circC]; Entries", 300, -20,40);

	while (myFile.good())
	{

		for (int j=0; j<10 ; j++)
		{
			myFile.ignore(5000, '\n');
			
		}		
		
		do
		{	
			getline(myFile, test[m], '\n');
			stringstream geek(test[m]);
			geek >> x[m];
			cout << x[m] << endl;
			m++;
				
		}
		while( x.at(m) != 0 );
		
		
		
		
		 	
	
		for (int i=0; i < vectorSize ; i++)
		{
	 

			getline(myFile, year[i], '-');
			getline(myFile, month[i], '-');
			getline(myFile, day[i], ';');
			getline(myFile, time[i], ';');
			getline(myFile, temp[i], ';');
			myFile.ignore(400, '\n');
			
				double y=0.;
				stringstream yeek(month.at(i));
				yeek >> y;
			
				double z=0.;
				stringstream zeek(day.at(i));
				zeek >> z;
				
			if (y == monthToCalculate && z == dayToCalculate){
				double x=0.;
				stringstream geek(temp.at(i));
				geek >> x;
				hist->Fill(x); //Going to become redundant as we make a function to take a vector and fill a histogram.
			}

		}
	
		
	}

	TCanvas* c1 = new TCanvas("c1", "Temperature on a Day Throughout the Years", 900, 600);
	double mean = hist->GetMean();
	double stdev = hist->GetRMS();


	//Style Settings
	gStyle->SetOptStat(0); //Let's make our plots look a bit better. Get rid of the stat box
	gStyle->SetOptTitle(0); //Get rid of the title (good plots use legends instead)
	gStyle->SetTitleSize(0.05, "x"); //Use bigger text on the axes
	gStyle->SetTitleSize(0.05, "y");
	gStyle->SetLabelSize(0.05, "x"); //Use bigger labels too
	gStyle->SetLabelSize(0.05, "y");
	gStyle->SetPadTopMargin(0.05); //Change the margins to fit our new sizes
	gStyle->SetPadRightMargin(0.05);
	gStyle->SetPadBottomMargin(0.16);
	gStyle->SetPadLeftMargin(0.16);
	
	//Set color and the minimum at 0
	hist->SetFillColor(kBlue);
	hist->SetMinimum(0);
	//Fit it with a Gaussian
	hist->Fit("gaus");

	//Draw it and save it
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

