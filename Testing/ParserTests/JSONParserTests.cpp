#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <list>
#include <fstream> 

#include "FileReader/FileReader.h"
#include "Structs/JSONValueStruct.h"
#include "TestObject.cpp"
#include "New-CPP.cpp"

#include "CPP-JSONParser.h"

TEST(JSONParserTests, case1) {
	TestObject newObj = TestObject("Hello");
	string TestString = GetStringFromTest();
	string newString = NewFunction();
	ASSERT_EQ(1, 1);
}