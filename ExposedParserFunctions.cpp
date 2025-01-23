#include <istream>
#include "Structs/JSONValueStruct.h"
#include <variant>

using std::variant; 

bool checkIfContainsKey(shared_ptr<JSONValue> pointer, string key) {

	
	// If it contains a JSONObject, get the object
	if (holds_alternative<JSONObject>(pointer->value)) {
		const JSONObject& obj = GetJSONObjectFromJSONValue(pointer);
		// Break out to handle
		// Will need a recurcive call 

	};
	if (holds_alternative<JSONArray>(pointer->value)) {
		
	
	}

	// If it contains a Json Array - Get the array
}

JSONObject GetJSONObjectFromJSONValue(const shared_ptr<JSONValue>& pointer) {
		return get<JSONObject>(pointer->value);
}

JSONArray GETJSONArrayFromJSONValue(const shared_ptr<JSONValue>& pointer) {
	return get<JSONArray>(pointer->value);

}





bool checkForKeyInJSONValueObject(const JSONObject& obj, const string& key) {

	//Iterator for find
	auto it = obj.find(key);
	// if end() is returned if the key is not found
	if (it != obj.end()) {
		return true;
	
	}
	return false;
}



