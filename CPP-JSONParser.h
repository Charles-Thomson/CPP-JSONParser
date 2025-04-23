
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
using std::is_same_v;

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
vector<T> ConvertVectorValuesToHeldType(JSONArray& vectorToConvert) {
    int vectorSize = vectorToConvert.size();

    cout << "The size of the input vector : " << vectorSize << endl;

    vector<T> resultVector;

    for (int i = 0; vectorSize > i; i++) {
        shared_ptr<JSONValue> ptr_val = vectorToConvert[i];

        T val = ptr_val->getV<T>();

        resultVector.push_back(val);
    }

    cout << "The size of the returned vector : " << resultVector.size() << endl;

    return resultVector;
}



// Handle the nested / recurcive call 
// this assunmes that a nested vector is held
template<typename T>
void HandleNestedVectors(JSONArray& nestedVector) {
    cout << "In the handling of nested vectors func" << endl;
    cout << nestedVector.size() << endl;

    for (shared_ptr<JSONValue> held : nestedVector) {
        cout << "Holding something" << endl;
        // get the type that it is expected to be and getV of the type from -> held 
    
    
    }

    //T unNestedVector;


    //// For each held vector
    //for (vector<shared_ptr<JSONValue>> heldVec : nestedVector) {

    //    cout << "In the loop for vectors" << endl; 
    //    JSONArray heldVector = heldVec->getV<JSONArray>;
    //    string heldType = heldVector->getType();


    //    if constexpr (is_same_v<T, vector<vector<double>>>) {
    //        cout << "Matched tot he nested vector type : vector<double>" << endl;
    //        vector<double> convertedHeldVector = ConvertVectorValuesToHeldType<double>(heldVector);

    //    }
    //}
   
}

// Needs to handle the unpacking of nested Vectors
template <typename T>
T GetValueByKeyWithType(shared_ptr<JSONValue>& JSONElement, string searchKey) {\

    shared_ptr<JSONValue> JSON = GetValueByKey(JSONElement, searchKey);

    string heldType = JSON->getType();

    

    if (heldType == "JSONArray") {
        cout << "Holding a JSON Array" << endl;
        cout << typeid(T).name() << endl;

        JSONArray value = JSON->getV<JSONArray>();

        if constexpr (is_same_v <T, vector<double>>) { 
            return ConvertVectorValuesToHeldType<double>(value);        
        }

        if constexpr (is_same_v <T, vector<string>>) {   
            return ConvertVectorValuesToHeldType<string>(value);
        }

        if constexpr (is_same_v <T, vector<bool>>) {
            return ConvertVectorValuesToHeldType<bool>(value);
        }

        if constexpr (is_same_v < T, vector<shared_ptr<JSONValue>>>) {
            // T can be passed in as vector<vector<type>>
            HandleNestedVectors<T>(value); // passing value, which will be JSONArray of shared_ptr<JSONValue>
        
        
        }
    }

    return JSON->getV<T>();
}





#endif // !JSON_PARSER_H







