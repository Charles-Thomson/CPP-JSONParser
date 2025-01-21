#include <gtest/gtest.h>

#include "CPP-JSONParser.h"
#include "FileReader/FileReader.h"
#include <iostream>
#include <string>
#include <list>
#include <fstream>

using std::string;
using std::list;
using std::ifstream;


list<string> TEST_FILE_PATHS = {
        "ValidStringWhiteSpace.txt",
        "ValidString.txt",
        "ValidStringArray.txt"
};



bool fileExists(const string& path) {
    ifstream file(path);
    return file.good();
}



TEST(FileReaderTests, ReadTestFiles) {

    for (const string& path : TEST_FILE_PATHS) {
        string fullPath = TEST_INPUT_FILE_PATH + path;

        ASSERT_TRUE(fileExists(fullPath)) << "File does not exist" << path;

        FileReader newFileReader(fullPath);
        pair<string, bool> testData = newFileReader.GetFileContents();



        ASSERT_TRUE(typeid(testData.first) == typeid(string)) << "Expected String got : " << typeid(testData.first).name();

        ASSERT_FALSE(testData.first.empty()) << "File is empty : " << fullPath;
    }

}






