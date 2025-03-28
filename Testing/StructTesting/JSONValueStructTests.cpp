
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

	shared_ptr<JSONValue> testValue = make_shared<JSONValue>(testDouble);

	double returnedValue = *testValue->get<double>();
	cout << "The returned Value: " << returnedValue << endl;

	double returnedValueDouble = testValue->returnThis();
	cout << "The returned Value Type : " << returnedValueDouble << endl;


	


	ASSERT_EQ(1, 2);
}



TEST(JSONStructTest, HeldTypeRetrival) {
	cout << "Held Type" << endl;
	ASSERT_EQ(1, 2);

}