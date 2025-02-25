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
using std::istringstream;


string GetStringFromJSONValue(const shared_ptr<JSONValue>& pointer) {
	return get<string>(pointer->value);
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


any getCorrectTypeFromJSONValue(const shared_ptr<JSONValue>& pointer ) {
	
	if (holds_alternative<string>(pointer->value)) {
		string value = GetStringFromJSONValue(pointer);
		cout << "getCorrectTypeFromJSONValue ->  GetStringFromJSONValue -> " << value << endl;

		return GetStringFromJSONValue(pointer);
	}
	if (holds_alternative<double>(pointer->value)) {
		double value = GetDoubleFromJSONValue(pointer);
		cout << "getCorrectTypeFromJSONValue ->  GetDoubleFromJSONValue -> " << std::to_string(value) << endl;

		return GetDoubleFromJSONValue(pointer);
	}
	if (holds_alternative<bool>(pointer->value)) {
		bool value = GetBoolFromJSONValue(pointer);
		cout << "getCorrectTypeFromJSONValue ->  GetDoubleFromJSONValue -> " << std::to_string(value) << endl;

		return GetBoolFromJSONValue(pointer);
	}
	if (holds_alternative<JSONObject>(pointer->value)) {
		return GetJSONObjectFromJSONValue(pointer);
	}
	if (holds_alternative<JSONArray>(pointer->value)) {
		return GetJSONArrayFromJSONValue(pointer);
	}
}


vector<any> ConvertVectorStringToVectorAny(vector<string>& inputVector) {
	vector<any> finalResult;

	for (string val : inputVector) {
		
		istringstream stream = istringstream(val);

		char ch = stream.peek();

		if (isdigit(ch)) {
			string result;

			
			while (stream.get(ch) && isdigit(ch)) {
				result += ch;
			}

			if (stream.get(ch) && !isdigit(ch)) {
				finalResult.push_back(val); // If a combination of digit and none digit values

			}else {
				double value = std::stod(result);
				finalResult.push_back(value);
			}

		} else if (val == "true") {
			bool value = true;
			finalResult.push_back(value);


		}else if (val == "false") {
			bool value = false;
			finalResult.push_back(value);

		}else if (val == "JSONObject") {
			JSONObject obj;
			finalResult.push_back(obj);

		}else if (val == "JSONArray") {
			JSONArray arr;
			finalResult.push_back(arr);
		}

		// If the val is a string
		else {
			
			finalResult.push_back(val);
	
		}
	}

	return finalResult;

}




