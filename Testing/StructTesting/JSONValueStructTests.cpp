
#include <gtest/gtest.h>
#include <string>
#include <iostream>
#include "Structs/JSONValueStruct.h"

using std::cout;
using std::endl;
using std::variant;
using std::make_shared;



TEST(JSONStructTest, HeldValueRetrival) {
	cout << "Held Value" << endl;
	double testDouble = 22.2;

	string testString = "22.2";

	shared_ptr<JSONValue> testValue = make_shared<JSONValue>(testDouble);

	shared_ptr<JSONValue> testValue2 = make_shared<JSONValue>(testString);

	double value = testValue->testVisit<double>();
	cout << value << typeid(value).name() << endl;

	string valueS = testValue2->testVisit<string>();
	cout << valueS << typeid(valueS).name() << endl;



	/*double returnedValue = *testValue->get<double>();
	cout << "The returned Value: " << returnedValue << endl;


	cout << value << endl;*/

	ASSERT_EQ(1, 2);
}



TEST(JSONStructTest, HeldTypeRetrival) {
	cout << "Held Type" << endl;
	ASSERT_EQ(1, 2);

}