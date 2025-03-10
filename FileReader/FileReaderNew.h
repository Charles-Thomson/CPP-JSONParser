#ifndef FILE_READER_NEW_H
#define FILE_READER_NEW_H

#include <iostream>
#include <fstream>
#include <string>
#include <tuple>



using std::string;
using std::cout;
using std::endl;
using std::ifstream;
using std::cerr;
using std::pair;
using std::tuple;

class FileReaderNew {
private:
	string INPUT_FILE_PATH;

	bool CheckFilePathValidityNew(const string& filePath) const;

public:

	FileReaderNew();

	~FileReaderNew();

	string GetTestInputFilePathNew() const;

	string GetFileContentsTest(string& fileName) const;

	string ReadFileContentsNew(string& filePath) const;

	
};





#endif // !FILE_READER_NEW_H
