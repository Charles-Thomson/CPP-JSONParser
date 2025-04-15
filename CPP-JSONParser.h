﻿
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

shared_ptr<JSONValue> GetValueByKey(shared_ptr<JSONValue>&, string); 


// The type passed is the type of the vector i.e vector<double> T = double
template <typename T>
vector<T> ConvertVectorValuesToHeldType(vector<shared_ptr<JSONValue>>& vectorToConvert) {
    int vectorSize = vectorToConvert.size();

    cout << "The size of the input vector : " << vectorSize << endl;

    vector<T> resultVector;

    for (int i = 0; vectorSize > i; i++) {
        shared_ptr<JSONValue> ptr_val = vectorToConvert[i];

        T val = ptr_val->getHeldValue<T>();

        resultVector.push_back(val);
    }

    cout << "The size of the returned vector : " << resultVector.size() << endl;

    return resultVector;
}


template <typename T>
T GetValueByKeyWithType(shared_ptr<JSONValue>& JSONElement, string searchKey) {
    shared_ptr<JSONValue> JSON = GetValueByKey(JSONElement, searchKey);

    string heldType = JSON->getType();

    if (heldType == "JSONArray") {
        cout << "Holding a JSON Array" << endl;

        if (typeid(T) == typeid(vector<double>)) {

            cout << "Of type double" << endl;

            //"Returning the vector - type shared_ptr<JSONArray>"
            JSONArray value = JSON->getV<JSONArray>();

            cout << value.size() << endl;


            /*vector<double> convertedVector = ConvertVectorValuesToHeldType<double>(value);*/
        }
    }

    return JSON->getV<T>();
}





#endif // !JSON_PARSER_H







