// CPP-JSONParser.cpp : Defines the entry point for the application.
//

#include "CPP-JSONParser.h"

// JSONParser.cpp : Defines the entry point for the application.
//


#include "FileReader/FileReader.h"
#include "Structs/JSONValueStruct.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <format>
#include <variant>
#include <map>
#include <memory>

using namespace std;

using std::string;
using std::cout;
using std::endl;
using std::ifstream;
using std::cerr;
using std::istringstream;
using std::runtime_error;
using std::unordered_map;
using std::stod;
using std::get;
using std::make_shared;
using std::variant;

//*
// @brief Remove whitespace from stream.
// 
// Removes white space for a given stream 
// Direct update to stream via reference passing.
// 
// @param stream The given istringstream
// */
void SkipWhiteSpace(istringstream& stream) {
	char ch;
	while (stream.get(ch)) {
		if (!isspace(ch)) {
			stream.putback(ch);
			break;
		}

	}
}

//*
// @Brief return a string from JSONValue type
// 
// Checks if the given JSONValue can return a string
// Returns if possible
// 
// @param jv The given JSONValue
// 
// @return string REpresentation of the given JSONValue
// 
// */
string getStringFromValue(const JSONValue& jv) {
	if (holds_alternative<string>(jv.value)) {
		return get<string>(jv.value);

	}
	return "";
}

//*
// 
// @Brief Parse stream to String
// 
// Parse a istringstream to a shared ptr <JSONValue> 
// 
// @param stream The given istringstream to be parsed
// @return result The parsed istreamstring element as a shared_ptr<JSONValue>
// */
shared_ptr<JSONValue> parseString(istringstream& stream) {
	char ch;

	string result;
	if (stream.get(ch) && ch == '\"') { // Indicates the start of a string
		/*cout << ch << endl;*/
		while (stream.get(ch)) {
			if (ch == '\"') { // Indicates the end of the string
				break;
			}
			result += ch;
			/*cout << result << endl;*/
		}
	}
	else {

		throw runtime_error("Expacted '\"'  at the start of string  ");
		cout << "String malformed" << endl;
	}
	return make_shared<JSONValue>(result);
}

//*
// 
// @Brief Parse stream to double
// 
// Parse a istringstream to a ptr for a JSONValue
// 
// @param stream The given istringstream to be parsed
// @return The parsed istreamstring element as a shared_ptr<JSONValue>
// */
shared_ptr<JSONValue> parseNumber(istringstream& stream) {
	string result;
	char ch;

	// Need to add in conditions for checking for . - ect 
	while (stream.get(ch) && isdigit(ch)) {
		result += ch;
		/*cout << result << endl;*/
	}

	// If the next character isn't a digit, put it back in the stream
	if (stream && !isdigit(ch)) {
		stream.putback(ch);  // Put the non-digit character back to stream
	}

	return make_shared<JSONValue>(result);

}


shared_ptr<JSONValue> parseObject(istringstream& stream);
shared_ptr<JSONValue> parseArray(istringstream& stream);


//*
// @Brief Case Switch based on char
// 
// Handles parsing func to be called based on the given char
// 
// @param istringstream& stream Referance to the input stream
// 
// @return shared_ptr<JSONValue> ptr for the parsed result
// */
shared_ptr<JSONValue> determineJSONType(istringstream& stream) {
	SkipWhiteSpace(stream);

	char ch;
	shared_ptr<JSONValue> returnPtr;

	ch = stream.peek();

	if (ch == '{') {
		/*cout << "Parsing Object" << endl;*/
		returnPtr = parseObject(stream);
	}
	else if (ch == '[') {
		/*cout << "Parsing Array" << endl;*/
		returnPtr = parseArray(stream);
	}
	else if (ch == '\"') {
		/*cout << "Parsing String" << endl;*/
		returnPtr = parseString(stream);
	}
	else if (isdigit(ch)) {
		/*cout << "parsing double" << endl;*/
		returnPtr = parseNumber(stream);
	}

	return returnPtr;
}


//*
// @Brief Check & handle if Object or array is empty
// 
// Checks if an object or array , indicated by '[]' or '{}', is empty. 
// Consumes and returns true if no contents is found
// 
// @param stream The given input stream
// @param matchCaseOpen The opening indicator of the type i.e { or [
// @param matchCaseClose The closing indicator of the type i.e } or ]
// 
// #return bool If the given case is Empty or contains content
// 
// */
bool checkAndHandleEmptyCase(istringstream& stream, char matchCaseOpen, char matchCaseClose) {
	char ch;
	if (stream.get(ch) && ch == matchCaseOpen) {
		SkipWhiteSpace(stream);
		if (stream.peek() == matchCaseClose) {
			stream.get(ch); // Consume the closing element i.e "]" "}"
			return true;
		}

	}
	return false;

}

