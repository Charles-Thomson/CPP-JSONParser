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