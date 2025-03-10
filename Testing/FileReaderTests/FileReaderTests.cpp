#include <gtest/gtest.h>

#include "CPP-JSONParser.h"
#include "FileReader/FileReader.h"
#include "FileReader/FileReaderNew.h"
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
        "ValidStringWhiteSpace",
        "ValidString",
        "ValidStringWithArray"
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



tuple<string, string> GetTestFileKeysAndValues(string& testFileName) {
    string fullPath = TEST_INPUT_FILE_PATH + testFileName + "KeysAndValues.txt";

    ifstream inputfile(fullPath);
    string testKeysIdentifier = "#TEST_KEYS#";
    string testValuesIdentifier = "#TEST_VALUES#";

    if (!inputfile) {
        cerr << "Error Opening File : " << fullPath << endl;
    }

    string line;
    string testKeys;
    string testValues;

    string stringHolder;

    while (getline(inputfile, line)) {
        stringHolder = line;

        if (stringHolder.find(testKeysIdentifier) != string::npos) {
            testKeys += line;
        }
        else if (stringHolder.find(testValuesIdentifier) != string::npos) {
            testValues += line;
        }
    }
    return {testKeys, testValues};

}


TEST(FileReaderTests, TestReadFile) {
    string fileName = "ValidMultiLine";
    string fullPath = TEST_INPUT_FILE_PATH + fileName + ".txt";

    FileReaderNew fileReader = FileReaderNew();

    string result = fileReader.GetFileContentsTest(fullPath);

    tuple<string, string> testKeysAndValues = GetTestFileKeysAndValues(fileName);

    cout << "Test Keys : " << get<0>(testKeysAndValues) << endl;

    cout << "Test Values : " << get<1>(testKeysAndValues) << endl;



    cout << "Test Return : " << result << endl;

    ASSERT_EQ(1, 2);


}






