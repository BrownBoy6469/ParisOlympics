/******************************************************************************

File: main.cpp
Author: Prof. Lupoli & Andrew Nemec
Date: 2/16/2021
Section: 
E-mail: slupoli@tamu.edu
Description:
This file contains C++  code that will simulate data collected from a track 
event with 9 lanes. The code will sort the order, then display the results

Updates
Author: J. Michael Moore & Paul Taele

Data File Information
name: data.text
content: The text file will contain data in the constant form of:
<Time (double)> <Abbreviated Country (String)> <Uniform number (int)> <Lastname (String)>
32.7 USA 12 Moore
36.5 RUS 35 Polsley
45.8 ENG 73 Teale
52.34 CHN 14 Nemec
76.45 ITY 23 Lupoli     

*******************************************************************************/

#include <iostream>
#include "parallel_tracks.h"

using std::cin; using std::cout; using std::endl;
using std::string; using std::getline; using std::ifstream;
using std::invalid_argument; using std::domain_error;

int main()
{
    // TODO: create arrays needed
	double timeArray[SIZE] = {};
    string countryArray[SIZE] = {};
    unsigned int numberArray[SIZE] = {};
    string lastnameArray[SIZE] = {};
    unsigned int rankArray[SIZE] = {};

    // TOTO: prep all arrays
	prep_double_array(timeArray);
    prep_string_array(countryArray);
    prep_unsigned_int_array(numberArray);
    prep_string_array(lastnameArray);
    prep_unsigned_int_array(rankArray);

    // TODO: prompt until both the file and the contained data are valid
	string file = "";
    bool isInvalidFile = true;
    while(isInvalidFile) {
        cout << "Enter file name: ";
        cin >> file;
        try {
            get_runner_data(file, timeArray, countryArray, numberArray, lastnameArray);
            isInvalidFile = false;
        } 
        catch(std::invalid_argument& e) {
            cout << "Invalid File: " << e.what() << endl;
        } 
        catch(std::domain_error& e) {
            cout << "Invalid File: " << e.what() << endl;
        }

    }

    // TODO: determine ranking, notice the rank array receives the results
    get_ranking(timeArray, rankArray);
    /* for(int i = 0; i < SIZE; i++) {
        cout << rankArray[i] << endl;
    } */
    // TODO: Output results
    print_results(timeArray, countryArray, lastnameArray, rankArray);

    return 0;
}

