#include <gtest/gtest.h>

#include "CPP-JSONParser.h"
#include "FileReader/FileReader.h"
#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <tuple>


using std::tuple;
using std::string;
using std::list;
using std::ifstream;

// Test File Paths
list<string> TEST_FILE_PATHS = {
        "ValidStringWhiteSpace.txt",
        "ValidString.txt",
        "ValidStringWithArray.txt"
};


//*
//  @ brief: Checks file exists
// 
// Checks if a file path is valid in the context of if the file exists
// 
// @param string& path : reference to the file path to be checked
// @return bool: IF the file path is valid
// */
bool fileExists(const string& path) {
    ifstream file(path);
    return file.good();
}


//*
// @ brief Test reading of test files
// 
//  Test if the test files can be read and return the expected data
// */
TEST(FileReaderTests, ReadTestFiles) {

    for (const string& path : TEST_FILE_PATHS) {
        string fullPath = TEST_INPUT_FILE_PATH + path;

        ASSERT_TRUE(fileExists(fullPath)) << "File does not exist" << path;

        FileReader newFileReader;

        tuple<string,string,string,  bool> testData = newFileReader.GetFileContents(fullPath);

        ASSERT_TRUE(typeid(get<0>(testData)) == typeid(string)) << "Expected String got : " << typeid(get<0>(testData)).name();

        ASSERT_FALSE(get<0>(testData).empty()) << "File is empty : " << fullPath;
    }

}






