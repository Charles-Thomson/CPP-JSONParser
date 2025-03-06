
#ifndef Check_IF_KEY_CONTAINS_H
#define Check_IF_KEY_CONTAINS_H



#include "../HelperFunctions/TypeConversions.h"
#include "../Structs/JSONValueStruct.h"

#include <variant>
#include <istream>
#include <format>
#include "../Testing/ParserTests/SupportingTestFunctions.h"

using std::string;
using std::variant;
using std::cout;
using std::endl;
using std::any_cast;



bool checkIfContainsKeyExposed(shared_ptr<JSONValue> pointer, string& searchKey);

bool checkIfSearchKey(const string& searchKey, const string& key);

#endif // !Check_IF_KEY_CONTAINS_H
