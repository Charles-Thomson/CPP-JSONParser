﻿// CPP-JSONParser.cpp : Defines the entry point for the application.

#include "CPP-JSONParser.h"

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
		
		while (stream.get(ch)) {
			if (ch == '\"') { // Indicates the end of the string
				break;
			}
			result += ch;
			
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
	while (stream.get(ch) && isdigit(ch) || ch == '.') {
		result += ch;
	}

	// If the next character isn't a digit, put it back in the stream
	if (stream && !isdigit(ch)) {
		stream.putback(ch);  // Put the non-digit character back to stream
	}

	
	double resultAsDouble = std::stod(result);

	return make_shared<JSONValue>(resultAsDouble);

}


shared_ptr<JSONValue> parseObject(istringstream& stream);
shared_ptr<JSONValue> parseArray(istringstream& stream);



//*
// @ brief Parse tream to bool
// 
// 
// */

shared_ptr<JSONValue> parseBoolean(istringstream& stream) {
	string result;
	char ch;

	while (stream.get(ch) && isalpha(ch)) {
		result += ch;
	}

	if (result == "true") {
		return make_shared<JSONValue>(true);
	
	}
	else if (result == "false") {
		return make_shared<JSONValue>(false);
	}
	else {
		throw runtime_error("Invalid bool");
	}
}

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
		
		returnPtr = parseObject(stream);
	}
	else if (ch == '[') {
		
		returnPtr = parseArray(stream);
	}
	else if (ch == '\"') {
		
		returnPtr = parseString(stream);
	}
	else if (isdigit(ch)) {
		
		returnPtr = parseNumber(stream);
	}
	else {
		if (isalpha(ch)) {
			string token;
			while (stream.get(ch) && isalpha(ch)) {
				token += ch;
			}
			stream.putback(ch);


			if (token == "true" ) {
				return make_shared<JSONValue >(true);
			
			} else if (token == "false") {
				return make_shared<JSONValue>(false);

			}
			else {
				throw runtime_error("Unexpected Token " + token);
			}
		}
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
	JSONVector ary;
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
		string keyString = key->getV<string>();

		SkipWhiteSpace(stream);

		if (stream.get(ch) && ch == ':') {
			SkipWhiteSpace(stream);

			shared_ptr<JSONValue> value = determineJSONType(stream);

			obj[keyString] = value;  // save as key - value to obj
			SkipWhiteSpace(stream); // Skip any white space after the value
		}
		else {
			string found = string(1, ch);
			string errorMessage = "Expacted ':' - but found : " + found;
			throw runtime_error(errorMessage);

		}

	} while (stream.get(ch) && ch == ','); // After the parse the next char should be a ","

	if (ch != '}') {
		cout << "The found char : " << ch << endl;
		cout << "The remaining string to be parsed : " << stream.rdbuf() << endl;
		throw runtime_error("Expected '}' at the end of object.");
	}

	return make_shared<JSONValue>(obj);

}

//*
// @Brief Get Key,value from shared_ptr<JSONValue>
// 
// Get the stored key value pair from a shared_ptr<JSONValue>
// 
// @param inputPtr The given shared_ptr<JSONValue>
// @retrun string, value pair
// */
shared_ptr<JSONValue> GetValueByKey(shared_ptr<JSONValue>& JSONElement, string searchKey) {

	// Check a value is being held
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



// Rework of GetValueByKey

//template <typename T>
//T GetValueByKeyWithT(shared_ptr<JSONValue>& JSONElement, string searchKey) {
//	shared_ptr<JSONValue> JSON = GetValueByKey(JSONElement, searchKey);
//
//	return JSON->getV<T>();
//}

shared_ptr<JSONValue> ParseToJSON(string inputString) {
	istringstream stream = istringstream(inputString);
	shared_ptr<JSONValue> returnedPtr = determineJSONType(stream);
	return returnedPtr;

}










