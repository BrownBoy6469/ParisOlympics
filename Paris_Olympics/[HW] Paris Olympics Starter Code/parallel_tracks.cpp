#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <limits>
#include "parallel_tracks.h"

using std::string;


//-------------------------------------------------------
// Name: get_runner_data
// PreCondition:  the prepped parallel arrays , and a legit filename is pass
// PostCondition: all arrays contain data from the text file given
//---------------------------------------------------------
void get_runner_data( const std::string& file, double timeArray[], std::string countryArray[], 
		unsigned int numberArray[], std::string lastnameArray[]) 
{
  	// Get data from file and check if file is valid
	std::ifstream fin(file);
  	string lineArray[SIZE] = {};
	int len = SIZE;
	int i = 0;
  	if(!(fin.is_open())) {
		throw std::invalid_argument("Cannot open file");
  	}
  	else {
		for(i = 0; i < len; i++) {
			getline(fin, lineArray[i]);
		}
  	}


	// Throw domain error is data is missing
	/* for(i = 0; i < len; i++) {
		std::cout << lineArray[i] << std::endl;
		std::cout << lineArray[i].length() << std::endl;
	} */
	for(i = 0; i < len; i++) {
		if(lineArray[i].length() < 10) {
			throw std::domain_error("File missing data");
		}
	}


	// Get the times and put them into the timeArray
	// Throw domain error for invalid arguments
	for(i = 0; i < len; i++) {
		int spaceIndex = lineArray[i].find(' ');
		string time = lineArray[i].substr(0, spaceIndex);
		if(time.length() == 1) {
			throw std::domain_error("File contains invalid data (time)");
		}
		for(long unsigned int digit = 0; digit < time.length(); digit++) {
			if(isalpha(time[digit]) or time[digit] == '-') {
				throw std::domain_error("File contains invalid data (time)");
			}
		}
		timeArray[i] = std::stod(time);
		lineArray[i].erase(0, spaceIndex + 1);
		if(timeArray[i] < 0) {
			throw std::domain_error("File contains invalid data (time)");
		}
	}
	/* for(i = 0; i < len; i++) {
		std::cout << timeArray[i] << std::endl;
		std::cout << lineArray[i] << std::endl;		
	} */
	

	// Get the country names and put them into the countryArray
	// Throw domain error for invalid arguments
	for(i = 0; i < len; i++) {
		int spaceIndex = lineArray[i].find(' ');
		string country = lineArray[i].substr(0, spaceIndex);
		if(country.length() != 3) {
			throw std::domain_error("File contains invalid data (country)");
		}
		for(long unsigned int letter = 0; letter < country.length(); letter++) {
			if(!(isalpha(country[letter]))) {
				throw std::domain_error("File contains invalid data (country)");
			}
			else if(!(isupper(country[letter]))) {
				throw std::domain_error("File contains invalid data (country)");
			}
		}
		countryArray[i] = country;
		lineArray[i].erase(0, spaceIndex + 1);
	}
	/* for(i = 0; i < len; i++) {
		std::cout << countryArray[i] << std::endl;
		std::cout << lineArray[i] << std::endl;		
	} */


	// Get the runner numbers and put them into the numberArray
	// Throw domain error for invalid arguments
	for(i = 0; i < len; i++) {
		int spaceIndex = lineArray[i].find(' ');
		string number = lineArray[i].substr(0, spaceIndex);
		if(number.length() != 1 and number.length() != 2) {
			throw std::domain_error("File contains invalid data (number)");
		}
		for(long unsigned int digit = 0; digit < number.length(); digit++) {
			if(isalpha(number[digit]) or number[digit] == '-' or number[digit] == '.') {
				throw std::domain_error("File contains invalid data (number)");
			}
		}
		numberArray[i] = std::stoi(number);
		lineArray[i].erase(0, spaceIndex + 1);
	}
	/* for(i = 0; i < len; i++) {
		std::cout << numberArray[i] << std::endl;
		std::cout << lineArray[i] << std::endl;		
	} */

	// Get the last names and put them into the lastnameArray
	// Throw domain error for invalid arguments
	for(i = 0; i < len; i++) {
		string name = lineArray[i];
		name = trim(name);
		if(name.length() == 1 or name.length() == 0) {
			throw std::domain_error("File contains invalid data (name)");
		}
		for(long unsigned int letter = 0; letter < name.length(); letter++) {
			if(!(isalpha(name[letter]))) {
				if(!(name[letter] == ' ')) {
					throw std::domain_error("File contains invalid data (name)");
				}
			}
		}
		lastnameArray[i] = name;
	}
	/* for(i = 0; i < len; i++) {
		std::cout << lastnameArray[i] << std::endl;
	} */
}

//-------------------------------------------------------
// Name: prep_double_array
// PreCondition:  a double arrays is passed in
// PostCondition: data in the array is 'zeroed' out
//---------------------------------------------------------
void prep_double_array(double ary[])
// making sure all values within the array are set to 0.0;
{	
	int len = SIZE;
	for(int i = 0; i < len; i++) {
		ary[i] = 0.0;
	}
}

//-------------------------------------------------------
// Name: prep_double_array
// PreCondition:  an unsigned int arrays is passed in
// PostCondition: data in the array is 'zeroed' out
//---------------------------------------------------------
void prep_unsigned_int_array(unsigned int ary[])
// making sure all values within the array are set to 0;
{
	int len = SIZE;
	for(int i = 0; i < len; i++) {
		ary[i] = 0;
	}
}

