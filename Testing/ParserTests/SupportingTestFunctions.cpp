
#include "SupportingTestFunctions.h"

#include "../../HelperFunctions/TypeConversions.h"
#include "../../Structs/JSONValueStruct.h"

#include <variant>
#include <istream>

using std::string;
using std::variant;
using std::cout;
using std::endl;

bool checkIfSearchKey(const string& searchKey, const string& key) {

	cout << "Comparing: " << searchKey << " : " << key << endl;

	if (key == searchKey) {
		return true;
	}
	return false;
}

//*
// @brief Check Key Exists 
// 
// Check if a key is contained within a given JSONValue -> JSONObject
// 
// 
// @param JSONObject Given ptr to JSONValue
// @param key Checked value
// 
// @return bool If key value is contained in JSONValue -> JSONObject
// */
bool checkIfContainsKey(shared_ptr<JSONValue> pointer, string& searchKey) {

	// If it contains a JSONObject, get the object
	if (holds_alternative<JSONObject>(pointer->value)) {
		const JSONObject& obj = GetJSONObjectFromJSONValue(pointer);

		for (const auto& [key, value] : obj) {

			if (checkIfSearchKey(searchKey, key)) {
				return true;
			}
			else {
				if (checkIfContainsKey(value, searchKey)) {
					return true;
				};
			};
		};
	};

	if (holds_alternative<JSONArray>(pointer->value)) {
		const JSONArray& ary = GetJSONArrayFromJSONValue(pointer);

		for (const auto& val : ary) {

			cout << "In the array checker with : " << val << endl;

			if (holds_alternative<string>(val->value)) {
				const string valueString = GetStringFromJSONValue(val);

				if (checkIfSearchKey(searchKey, valueString)) {
					return true;
				}
			}
			else {
				if (checkIfContainsKey(val, searchKey)) {
					return true;
				}
			}
		}
	};

	if (holds_alternative<string>(pointer->value)) {
		const string stringValue = GetStringFromJSONValue(pointer);

		if (checkIfSearchKey(searchKey, stringValue)) {
			return true;
		}
		return false;
	}

	return false;
}





