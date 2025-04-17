# CMakeList.txt : CMake project for CPP-JSONParser, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.12)

set(CMAKE_CXX_STANDARD 20)  # Ensure C++20 is enabled
set(CMAKE_CXX_STANDARD_REQUIRED ON)  # Require C++20 features

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zi")  # Enable debug information
endif()

project ("CPP-JSONParser")

# Add source to this project's executable.

# Add a library
add_library(CPP-JSONParser 
    CPP-JSONParser.cpp
    CPP-JSONParser.h
    Structs/JSONValueStruct.cpp
    Structs/JSONValueStruct.h
    FileReader/FileReader.cpp
    FileReader/FileReader.h
    
    HelperFunctions/TypeConversions.h
    HelperFunctions/TypeConversions.cpp
    HelperFunctions/PrintJSON.h
    HelperFunctions/PrintJSON.cpp
    Testing/TestDataPreProcessing/TestDataPreProcessing.h
    Testing/TestDataPreProcessing/TestDataPreProcessing.cpp
    Testing/ParserTests/SupportingTestFunctions.h
    Testing/ParserTests/SupportingTestFunctions.cpp
    
    ExposedFunctions/CheckIfContainsKey.h   
    ExposedFunctions/cppJSONParser.h
)

#Source Files
set(SOURCES
    CPP-JSONParser.cpp
    Structs/JSONValueStruct.cpp
    FileReader/FileReader.cpp
    HelperFunctions/TypeConversions.cpp
    HelperFunctions/PrintJSON.cpp
    Testing/TestDataPreProcessing/TestDataPreProcessing.cpp
    Testing/ParserTests/SupportingTestFunctions.cpp
)

#Private Headers - not exposed
set(HEADERS_PRIVATE
    CPP-JSONParser.h
    Structs/JSONValueStruct.h
    FileReader/FileReader.h
    HelperFunctions/TypeConversions.h
    HelperFunctions/PrintJSON.h
    Testing/TestDataPreProcessing/TestDataPreProcessing.h
    Testing/ParserTests/SupportingTestFunctions.h
)

#Public headers - exposed
set(HEADERS_PUBLIC
    ExposedFunctions/cppJSONParser.h
    ExposedFunctions/CheckIfContainsKey.h
)

#Create Static Lib
add_library(CPP-JSONParserStatic STATIC ${SOURCES} ${HEADERS_PRIVATE} ${HEADERS_PUBLIC})

# Set up include directories
target_include_directories(CPP-JSONParserStatic 
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/ExposedFunctions
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/HelperFunctions
        ${CMAKE_CURRENT_SOURCE_DIR}/FileReader
        ${CMAKE_CURRENT_SOURCE_DIR}/Structs
        ${CMAKE_CURRENT_SOURCE_DIR}/Testing
)



#add_library(CPP-JSONParserStatic STATIC PROPORTIES  
#    ExposedFunctions/cppJSONParser.h
#)

# Fetch fmt library
include(FetchContent)

FetchContent_Declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG        8.0.1
)
FetchContent_MakeAvailable(fmt)


# Fetch Google Test
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.11.0
)
FetchContent_MakeAvailable(googletest)

include(GoogleTest)

# Force consistent runtime 
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MDd")  # Dynamic debug runtime
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /MDd")  # Dynamic debug runtime for C
    set_target_properties(gtest PROPERTIES COMPILE_OPTIONS "/MDd")
    set_target_properties(gtest_main PROPERTIES COMPILE_OPTIONS "/MDd")
endif()



#Testing


option(CPP_JSONPARSER_BUILD_TESTS "Build tests for CPP-JSONParser" ON)

if(CPP_JSONPARSER_BUILD_TESTS)
    # Enable testing
    enable_testing()
endif()



