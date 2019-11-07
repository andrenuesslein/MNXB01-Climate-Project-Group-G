void tempTrender::tempPerDay(int yearToPlot){
	ifstream f("smhi-openda_Karlstad_1.csv"); //opening the file for reading
	if (f.fail()){
		cout<<"Could not open file.\n";
	}
	
	TH1D* hist = new TH1D("Histogram","Temperature Throughout a Year; Day of the year; Temperature[#circC]", 357, 0, 356);
	
	f.ignore(256, '\n'); //we need to ignore the first line because it's empty
	char fline[256];
	double temp;
	vector<double> temps;
	
	int bin = 1;
	//read every line and only use the one with the correct year (and lunch time)
	while (f.getline(fline, 256, '\n')) {
		
		vector<string> v = split(fline, ";");
		temp = atof(v.at(2).c_str()); //turns string into double

		vector<string> date = split(v.at(0), "-");
		int year;
		istringstream(date[0]) >> year;
		
		vector<string> time = split(v.at(1), ":");
		int hour;
		istringstream(time[0]) >> hour;

		if (year == yearToPlot && hour == 12){
			temps.push_back(temp);
			hist->SetBinContent(bin, temp);
			//hist->SetBinError(bin, sqrt(temp.));
			++bin;
			}			
		}
	
	f.close();
	
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
 
