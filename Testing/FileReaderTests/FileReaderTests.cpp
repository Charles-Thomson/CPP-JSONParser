#include <gtest/gtest.h>

#include "../../CPP-JSONParser.h"
#include "../../FileReader/FileReader.h"
#include "../TestDataPreProcessing/TestDataPreProcessing.h"
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
list<string> TEST_FILE_NAMES = {
        "ValidStringWhiteSpace",
        "ValidString",
        "ValidStringWithArray",
        "ValidMultiLine"
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
TEST(FileReaderTests, TestReadFile) {
    string fileName = "ValidMultiLine";
    string fullPath = TEST_INPUT_FILE_PATH + fileName + ".txt";

    FileReader fileReader = FileReader();

    string result = fileReader.GetFileContents(fullPath);

    tuple<string, string> testKeysAndValues = GetTestFileKeysAndValues(fileName);

    ASSERT_TRUE(typeid(result) == typeid(string)) << "Expected String got : " << typeid(result).name();

    ASSERT_FALSE(result.empty()) << "File is empty : " << fullPath;

    cout << "Test Keys : " << get<0>(testKeysAndValues) << endl;

    cout << "Test Values : " << get<1>(testKeysAndValues) << endl;

    cout << "Test Return : " << result << endl;
}






