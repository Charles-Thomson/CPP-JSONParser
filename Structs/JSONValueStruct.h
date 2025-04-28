#ifndef JSONVALUE_STRUCT_H
#define JSONVALUE_STRUCT_H

#include<iostream>
#include<variant>
#include<String>
#include<unordered_map>
#include<vector>
#include<memory>
#include <variant>
#include <optional>
#include <typeindex>
#include <any>
#include <format>

using std::string;
using std::shared_ptr;
using std::unordered_map;
using std::vector;
using std::variant;
using std::nullptr_t;
using std::optional;
using std::nullopt;
using std::visit;
using std::decay_t;
using std::is_same_v;
using std::type_index;
using std::any;
using std::to_string;
using std::endl;
using std::cout;


struct JSONValue;

using JSONObject = unordered_map<string, shared_ptr<JSONValue>>;
using JSONVector = vector<shared_ptr<JSONValue>>;



// Acts as a linked list data structure

struct JSONValue {
    using JSONType = variant<nullptr_t, bool, double, string, JSONObject, JSONVector>;

    JSONType value;
    

    JSONValue();
    JSONValue(nullptr_t);  // Declaration only
    JSONValue(bool b);
    JSONValue(double d);
    JSONValue(const string& s);
    JSONValue(const JSONObject& obj);
    JSONValue(const JSONVector& arr);


    //*
    // @ brief Get the held value
    // 
    // Return the held value in the given type via templating(T). 
    // If the given T value does not match the held type a empty of type T is returned
    // 
    // @template T The desiered return type
    // @return The held value in type T
    // */
    template<typename T>
    T getV() {
        return visit([](const auto& val) -> T{
            using TArg = decay_t<decltype(val)>;

            if constexpr (is_same_v<TArg, T>) {
               
                return val; 
            }
            else {
                
                return T{};
            }
        }, value);
    }

   /* shared_ptr<JSONValue> GetValueFromKey(string searchKey) {
        if (holds_alternative<JSONObject>(value)) {
        
            const JSONObject& obj = get<JSONObject>(value);

            for (const auto& [key, valueI] : obj) {
                if (key == searchKey) {
                    return valueI;
                
                
                }
            }
        }
    }*/

    // Returns the value with the correct held type
    template <typename T>
    T getHeldValue() const {
        if (auto ptr = get_if<T>(&value)) {
            return *ptr;
        }
        return nullopt; // Empty if no type match
     
    }

    

    // Return the type of the value
    string getType() const {
        return visit([](const auto& val) -> string {
            using T = decay_t<decltype(val)>;  // Get type without const/reference
            if constexpr (is_same_v<T, nullptr_t>) return "null";
            else if constexpr (is_same_v<T, bool>) return "bool";
            else if constexpr (is_same_v<T, double>) return "double";
            else if constexpr (is_same_v<T, string>) return "string";
            else if constexpr (is_same_v<T, JSONObject>) return "JSONObject";
            else if constexpr (is_same_v<T, JSONVector>) return "JSONArray";
            else return "unknown";
            }, value);
    }

    // Returns the value of the type varient
    const JSONValue::JSONType& getValue() const {
        return value;
    }

};


#endif // !JSONVALUE_STRUCT_H
