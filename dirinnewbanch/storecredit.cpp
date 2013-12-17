//============================================================================
// Name        : storecredit.cpp
// Author      : Manikandan.B
// Version     : 1.0
// Copyright   : Freeware license terms
//				 Can be freely distributed for educational purposes
//				 All distribution and derivative works should carry the license terms
// Description : Solution to the Store Credit Puzzle from google code jam
//============================================================================

#define DEBUG_PRINT

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <vector>
#include <cassert>

const unsigned int BUFFSIZE = 4096;
char buffer[BUFFSIZE];

const unsigned int LINES_IN_FILE_FOR_EACH_CASE = 3;	// problem specific

// Each case will have the following data
// Modelled after the problem statement Store Credit
struct CaseData {
  unsigned int C; 	// Store credit
  unsigned int nbItems; // No. of items
  std::vector<int> prices;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * To read data from the input file
 */
void
read_data(const char* inputfile, std::vector<CaseData>& casevec) {

	/*
	 * Accepts an input file and reads data into a custom data structure
	 */

	std::ifstream finput(inputfile);
	if (!finput.is_open()) {
		std::cerr<<"ERROR OPENING INPUT FILE "<<inputfile<<std::endl;
		exit(-1);
	}

	std::string line;
	std::getline(finput, line);
	const unsigned int nbCases = atoi(line.c_str());
	std::cout<<"Number of cases = "<<nbCases<<std::endl;
	casevec.resize(nbCases);

	std::stringstream mystrstream;
	unsigned int reminder = 0;

	for(unsigned int count=0; count<nbCases; count++) {
		// For each case
		std::cout<<"--------------------------------Case number: "<<count+1<<std::endl;
		for (unsigned int lines = 0; lines<LINES_IN_FILE_FOR_EACH_CASE; lines++) {
			std::getline(finput, line);
			reminder = (lines+1)%LINES_IN_FILE_FOR_EACH_CASE;
			switch(reminder){
				case 1:	{
					// First line. Read the credit
					casevec.at(count).C = atoi(line.c_str());
					std::cout<<"C = "<<casevec.at(count).C<<std::endl;
					break;
				}
				case 2:	{
					// Second line is the No. of items
					casevec.at(count).nbItems = atoi(line.c_str());
					std::cout<<"NbItems = "<<casevec.at(count).nbItems<<std::endl;
					casevec.at(count).prices.resize(casevec.at(count).nbItems);				// Resize the price vector according to number of items
					break;
				}
				case 0: {
					// Last line
					// Move to a string stream and use its method to extract each space separated value
					mystrstream<<line;
					//for(unsigned int itemno = 0; itemno<casevec.at(count).nbItems; itemno++) {	// get each value separated by space
					unsigned int itemno = 0;
					while (mystrstream.getline(buffer, BUFFSIZE, ' ')) {
						casevec.at(count).prices.at(itemno) = atoi(buffer);
						std::cout<<"prices["<<itemno<<"] = "<<casevec.at(count).prices.at(itemno)<<"\t";
						itemno++;
					}
					std::cout<<std::endl;
					mystrstream.clear();		//Clear the eof flag
					break;
				}
			}
		}
	}
	finput.close();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * Main processing logic to find the 2 items that add up to the credit C
 */
void
find_items(const CaseData& casedata, unsigned int& ii, unsigned int& jj) {
	/*
	 * i and j are the 2 item's indices that add up to the credit C
	 *
	 */
	for (unsigned int i = 0; i<casedata.nbItems; i++)
		for (unsigned int j = 0; j<casedata.nbItems; j++)
			if (!(i==j))
				if ( (casedata.prices.at(i) + casedata.prices.at(j)) == casedata.C){
					// return indices in increasing order
					if (i<j) {
						ii = i+1;
						jj=j+1;
					}
					else {
						jj = i+1;
						ii = j+1;
					}
				}
}


int main(int argc, char* argv[]) {

  std::string inputfilename = "/local/mbakthav/_myCode/c++_personal_projects_workspace/storecredit/src/A-large-practice.in";

  /*			Read data from input file into a vector of custom data structure	*/
  std::vector<CaseData> casevec;
  read_data(inputfilename.c_str(), casevec);

  unsigned int nbCases = (int)casevec.size();
  std::cout<<"No. of cases from size of casevec: "<<nbCases<<std::endl;

  /* 			Main Part		*/
  std::string outfilename = "Output_large_practice.txt";
  std::ofstream fout(outfilename.c_str(), std::fstream::out);
  CaseData dat;
  unsigned int idx1 = 0;
  unsigned int idx2 = 0;
  for (unsigned int c=0; c<nbCases; c++) {
	  dat = casevec.at(c);
	  find_items(dat,idx1,idx2);
	  std::cout<<"Case #"<<(c+1)<<": "<<idx1<<" "<<idx2<<std::endl;
	  fout<<"Case #"<<(c+1)<<": "<<idx1<<" "<<idx2<<std::endl;
  }

  return 0;
}

/*
-------------------------
Input
-------------------------
3
100
3
5 75 25
200
7
150 24 79 50 88 345 3
8
8
2 1 9 4 4 56 90 3
--------------------------
Output
--------------------------
Case #1: 2 3
Case #2: 1 4
Case #3: 4 5
--------------------------
*/
