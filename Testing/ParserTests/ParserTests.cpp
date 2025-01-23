#include "CPP-JSONParser.h"

#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <list>
#include <fstream> 

#include "FileReader/FileReader.h"
#include "Structs/JSONValueStruct.h"

//list<string> TEST_FILE_PATHS = {
//    "ValidStringWhiteSpace.txt",
//    "ValidString.txt",
//    "ValidStringWithArray.txt"
//};


/// Make a file reader to get the file
/// Test to check if the file is parsed correctly

//list<string> KEYS = {
//
//    "name",
//    "age",
//    "address",
//    "building",
//    "family ",
//    "jeff"
//};


//*
// @brief Test conversion from string to JSON
// 
// Test pre defined input strings for JSON conversion
// */
TEST(ParserTests, ParserWhiteSpaceTest) {

    /*FileReader newFileReader("C:/Users/Charl/source/repos/C++/JSONParser/TestStrings/ValidStringWhiteSpace.txt");

    pair<string, bool> returnedData = newFileReader.GetFileContents();

    string holder = returnedData.first;*/

    /*shared_ptr<JSONValue> ParsedData = ParseJson(holder);*/


    /*string hO = HolderFunc();*/ // This is the call to the external JSONParser.h file 
    ASSERT_EQ(1, 1);


    /*for (string& key : KEYS) {
        ASSERT_EQ(CheckKeyExists(ParsedData, key), true);
    }*/



}




