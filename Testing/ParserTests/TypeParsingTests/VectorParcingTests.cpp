#include <gtest/gtest.h>
#include "../../../CPP-JSONParser.h"
#include "../../../Testing/TestDataPreProcessing/TestDataPreProcessing.cpp"

#include <string>

using std::string;
using std::format;

using JSON = shared_ptr<JSONValue>;


template<typename T>
T LoadVectorFromFile(const string& relitiveFilePath, const string& key) {
	string filePath = string(TYPE_TEST_FILE_PATH) + relitiveFilePath;
	JSON testJSON = ReadAndParseTypeTestFile(filePath);
	return GetValueByKeyWithType<T>(testJSON, key);
}
template<typename T>
void CheckVectorSize(vector<T>& vec, size_t expectedSize) {
	ASSERT_EQ(vec.size(), expectedSize) << "Expected Vector size : " << expectedSize << " but got vector size : " << vec.size();

}

TEST(TypeParsingTests, TypeParcing_Vector_double) {
	string relitiveFilePath = "vector/vector_type_double.txt";
	string key = "test_vector";

	vector<double> testVector = LoadVectorFromFile<vector<double>>(relitiveFilePath, key);

	ASSERT_EQ(typeid(testVector), typeid(vector<double>)) << "Expected Type : vector<double> - Returned Type " << typeid(testVector).name();
	CheckVectorSize(testVector, 3);

	EXPECT_DOUBLE_EQ(testVector[0], 1);
	EXPECT_DOUBLE_EQ(testVector[1], 2);
	EXPECT_DOUBLE_EQ(testVector[2], 3.3);
}



TEST(TypeParsingTests, TypeParcing_Vector_string) {
	string relitiveFilePath = "vector/vector_type_string.txt";
	string key = "test_vector";

	vector<string> testVector = LoadVectorFromFile<vector<string>>(relitiveFilePath, key);

	ASSERT_EQ(typeid(testVector), typeid(vector<string>)) << "Expected Type : vector<string> - Returned Type :  " << typeid(testVector).name();
	CheckVectorSize(testVector, 3);

	EXPECT_EQ(testVector[0], "Jeff");
	EXPECT_EQ(testVector[1], "Bill");
	EXPECT_EQ(testVector[2], "3.3");
	
}

TEST(TypeParsingTests, TypeParcing_Vector_bool) {
	string relitiveFilePath = "vector/vector_type_bool.txt";
	string key = "test_vector";

	vector<bool> testVector = LoadVectorFromFile<vector<bool>>(relitiveFilePath, key);

	ASSERT_EQ(typeid(testVector), typeid(vector<bool>)) << "Expected Type : vector<bool> - Returned Type : {}" << typeid(testVector).name();
	CheckVectorSize(testVector, 3);

	EXPECT_EQ(testVector[0], true);
	EXPECT_EQ(testVector[1], false);
	EXPECT_EQ(testVector[2], true);

}


TEST(TypeParsingTests, TypeParcing_nested_vector_double) {

	string relitiveFilePath = "vector/vector_type_nested_double.txt";
	string key = "test_vector";

	vector<vector<double>> testVector = LoadVectorFromFile<vector<vector<double>>>(relitiveFilePath, key);

	CheckVectorSize(testVector, 3);
	CheckVectorSize(testVector[0], 3);
	CheckVectorSize(testVector[1], 3);
	CheckVectorSize(testVector[2], 3);

	ASSERT_TRUE(testVector.size() > 0) << "Expected the size of the testVector to be non 0 : size found : " << testVector.size();
	EXPECT_DOUBLE_EQ(testVector[0][0], 1);
	EXPECT_DOUBLE_EQ(testVector[0][1], 2);
	EXPECT_DOUBLE_EQ(testVector[0][2], 3);

	EXPECT_DOUBLE_EQ(testVector[1][0], 4);
	EXPECT_DOUBLE_EQ(testVector[1][1], 5);
	EXPECT_DOUBLE_EQ(testVector[1][2], 6);

	EXPECT_DOUBLE_EQ(testVector[2][0], 7);
	EXPECT_DOUBLE_EQ(testVector[2][1], 8);
	EXPECT_DOUBLE_EQ(testVector[2][2], 9);

}

