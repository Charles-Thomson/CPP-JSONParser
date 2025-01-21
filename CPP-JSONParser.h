
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

void SkipWhiteSpace(istringstream& stream);

void RemoveExternalQuoteChar(string& inputString);

string getStringFromValue(const JSONValue& jv);

shared_ptr<JSONValue> parseString(istringstream& stream);

shared_ptr<JSONValue> parseNumber(istringstream& stream);

shared_ptr<JSONValue> parseJSON(istringstream& stream);

shared_ptr<JSONValue> parseArray(istringstream& stream);

shared_ptr<JSONValue> parseObject(istringstream& stream);

bool checkAndHandleEmptyCase(istringstream& stream, char matchCaseOpen, char matchCaseClosed);

//void PrintJson(shared_ptr<JSONValue>& jsonValue, int indent = 0, bool nested = false);

bool CheckKeyExists(const shared_ptr<JSONValue>& jsonValue, const string& key);


istringstream preProcessing(string& inputString);

shared_ptr<JSONValue> ParseJson(string inputString);

string HolderFunc();

#endif // !JSON_PARSER_H







