#include "PrintJSON.h"
#include "../Structs/JSONValueStruct.h"

#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::endl;


//*
// 
// @Brief Print a JSONObject
// 
// Print the contents of a JSONObject 
// 
// @param jsonValue shared_ptr<JSONValue> a referance the the pointer of the object pointer
// @param indent int The current indent, beased on depth of nesting
//  @param nested Bool Indicates if there is object nesting in the Object
// 
// @return void
// */
void PrintJson(const shared_ptr<JSONValue>& jsonValue, int indent, bool nested) {

	//If the value == JSONObject
	if (holds_alternative<JSONObject>(jsonValue->value)) {
		const JSONObject& obj = get<JSONObject>(jsonValue->value);
		if (nested) {
			cout << endl;
		}

		for (const auto& [key, value] : obj) {

			cout << string(indent, ' ') << key << ": ";
			PrintJson(value, indent + 2, true); // recursive call 
		}
	}
	else if (holds_alternative<JSONArray>(jsonValue->value)) {
		const JSONArray& ary = get<JSONArray>(jsonValue->value);


		for (const auto& val : ary) {
			cout << string(indent, ' ') << endl;
			PrintJson(val, indent, true);
		}

	}
	else if (holds_alternative<string>(jsonValue->value)) {
		cout << string(indent, ' ') << get<string>(jsonValue->value) << endl;
	}

	else if (holds_alternative<double>(jsonValue->value)) {

		cout << get<double>(jsonValue->value) << endl;
		cout << "   " << endl;
	}
}