//-------------------------------------------------------
// Name: prep_string_array
// PreCondition:  a string arrays is pass in
// PostCondition: data in the array is "N/A" out to determine if
// a value has changed
//---------------------------------------------------------
void prep_string_array(std::string ary[])
// making sure all values within the array are set to "N/A";
{
	int len = SIZE;
	for(int i = 0; i < len; i++) {
		ary[i] = "N/A";
	}
}

//-------------------------------------------------------
// Name: get_ranking
// PreCondition:  just the time array is passed in, and has valid data
// PostCondition: after a very inefficient nested loop to determine the placements 
// and places the ranks in a new array. That new array is returned
//---------------------------------------------------------
void get_ranking(const double timeArray[], unsigned int rankArray[])
{
	int len = SIZE;
	int i = 0;	
	double ninth = 0;
	double eighth = 0;
	double seventh = 0;
	double sixth = 0;
	double fifth = 0;
	double fourth = 0;
	double third = 0;
	double second = 0;
	double first = 0;

	for(i = 0; i < len; i++) {
		if(timeArray[i] > ninth) {
			ninth = timeArray[i];
		}
	}

	first = ninth;
	for(i = 0; i < len; i++) {
		if(timeArray[i] < first) {
			first = timeArray[i];
		}
	}

	eighth = first;
	for(i = 0; i < len; i++) {
		if(timeArray[i] > eighth and timeArray[i] != ninth) {
			eighth = timeArray[i];
		}
	}

	second = eighth;
	for(i = 0; i < len; i++) {
		if(timeArray[i] < second and timeArray[i] != first) {
			second = timeArray[i];
		}
	}

	seventh = second;
	for(i = 0; i < len; i++) {
		if(timeArray[i] > seventh and timeArray[i] != ninth and timeArray[i] != eighth) {
			seventh = timeArray[i];
		}
	}

	third = seventh;
	for(i = 0; i < len; i++) {
		if(timeArray[i] < third and timeArray[i] != first and timeArray[i] != second) {
			third = timeArray[i];
		}
	}

	sixth = third;
	for(i = 0; i < len; i++) {
		if(timeArray[i] > sixth and timeArray[i] != ninth and timeArray[i] != eighth and timeArray[i] != seventh) {
			sixth = timeArray[i];
		}
	}

	fourth = sixth;
	for(i = 0; i < len; i++) {
		if(timeArray[i] < fourth and timeArray[i] != first  and timeArray[i] != second and timeArray[i] != third) {
			fourth = timeArray[i];
		}
	}

	for(i = 0; i < len; i++) {
		if(timeArray[i] != first and timeArray[i] != second and timeArray[i] != third and timeArray[i] != fourth 
		and timeArray[i] != sixth and timeArray[i] != seventh and timeArray[i] != eighth and timeArray[i] != ninth) {
			fifth = timeArray[i];
		}
	}

	for(i = 0; i < len; i++) {
		if(timeArray[i] == first) {
			rankArray[i] = 1;
		}
		else if(timeArray[i] == second) {
			rankArray[i] = 2;
		}
		else if(timeArray[i] == third) {
			rankArray[i] = 3;
		}
		else if(timeArray[i] == fourth) {
			rankArray[i] = 4;
		}
		else if(timeArray[i] == fifth) {
			rankArray[i] = 5;
		}
		else if(timeArray[i] == sixth) {
			rankArray[i] = 6;
		}
		else if(timeArray[i] == seventh) {
			rankArray[i] = 7;
		}
		else if(timeArray[i] == eighth) {
			rankArray[i] = 8;
		}
		else if(timeArray[i] == ninth) {
			rankArray[i] = 9;
		}
	}
}


//-------------------------------------------------------
// Name: print_results
// PreCondition:  almost all parallel arrays are passed in and have valid data
// PostCondition: after a very inefficient nested loop to determine the ranks
// it then displays then along with a delta in time from the start
//---------------------------------------------------------
void print_results(const double timeArray[], const std::string countryArray[],
		const std::string lastnameArray[], const unsigned int rankArray[])
{

	std::cout << "Final results!!";
	std::cout << std::setprecision(2) << std::showpoint << std::fixed << std::endl;
	double best_time = 0.0;
		
	// print the results, based on rank, but measure the time difference_type
	for(unsigned int j = 1; j <= SIZE; j++)
	{
		
		// go thru each array, find who places in "i" spot
		for(unsigned int i = 0; i < SIZE; i++)
		{
			if(rankArray[i] == 1) // has to be a better way, but need the starting time
			{
				best_time = timeArray[i];
			}
			
			
			if(rankArray[i] == j) // then display this person's data
			{
				// this needs precision display
				std::cout << "[" << j << "]  " << timeArray[i] << " " << std::setw(15) << std::left << lastnameArray[i] << "\t" << "(" << countryArray[i] << ")  +" << (timeArray[i] - best_time) << std::endl; 
			}
			
		}
	}	
}

std::string trim(std::string ret) {
	// remove whitespace from the beginning
	while (!ret.empty() && isspace(ret.at(0))) {
			ret.erase(0, 1);
		}

	// remove whitespace from the end
	//  Note: last index is (.size() - 1) due to 0 based indexing
	while (!ret.empty() && isspace(ret.at(ret.size()-1))) {
		ret.erase(ret.size()-1, 1);
	}
	
	return ret;
}