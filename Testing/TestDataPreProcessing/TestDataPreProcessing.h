#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <list>
#include <fstream> 
#include <tuple>
#include <sstream>
#include <typeindex>
#include <variant>
#include <unordered_map>
#include <format>
#include <map>
#include <memory>


tuple<shared_ptr<JSONValue>, vector<string>, vector<string>> processTestData(const tuple<string, string, string, bool> rawTestData);

tuple<shared_ptr<JSONValue>, vector<string>, vector<string>> getTestData();