//*
// @Brief Parse a string to JSONArray
// 
// Parse a string to a JSONArray as indicated by "[]". Handles nested through recursive call to pareseJSON
// 
// @param istringstream& stream Referance to the input stream
// 
// @return shared_ptr<JSONValue> ptr for the parsed JSONValue
// */
shared_ptr<JSONValue> parseArray(istringstream& stream) {
	JSONArray ary;
	char ch;

	if (checkAndHandleEmptyCase(stream, '[', ']')) {
		return make_shared<JSONValue>(ary);
	}

	do {
		SkipWhiteSpace(stream);

		shared_ptr<JSONValue> value = determineJSONType(stream);
		ary.emplace_back(value);

		SkipWhiteSpace(stream);

	} while (stream.get(ch) && ch == ',');

	if (ch != ']') {
		throw runtime_error("Expected ']' at the end of array");
	}

	/*cout << "Array parsed" << endl;*/

	return make_shared<JSONValue>(ary);
}


//*
// 
// @Brief Parse a string to JSONObject
// 
// Parse a string to a JSONObject as indicated by "{}". Handles nested objects
// 
// @param istringstream& stream Referance to the input stream
// 
// @return shared_ptr<JSONValue> ptr for the parsed JSONObject
// */
shared_ptr<JSONValue> parseObject(istringstream& stream) {
	JSONObject obj;
	char ch;

	if (checkAndHandleEmptyCase(stream, '{', '}')) {
		return make_shared<JSONValue>(obj);
	}

	do {
		SkipWhiteSpace(stream);

		shared_ptr<JSONValue> key = determineJSONType(stream); // Get the key 
		string keyString = getStringFromValue(*key); // Key is always a string

		SkipWhiteSpace(stream);

		if (stream.get(ch) && ch == ':') {
			SkipWhiteSpace(stream);

			shared_ptr<JSONValue> value = determineJSONType(stream);

			obj[keyString] = value;  // save as key - value to obj
			
		}
		else {
			string found = string(1, ch);
			string errorMessage = "Expacted ':' - but found : " + found;
			throw runtime_error(errorMessage);

		}

	} while (stream.get(ch) && ch == ','); // After the parse the next char should be a ","

	if (ch != '}') {
		cout << "The found char : " << ch << endl;
		throw runtime_error("Expected '}' at the end of object.");
	}

	return make_shared<JSONValue>(obj);

}

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
void PrintJson(const shared_ptr<JSONValue>& jsonValue, int indent = 0, bool nested = false) {

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
		cout <<  "   " << endl;
	}
}


//*
// @Brief Get Key,value from shared_ptr<JSONValue>
// 
// Get the stored key value pair from a shared_ptr<JSONValue>
// 
// @param inputPtr The given shared_ptr<JSONValue>
// @retrun string, value pair
// */
shared_ptr<JSONValue> GetValueByKey(shared_ptr<JSONValue>& JSONElement, string& searchKey) {

	// Passing in the full object

	// Need to get the value from the objct

	// Loop through to find the matching key 

	if (holds_alternative<JSONObject>(JSONElement->value)) {

		const JSONObject& obj = get<JSONObject>(JSONElement->value);

		for(const auto& [key , value] : obj) {
			if (key == searchKey) {
				return value;
			}
		
		}
		
	}
	return JSONElement;
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
bool CheckKeyExists(const shared_ptr<JSONValue>& jsonValue, const string& key) {

	if (jsonValue && holds_alternative<JSONObject>(jsonValue->value)) {

		const auto& obj = get<JSONObject>(jsonValue->value);
		auto it = obj.find(key); // Search for the key

		if (it != obj.end()) {  // Check if the key exists
			return true;
		}
		return false;
	}
	return false;
}

//*
// @Brief preProcessing of input string
// 
// Remove outermost quotes if present
// convert to istringstream and return
// 
// @ param inputString The string to be preProcessed
// @ return istringstream Of the given inputString
// */
istringstream preProcessing(string& inputString) {
	/*RemoveExternalQuoteChar(inputString);*/

	return istringstream(inputString);
}

shared_ptr<JSONValue> ParseJson(string inputString) {
	istringstream stream = preProcessing(inputString);
	shared_ptr<JSONValue> returnedPtr = determineJSONType(stream);
	return returnedPtr;

}










