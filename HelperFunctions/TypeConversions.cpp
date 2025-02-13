#include "TypeConversions.h"

#include <vector>
#include <variant> 
#include <iostream>
#include <string>
#include <format>
#include <memory>
#include <unordered_map>
#include <sstream>
#include "../Structs/JSONValueStruct.h"
#include <any>


using std::variant;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::stringstream;
using std::any;

string GetStringFromJSONValue(const shared_ptr<JSONValue>& pointer) {
	string holder = get<string>(pointer->value);
	
	cout << "In the string get with value:" << holder << " " << typeid(holder).name() << endl;
	return holder;
}

double GetDoubleFromJSONValue(const shared_ptr<JSONValue>& pointer) {
	return get<double>(pointer->value);
}

bool GetBoolFromJSONValue(const shared_ptr<JSONValue>& pointer) {
	if (std::holds_alternative<bool>(pointer->value)) {
		return std::get<bool>(pointer->value);
	}
}

JSONObject GetJSONObjectFromJSONValue(const shared_ptr<JSONValue>& pointer) {
	return get<JSONObject>(pointer->value);
}

JSONArray GetJSONArrayFromJSONValue(const shared_ptr<JSONValue>& pointer) {
	return get<JSONArray>(pointer->value);

}

vector<string> stringToVector(const string& inputString) {
	vector<string> stringList;
	stringstream ss(inputString);
	string word;

	while (getline(ss, word, ',')) {
		stringList.push_back(word);
	}
	return stringList;
}


// Have this return a lamde to be called to remove the return type issue ?
any getCorrectTypeFromJSONValue(const shared_ptr<JSONValue>& pointer ) {
	
	if (holds_alternative<string>(pointer->value)) {
		return GetStringFromJSONValue(pointer);
	}
	if (holds_alternative<double>(pointer->value)) {
		return GetDoubleFromJSONValue(pointer);
	}
	if (holds_alternative<bool>(pointer->value)) {
		return GetBoolFromJSONValue(pointer);
	}
	if (holds_alternative<JSONObject>(pointer->value)) {
		return GetJSONObjectFromJSONValue(pointer);
	}
	if (holds_alternative<JSONArray>(pointer->value)) {
		return GetJSONArrayFromJSONValue(pointer);
	}
}



