
#ifndef FILEREADER_H
#define FILEREADER_H



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

class FileReader {
private:
	string INPUT_FILE_PATH;

	pair<string, string> ReadJSONTestFileContents(const string& filePath) const;

	string BuildFilePath(const string& fileType) const;

	bool CheckFilePathValidity(const string& filePath) const;

public:
	FileReader(const string& filePath);

	~FileReader();

	string GetTestInputFilePath() const;

	tuple<string, string, bool> GetFileContents() const;

};



#endif // !FILEREADER_H