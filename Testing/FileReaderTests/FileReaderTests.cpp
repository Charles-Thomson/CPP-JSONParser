#include <gtest/gtest.h>

#include "CPP-JSONParser.h"
#include "FileReader/FileReader.h"
#include "TestDataPreProcessing/TestDataPreProcessing.h"
//#include "FileReader/FileReaderNew.h"
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

    for (const string& fileName : TEST_FILE_NAMES) {
        string fullPath = TEST_INPUT_FILE_PATH + fileName + ".txt";

        ASSERT_TRUE(fileExists(fullPath)) << "File does not exist" << fullPath;

        FileReader newFileReader;

        string testData = newFileReader.GetFileContents(fullPath);

        ASSERT_TRUE(typeid(testData) == typeid(string)) << "Expected String got : " << typeid(testData).name();

        ASSERT_FALSE(testData.empty()) << "File is empty : " << fullPath;
    }

}

TEST(FileReaderTests, TestReadFile) {
    string fileName = "ValidMultiLine";
    string fullPath = TEST_INPUT_FILE_PATH + fileName + ".txt";

    FileReader fileReader = FileReader();

    string result = fileReader.GetFileContents(fullPath);

    tuple<string, string> testKeysAndValues = GetTestFileKeysAndValues(fileName);

    cout << "Test Keys : " << get<0>(testKeysAndValues) << endl;

    cout << "Test Values : " << get<1>(testKeysAndValues) << endl;



    cout << "Test Return : " << result << endl;

    /*ASSERT_EQ(1, 2);*/


}






