
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
vector<T> ConvertVectorValuesToHeldType(JSONVector& vectorToConvert) {
    int vectorSize = vectorToConvert.size();

    vector<T> resultVector;

    for (int i = 0; vectorSize > i; i++) {
        shared_ptr<JSONValue> ptr_val = vectorToConvert[i];

        T val = ptr_val->getV<T>();

        resultVector.push_back(val);
    }
    return resultVector;
}



//*
// @brief Handle nested vectors
// 
// Handle vectors nested within other vectors to a single level of nesting
// 
// @param nestedVector Vector that is known to contain nested vectors
// @return rtnVector Vector containing nexted vecotors all parsed to correct type
// */
template<typename T>
T HandleNestedVectors(JSONVector& nestedVector) {
    T rtnVector;

    for (shared_ptr<JSONValue> ptr : nestedVector) {
        
        JSONVector vec = ptr->getV<JSONVector>();

        if constexpr (is_same_v<T, vector<vector<double>>>) {
            vector<double> convertedHeldVector = ConvertVectorValuesToHeldType<double>(vec);
            rtnVector.push_back(convertedHeldVector); 
        } 

        if constexpr (is_same_v<T, vector<vector<string>>>) {
            vector<double> convertedHeldVector = ConvertVectorValuesToHeldType<string>(vec);
            rtnVector.push_back(convertedHeldVector);
        }

        if constexpr (is_same_v<T, vector<vector<bool>>>) {
            vector<double> convertedHeldVector = ConvertVectorValuesToHeldType<bool>(vec);
            rtnVector.push_back(convertedHeldVector);
        }
    }
    return rtnVector;
}


// Helper trait to detect if T is a vector of vectors
template<typename T>
struct is_vector_of_vector : std::false_type {};

template<typename U>
struct is_vector_of_vector<std::vector<std::vector<U>>> : std::true_type {};



//*
// @ brief Handle the parsing of JSONVector 
// 
// Handle the parsing of the JSONVector to a vecotr of the correct held type
// 
// @param JSONData JSON(shared_ptr<JSONValuve>) data known to contain the vector
// @return retrunData JSON data parsed to correct vector type
// */
template <typename T>
T HandleJSONVectorReturn(shared_ptr<JSONValue>& JSONData) {

    cout << "HandleJSONVectorReturn -> handling a JSON ARRAY" << endl;
    
    T retrunData;

    JSONVector vectorDataAsJSON = JSONData->getV<JSONVector>();

    if constexpr (is_same_v <T, vector<double>>) {
        return ConvertVectorValuesToHeldType<double>(vectorDataAsJSON);
    }

    if constexpr (is_same_v <T, vector<string>>) {
        return ConvertVectorValuesToHeldType<string>(vectorDataAsJSON);
    }

    if constexpr (is_same_v <T, vector<bool>>) {
        return ConvertVectorValuesToHeldType<bool>(vectorDataAsJSON);
    }

    if constexpr (is_vector_of_vector<T>::value) {
        return HandleNestedVectors<T>(vectorDataAsJSON); // passing value, which will be JSONArray of shared_ptr<JSONValue>
    }

    return retrunData;

}



// Needs to handle the unpacking of nested Vectors
template <typename T>
T GetValueByKeyWithType(shared_ptr<JSONValue>& JSONElement, string searchKey) {\

    shared_ptr<JSONValue> JSONdata = GetValueByKey(JSONElement, searchKey);

    string heldType = JSONdata->getType();

    if (heldType == "JSONArray") {
        return HandleJSONVectorReturn<T>(JSONdata);
    }

    return JSONdata->getV<T>();
}





#endif // !JSON_PARSER_H







