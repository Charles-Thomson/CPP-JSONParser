#include "FileReaderNew.h"



#include <iostream>
#include <fstream>
#include <string>
#include <tuple>
#include <list>
#include <variant>
#include <sstream>

#include "FileReader.h"
using std::tuple;
using std::string;
using std::cout;
using std::endl;
using std::ifstream;
using std::cerr;
using std::getline;
using std::stringstream;
using std::pair;
using std::list;
using std::variant;



// Constructor
FileReaderNew::FileReaderNew() {}

// Destructor 
FileReaderNew::~FileReaderNew() {}


//**
// @brief returns INPUT_FILE_PATH 
// 
// Returns the stored const of the INPUT_FILE_PATH
// */
string FileReaderNew::GetTestInputFilePathNew() const {
	return INPUT_FILE_PATH;
}

//*
// @brief Check file path validity
// 
// Checks if a given file path is reachable, and is open 
// 
// @param filePath The given file path to check
// */
bool FileReaderNew::CheckFilePathValidityNew(const string& filePath) const {
	ifstream inputFile(filePath);
	return inputFile.is_open();
}




string FileReaderNew::GetFileContentsTest(string& filePath) const{
	bool filePathValid = CheckFilePathValidityNew(filePath);
	
	string fileData = ReadFileContentsNew(filePath);
	return fileData;


}


string FileReaderNew::ReadFileContentsNew(string& filePath) const{
	ifstream inputfile(filePath);
	string testKeysIdentifier = "#TEST_KEYS#";
	string testValuesIdentifier = "#TEST_VALUES#";

	if (!inputfile) {
		cerr << "Error Opening File : " << filePath << endl;
	}

	string fileContent;
	string contentLine;
	string testKeys;
	string testValues;
	string holderString;
	string line;


	while (getline(inputfile, line)) {
		contentLine += line;

		/*if (holderString.find(testKeysIdentifier) != string::npos) {
			testKeys += holderString;
		}else if (holderString.find(testValuesIdentifier) != string::npos) {
			testValues += holderString;
		}
		else {
			contentLine += holderString;
		
		}*/

	}

	return contentLine;

}


