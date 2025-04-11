#include <gtest/gtest.h>
#include "CPP-JSONParser.h"
#include "../Testing/TestDataPreProcessing/TestDataPreProcessing.cpp"

#include <string>

using std::string;

using JSON = shared_ptr<JSONValue>;







TEST(TypeParcingTests, TypeParcing_Vecotor) {

	cout << "In the vector parcing testsing" << endl;

	string filePath = string(TYPE_TEST_FILE_PATH) + "vector/vector_type_double.txt";

	JSON testJson = ReadAndParseTypeTestFile(filePath);

	cout << "TypeParcing_Vecotor  - > File Read OKAY" << endl;

	JSON result = GetValueByKey(testJson, "test_vector");

	string heldType = result->getType();

	vector<double> vectorDouble = GetValueByKeyWithType<vector<double>>(testJson, "test_vector");

	cout << "The held type : " << heldType << endl;

	cout << "Size of the array : " << vectorDouble.size() << endl;
	
	ASSERT_EQ(1, 2);
}