#include <istream>
#include "Structs/JSONValueStruct.h"
#include <variant>

using std::variant;
using std::cout;
using std::endl;

string GetStringFromJSONValue(const shared_ptr<JSONValue>& pointer);

JSONObject GetJSONObjectFromJSONValue(const shared_ptr<JSONValue>& pointer);

JSONArray GetJSONArrayFromJSONValue(const shared_ptr<JSONValue>& pointer);

vector<string> stringToVector(const string& inputString);

bool checkIfSearchKey(const string& searchKey, const string& key);

bool checkIfContainsKey(shared_ptr<JSONValue> pointer, string& searchKey);