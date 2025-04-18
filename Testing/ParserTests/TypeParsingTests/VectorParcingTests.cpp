#include <gtest/gtest.h>
#include "../../../CPP-JSONParser.h"
#include "../../../Testing/TestDataPreProcessing/TestDataPreProcessing.cpp"

#include <string>

using std::string;
using std::format;

using JSON = shared_ptr<JSONValue>;

TEST(TypeParcingTests, TypeParcing_Vector_double) {

	string filePath = string(TYPE_TEST_FILE_PATH) + "vector/vector_type_double.txt";

	JSON testJson = ReadAndParseTypeTestFile(filePath);

	cout << "TypeParcing_Vecotor  - > File Read OKAY" << endl;

	JSON result = GetValueByKey(testJson, "test_vector");

	string heldType = result->getType();

	vector<double> testVector = GetValueByKeyWithType<vector<double>>(testJson, "test_vector");

	SCOPED_TRACE(format("The expected return type vector<double> - The actual return type : {}", typeid(testVector).name()));
	ASSERT_TRUE(typeid(testVector) == typeid(vector<double>));

	SCOPED_TRACE(format("The size of the test vector : 3 - The size of the returned Vactor : {}", testVector.size()));
	ASSERT_TRUE(testVector.size() == 3);
}



TEST(TypeParcingTests, TypeParcing_Vector_string) {

	string filePath = string(TYPE_TEST_FILE_PATH) + "vector/vector_type_string.txt";

	JSON testJson = ReadAndParseTypeTestFile(filePath);

	cout << "TypeParcing_Vecotor  - > File Read OKAY" << endl;

	JSON result = GetValueByKey(testJson, "test_vector");

	string heldType = result->getType();

	vector<string> testVector = GetValueByKeyWithType<vector<string>>(testJson, "test_vector");

	SCOPED_TRACE(format("The expected return type vector<string> - The actual return type : {}", typeid(testVector).name()));
	ASSERT_TRUE(typeid(testVector) == typeid(vector<string>));

	SCOPED_TRACE(format("The size of the test vector : 3 - The size of the returned Vactor : {}", testVector.size()));
	ASSERT_TRUE(testVector.size() == 3);

	for (string val : testVector) {
		cout << format("Vector Element : {}", val) << endl;

	};
	
}

TEST(TypeParcingTests, TypeParcing_Vector_bool) {

	string filePath = string(TYPE_TEST_FILE_PATH) + "vector/vector_type_bool.txt";

	JSON testJson = ReadAndParseTypeTestFile(filePath);

	cout << "TypeParcing_Vecotor  - > File Read OKAY" << endl;

	JSON result = GetValueByKey(testJson, "test_vector");

	string heldType = result->getType();

	vector<bool> testVector = GetValueByKeyWithType<vector<bool>>(testJson, "test_vector");

	SCOPED_TRACE(format("The expected return type vector<bool> - The actual return type : {}", typeid(testVector).name()));
	ASSERT_TRUE(typeid(testVector) == typeid(vector<bool>));

	SCOPED_TRACE(format("The size of the test vector : 3 - The size of the returned Vactor : {}", testVector.size()));
	ASSERT_TRUE(testVector.size() == 3);

	for (bool val : testVector) {
		cout << format("Vector Element : {}", val) << endl;

	};
}

