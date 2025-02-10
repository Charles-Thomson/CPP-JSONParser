
#include "TypeConversions.h"
#include <vector>
using std::variant;
using std::cout;
using std::endl;
using std::vector;

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
