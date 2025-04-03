
#include "SupportingTestFunctions.h"

#include "../../HelperFunctions/TypeConversions.h"
#include "../../Structs/JSONValueStruct.h"

#include <variant>
#include <istream>
#include <format>

using std::string;
using std::variant;
using std::cout;
using std::endl;
using std::any_cast;

//*
// @ Check if two strings are equal
// 
//  Check if the given searchKey is equal to the given key
// 
// @ prama string& searchKey : key being searched for
// @ param string& key : instance of a stored key
// 
// @ return bool: True If given param values are equal
// */
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
// Check if a key is contained within a given JSONValue - recursively called to hendle nested instances
// 
// @param JSONObject Given ptr to JSONValue
// @param key Checked value
// 
// @return bool If key value is contained in JSONValue -> JSONObject
// */
bool checkIfContainsKey(shared_ptr<JSONValue> pointer, string& searchKey) {

	if (holds_alternative<JSONObject>(pointer->value)) {
		const JSONObject& obj = GetJSONObjectFromJSONValue(pointer);

		for (const auto& [key, value] : obj) {

			if (checkIfSearchKey(searchKey, key)) {
				return true;
			}
			else if (checkIfContainsKey(value, searchKey)) {
					return true;
			};
		};
	};

	if (holds_alternative<JSONArray>(pointer->value)) {
		const JSONArray& ary = GetJSONArrayFromJSONValue(pointer);

		for (const auto& val : ary) {

			// Check if any of the keys in the array are the search key
			if (holds_alternative<string>(val->value)) {
				const string valueString = GetStringFromJSONValue(val);

				if (checkIfSearchKey(searchKey, valueString)) {
					return true;
				}
			}
			else if (checkIfContainsKey(val, searchKey)) {
					return true;	
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


//*
// @Brief compare shared_ptr<JSONValue> to any& 
// 
// Determine if a shared_ptr<JSONValue> and any type have the contained/held type
// 
// @ param shared_ptr<JSONValue>& pointerValue: The given shared pointer JSONValue
// @ param any& anyValue : The any type to be compared against the shared_ptr type
// @ return bool: True If the two contained/held type are equal
// */
bool compareJSONValueToTestValue(shared_ptr<JSONValue>& pointerValue, any& anyValue) {

	string typeHeld = pointerValue->getType();

	cout << "The type in compare function  " << typeHeld << endl;

	if (holds_alternative<string>(pointerValue->value)) {
		cout << "holding string" << endl;
		string value = GetStringFromJSONValue(pointerValue);
		return value == any_cast<string>(anyValue);
	}

	if (holds_alternative<double>(pointerValue->value)) {
		double value = GetDoubleFromJSONValue(pointerValue);
		return value == any_cast<double>(anyValue);
	}

	if (holds_alternative<bool>(pointerValue->value)) {
		bool value = GetBoolFromJSONValue(pointerValue);
		return value == any_cast<bool>(anyValue);
	}

	if (holds_alternative<JSONObject>(pointerValue->value)) {
		return typeid(shared_ptr<JSONObject>).name() == typeid(any_cast<shared_ptr<JSONObject>>(anyValue)).name();
	}

	if (holds_alternative<JSONArray>(pointerValue->value)) {
		return typeid(shared_ptr<JSONArray>).name() == typeid(any_cast<shared_ptr<JSONArray>>(anyValue)).name();
	}

	

	return false;
}