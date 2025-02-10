#ifndef PRINT_JSON_H
#define PRINT_JSON_H

#include "../Structs/JSONValueStruct.h"

void PrintJson(const shared_ptr<JSONValue>& jsonValue, int indent = 0, bool nested = false);

#endif PRINT_JSON_H