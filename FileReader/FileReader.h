
#ifndef FILEREADER_H
#define FILEREADER_H



#include <iostream>
#include <fstream>
#include <string>



using std::string;
using std::cout;
using std::endl;
using std::ifstream;
using std::cerr;
using std::pair;

class FileReader {
private:
	string INPUT_FILE_PATH;

	string ReadFileContents(const string& filePath) const;

	string BuildFilePath(const string& fileType) const;

	bool CheckFilePathValidity(const string& filePath) const;

public:
	FileReader(const string& filePath);

	~FileReader();

	string GetTestInputFilePath() const;

	pair<string, bool> GetFileContents() const;

};



#endif // !FILEREADER_H