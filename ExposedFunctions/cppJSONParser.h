#ifndef cppJSONParser
#define cppJSONParser

#include "../CPP-JSONParser.h"
#include "../Structs/JSONValueStruct.h"
#include "../FileReader/FileReader.h"
#include "../Testing/TestDataPreProcessing/TestDataPreProcessing.h"

using JSON = shared_ptr<JSONValue>;

shared_ptr<JSONValue> ParseToJSON(string inputString);

shared_ptr<JSONValue> GetValueByKey(shared_ptr<JSONValue>&, string);

void PrintJson(shared_ptr<JSONValue>& jsonValue, int indent = 0, bool nested = false);

template <typename T>
T GetValueByKeyWithType(shared_ptr<JSONValue>& JSONElement, string searchKey) {
    

    shared_ptr<JSONValue> JSON = GetValueByKey(JSONElement, searchKey);

    string heldType = JSON->getType();

    if (heldType == "JSONArray") {
        cout << "Holding a JSON Array" << endl;
        cout << typeid(T).name() << endl;

        if constexpr (is_same_v <T, vector<double>>) {
            JSONArray value = JSON->getV<JSONArray>();
            return ConvertVectorValuesToHeldType<double>(value);
        }

        if constexpr (is_same_v <T, vector<string>>) {
            JSONArray value = JSON->getV<JSONArray>();
            return ConvertVectorValuesToHeldType<string>(value);
        }

        if constexpr (is_same_v <T, vector<bool>>) {
            JSONArray value = JSON->getV<JSONArray>();
            return ConvertVectorValuesToHeldType<bool>(value);
        }
    }

    return JSON->getV<T>();
}




#endif // !cppJSONParser