#Executables
 add_executable(file_reader_tests Testing/FileReaderTests/FileReaderTests.cpp  )

 add_executable(json_parser_tests Testing/ParserTests/JSONParserTests.cpp  )

 add_executable(json_value_struct_tests Testing/StructTesting/JSONValueStructTests.cpp  )

 add_executable(parser_type_tests  Testing/ParserTests/TypeParsingTests/VectorParcingTests.cpp  )



# Set runtime library for test target (match the option you selected above)
target_compile_options(file_reader_tests PRIVATE /MDd)

target_compile_options(json_parser_tests PRIVATE /MDd)

target_compile_options(json_value_struct_tests PRIVATE /MDd)

target_compile_options(parser_type_tests PRIVATE /MDd)

set(TEST_TARGETS
    file_reader_tests
    json_parser_tests
    json_value_struct_tests
    parser_type_tests
)

foreach(target IN LISTS TEST_TARGETS)
    target_include_directories(${target} PRIVATE 
        "${CMAKE_SOURCE_DIR}"
        "${CMAKE_SOURCE_DIR}/FileReader"
        "${CMAKE_SOURCE_DIR}/Structs"
        "${CMAKE_SOURCE_DIR}/HelperFunctions"
        "${CMAKE_SOURCE_DIR}/Testing"
        "${gtest_SOURCE_DIR}/include"
    )
endforeach()


# Set the global path
set(TEST_FILE_PATH "C:/Users/Charl/source/repos/C++/CPP-JSONParser/Testing/TestData/")
message(STATUS "TEST_FILE_PATH is set to: ${TEST_FILE_PATH}")  # Debugging output

# Set the global path
set(TYPE_TEST_FILE_PATH "C:/Users/Charl/source/repos/C++/CPP-JSONParser/Testing/TestData/Type_testing/")
message(STATUS "TYPE_TEST_FILE_PATH is set to: ${TYPE_TEST_FILE_PATH}")  # Debugging output

# Define the preprocessor definition for all targets
add_compile_definitions(TEST_FILE_PATH="${TEST_FILE_PATH}")

# Define the preprocessor definition for all targets
add_compile_definitions(TYPE_TEST_FILE_PATH="${TYPE_TEST_FILE_PATH}")

# Pass the file path as a compile definition to individual targets
target_compile_definitions(file_reader_tests PRIVATE TEST_INPUT_FILE_PATH="${TEST_FILE_PATH}")
target_compile_definitions(json_parser_tests PRIVATE TEST_INPUT_FILE_PATH="${TEST_FILE_PATH}")
target_compile_definitions(json_value_struct_tests PRIVATE TEST_INPUT_FILE_PATH="${TEST_FILE_PATH}")
target_compile_definitions(CPP-JSONParser PRIVATE TEST_INPUT_FILE_PATH="${TEST_FILE_PATH}")
target_compile_definitions(parser_type_tests PRIVATE TYPE_TEST_FILE_PATH="${TYPE_TEST_FILE_PATH}")

#Link Google Tests and project Libs
target_link_libraries(file_reader_tests PRIVATE gtest gtest_main CPP-JSONParser fmt::fmt)
target_link_libraries(json_parser_tests PRIVATE gtest gtest_main CPP-JSONParser fmt::fmt)
target_link_libraries(json_value_struct_tests PRIVATE gtest gtest_main CPP-JSONParser fmt::fmt)
target_link_libraries(parser_type_tests PRIVATE gtest gtest_main CPP-JSONParser fmt::fmt)

#Add Tests
add_test(NAME FileReaderTests COMMAND file_reader_tests)
add_test(NAME JSONParserTests COMMAND json_parser_tests)
add_test(NAME JSONValueStructTests COMMAND json_value_struct_tests)
add_test(NAME TypeParcingTests COMMAND parser_type_tests)

#Gtests Discovery 
gtest_discover_tests(file_reader_tests)
gtest_discover_tests(json_parser_tests)
gtest_discover_tests(json_value_struct_tests)
gtest_discover_tests(parser_type_tests)