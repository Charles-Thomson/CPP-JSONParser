
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


using std::variant;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::stringstream;

string GetStringFromJSONValue(const shared_ptr<JSONValue>& pointer) {
	return get<string>(pointer->value);
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
