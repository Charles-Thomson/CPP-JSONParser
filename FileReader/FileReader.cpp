//*
// ****FILE READER****
// 
// Used to read the input files stored in TestStrings folder
// 
// Currently only used to test the JSONParser
// 
// Main function to be called - GetFileContents()
// */


#include <iostream>
#include <fstream>
#include <string>
#include <tuple>

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

// Constructor
FileReader::FileReader() {
}
// Destructor
FileReader::~FileReader() {
}

//**
// @brief returns INPUT_FILE_PATH 
// 
// Returns the stored const of the INPUT_FILE_PATH
// */
string FileReader::GetTestInputFilePath() const {
	return INPUT_FILE_PATH;
}


//*
// @brief Check file path validity
// 
// Checks if a given file path is reachable, and is open 
// 
// @param filePath The given file path to check
// */
bool FileReader::CheckFilePathValidity(const string& filePath) const {
	ifstream inputFile(filePath);
	return inputFile.is_open();
}

//*
// @brief Read and Return file contents
// 
// Read the contents of a given file and condence into single string
// 
// @param filePath Path to the stored file
// @Return The contents of the file as a single string
// */
pair<string, string> FileReader::ReadJSONTestFileContents(const string& filePath) const {
	ifstream inputFile(filePath);
	if (!inputFile) {
		cerr << "Error Opening File: " << filePath << endl;
		return {"", ""};
	}

	string fileContent;
	string contentLine;
	string keysLine;
	string line;

	if (getline(inputFile, line)) {
		contentLine = line;

	};

	if (getline(inputFile, line)) {
		keysLine = line;
		
	};

	cout << keysLine << endl; 
	return {contentLine, keysLine};
}

//*
// @brief Main Function call - Get the contents of a file 
// 
// Function to get the content of a file. Calls to build the file path, check for path validity and read & return file contents
// Uses a bool flag as part of the returned pair to indicate if the read is successful
// 
// @param fileType The type of file to be read(i.e valid, invalid, nested ...)
// @Return The contents of the file as a single string, bool falg to indicate if read successful
// */
tuple<string,string,bool> FileReader::GetFileContents(const string& filePath)  {

	// Check the Path is valid
	if (!CheckFilePathValidity(filePath)) {
		cout << "File Path is Invalid" << endl;
		return { "", "", false};
	}

	pair<string, string> content = ReadJSONTestFileContents(filePath);

	return { content.first, content.second, true };
}





