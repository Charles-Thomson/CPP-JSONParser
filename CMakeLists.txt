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
add_library(CPP-JSONParser SHARED
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
)

add_library(CPP-JSONParserStatic STATIC 
    CPP-JSONParser.cpp
    CPP-JSONParser.h
)

# Enable testing
enable_testing()

# Fetch Google Test
include(FetchContent)
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

#Executables
# add_executable(file_reader_tests Testing/FileReaderTests/FileReaderTests.cpp )

# add_executable(json_parser_tests Testing/ParserTests/JSONParserTests.cpp )

# Set runtime library for test target (match the option you selected above)
#target_compile_options(file_reader_tests PRIVATE /MDd)

#target_compile_options(json_parser_tests PRIVATE /MDd)

#Target Libs
#target_include_directories(file_reader_tests PRIVATE
#   "${CMAKE_SOURCE_DIR}"
#  "${CMAKE_SOURCE_DIR}/FileReader"
# "${CMAKE_SOURCE_DIR}/Structs"
#"${CMAKE_SOURCE_DIR}/HelperFunctions"
#)

#target_include_directories(json_parser_tests PRIVATE
#    "${CMAKE_SOURCE_DIR}"
#    "${CMAKE_SOURCE_DIR}/FileReader"
#    "${CMAKE_SOURCE_DIR}/Structs"
#    "${CMAKE_SOURCE_DIR}/HelperFunctions"
#    "${CMAKE_SOURCE_DIR}/Testing"
#)


# Pass file path as a compile definition
#target_compile_definitions(file_reader_tests PRIVATE 
#    TEST_INPUT_FILE_PATH="C:/Users/Charl/source/repos/C++/CPP-JSONParser/Testing/TestData/"
#)

# Pass file path as a compile definition
#target_compile_definitions(json_parser_tests PRIVATE 
#    TEST_INPUT_FILE_PATH="C:/Users/Charl/source/repos/C++/CPP-JSONParser/Testing/TestData/"
#)


#Link Google Tests and project Libs
#target_link_libraries(file_reader_tests PRIVATE gtest gtest_main CPP-JSONParser)
#target_link_libraries(json_parser_tests PRIVATE gtest gtest_main CPP-JSONParser)


#Add Tests
#add_test(NAME FileReaderTests COMMAND file_reader_tests)
#add_test(NAME JSONParserTests COMMAND json_parser_tests)


#Gtests Discovery 
#gtest_discover_tests(file_reader_tests)
#gtest_discover_tests(json_parser_tests)