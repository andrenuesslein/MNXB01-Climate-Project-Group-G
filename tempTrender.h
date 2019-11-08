#ifndef TEMPTRENDER_H
#define TEMPTRENDER_H

#include <string>
#include <vector>
//This is the file that will contain the list of data and function members
class tempTrender {
	//Path to File
	string FilePath;
	
	public:
	tempTrender(string filePath); //Construct using the specified file
	~tempTrender() {} //Destructor
	
	//Main Functions
	void tempOnDay(int monthToCalculate, int dayToCalculate); //Make a histogram of the temperature on this day
	void Seasons(double Hour); //Make Graph of Temperature on a given hour every day.
	
	
	//void tempOnDay(int dateToCalculate); //Make a histogram of the temperature on this date
	void tempPerDay(double YearToRead, double Hour); //Make a histogram of the average temperature of each day of the year
	//void hotCold(); //Make a histogram of the hottest and coldest day of the year
	//void tempPerYear(int yearToExtrapolate); //Make a histogram of average temperature per year, then fit and extrapolate to the given year
	
	
	//Auxiliary Functions
	void VectorConstructor(vector<double> &vect, string &s);
	void Reader(ifstream &file, vector<double> &v1, vector<double> &v2, vector<double> &v3, vector<double> &v4, vector<double> &v5);
	
	private:
	//Private Variables
	int monthToCalculate;
	int dayToCalculate;
	double Hour;
	double Year;
	double OverWriteDouble;
	vector<double> vect;
	string s;
	string delimiter;

};

#endif
