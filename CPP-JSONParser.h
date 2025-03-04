
#ifndef JSON_PARSER_H
#define JSON_PARSER_H

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
using std::ifstream;
using std::cerr;
using std::istringstream;
using std::stod;
using std::get;
using std::make_shared;
using std::variant;

void SkipWhiteSpace(istringstream& stream);

string getStringFromValue(const JSONValue& jv);

shared_ptr<JSONValue> parseString(istringstream& stream);

shared_ptr<JSONValue> parseNumber(istringstream& stream);

shared_ptr<JSONValue> determineJSONType(istringstream& stream);

shared_ptr<JSONValue> parseArray(istringstream& stream);

shared_ptr<JSONValue> parseObject(istringstream& stream);

bool checkAndHandleEmptyCase(istringstream& stream, char matchCaseOpen, char matchCaseClosed);

void PrintJson(shared_ptr<JSONValue>& jsonValue, int indent = 0, bool nested = false);

istringstream preProcessing(string& inputString);

string TestReturn();

shared_ptr<JSONValue> ParseToJSON(string inputString);

shared_ptr<JSONValue> GetValueByKey(shared_ptr<JSONValue>&, string&); 



#endif // !JSON_PARSER_H







