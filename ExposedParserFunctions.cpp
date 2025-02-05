#include <istream>
#include "Structs/JSONValueStruct.h"
#include <variant>

using std::variant; 
using std::cout;
using std::endl;
 
// TODO
// Handle the nesting cases correctly
// use itor for the objects to speed up the search then go into the nesting ?
// Fix the issue of it looping over the value - this might be needed to see if it is nesting ?

int placeHolder() {
	return 0;

}

bool checkIfSearchKey( const string& searchKey, const string& key) {

	cout << "Comparing: " << searchKey << " : " << key << endl;

	if (key == searchKey) {
		cout << "Returning True" << endl;
		return true;
	
	}
	cout << "Returning False" << endl;
	return false;
}

string GetStringFromJSONValue(const shared_ptr<JSONValue>& pointer) {
	return get<string>(pointer->value);
}

JSONObject GetJSONObjectFromJSONValue(const shared_ptr<JSONValue>& pointer) {
	return get<JSONObject>(pointer->value);
}

JSONArray GetJSONArrayFromJSONValue(const shared_ptr<JSONValue>& pointer) {
	return get<JSONArray>(pointer->value);

}

// Move to use the iterator to check all the keys before going into the nesting
// It is passing the value 

bool checkIfContainsKey(shared_ptr<JSONValue> pointer, string& searchKey) {

	cout << "Search Key " << searchKey << endl;
	
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

			if (holds_alternative<string>(val -> value)) {
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






// add this function in to improve the search at each level ?
bool checkForKeyInJSONValueObject(const JSONObject& obj, const string& key) {

	//Iterator for find
	auto it = obj.find(key);
	// if end() is returned if the key is not found
	if (it != obj.end()) {
		return true;
	
	}
	return false;
}



