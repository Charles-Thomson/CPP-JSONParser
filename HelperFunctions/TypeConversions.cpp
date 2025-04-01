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

//*
// @ brief Get type string from JSONValue type
// 
// @ param shared_ptr<JSONValue>& pointer : referance pointer to the JSONValue
// @ return Stored String value
// */
string GetStringFromJSONValue(const shared_ptr<JSONValue>& pointer) {
	return get<string>(pointer->value);
}


//*
// @ brief Get type double from JSONValue type
// 
// @ param shared_ptr<JSONValue>& pointer : referance pointer to the JSONValue
// @ return Stored double value
// */
double GetDoubleFromJSONValue(const shared_ptr<JSONValue>& pointer) {
	
	return get<double>(pointer->value);
}

//*
// @ brief Get type bool from JSONValue type
// 
// @ param shared_ptr<JSONValue>& pointer : referance pointer to the JSONValue
// @ return Stored bool value
// */
bool GetBoolFromJSONValue(const shared_ptr<JSONValue>& pointer) {
	if (std::holds_alternative<bool>(pointer->value)) {
		return std::get<bool>(pointer->value);
	}
}

//*
// @ brief Get type JSONObject from JSONValue type
// 
// @ param shared_ptr<JSONValue>& pointer : referance pointer to the JSONValue
// @ return Stored JSONObject value
// */
JSONObject GetJSONObjectFromJSONValue(const shared_ptr<JSONValue>& pointer) {
	return get<JSONObject>(pointer->value);
}

//*
// @ brief Get type JSONArray from JSONValue type
// 
// @ param shared_ptr<JSONValue>& pointer : referance pointer to the JSONValue
// @ return Stored JSONArray value
// */
JSONArray GetJSONArrayFromJSONValue(const shared_ptr<JSONValue>& pointer) {
	return get<JSONArray>(pointer->value);

}

//*
// @ brief Parse string to vector
// 
// Pareses the given input string to vector<string> on ',' deliminator
// 
// @ param string& inputString : Reference to string to be parsed
// @ return vector<string> : Vaecot of parsed string
// 
// */
vector<string> stringToVector(const string& inputString) {
	vector<string> stringList;
	stringstream ss(inputString);
	string word;

	while (getline(ss, word, ',')) {
		stringList.push_back(word);
	}
	return stringList;
}



//*
// @ brief Retrive held type from JSONValue
// 
// Determines and retrives held type from JSONValue object
// 
// @ param shared_ptr<JSONValue>& pointer: reference to pointer of JSONValue
// @ return any : The held type/value of the given JSONValue object
// */

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

//*
// @ brief Parse Vector<string> to vector<any>
// 
// Parses a vector<string>, where stored strings are string representations of other types
// returns represented types to "held" type and stores in vector
// 
// @ param vector<string>& inputVector : reference to the vector to be parsed
// @ param vector<any>: Vector containing the values of correct(held) type
// */
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




