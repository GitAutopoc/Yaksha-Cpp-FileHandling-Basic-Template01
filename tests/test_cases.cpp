#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <iostream>
#include <gtest/gtest.h>
#include "../fileOperations.cpp"
#include "./utils/testUtils.cpp"

using namespace curlpp::options;

TEST(CppFileHandlingProjectTest, FilePresentTrue) {
    const int filePresent = isFilePresent("sample.txt");
    TestUtils t;
    t.yakshaAssert("FilePresentTrue", filePresent, "boundary");    
    ASSERT_EQ(1, filePresent);
}

TEST(CppFileHandlingProjectTest, CreateFileAndWriteDataTrue) {
    const int dataWritten = createFileAndWriteData("test1.txt", "some sample data");
    const int fileCreated = dataWritten ? readData("test1.txt").length() ? 1 : 0 : 0;
    TestUtils t;
    t.yakshaAssert("CreateFileAndWriteDataTrue", dataWritten, "boundary");    
    ASSERT_EQ(1, dataWritten);
}

TEST(CppFileHandlingProjectTest, SearchTextTrue) {
    const int textPresent = searchText("test1.txt", "string search") ? 1 : 0;
    TestUtils t;
    t.yakshaAssert("SearchTextTrue", textPresent, "boundary");    
    ASSERT_EQ(1, textPresent);
}

TEST(CppFileHandlingProjectTest, ReadDataTrue) {
    const int readedData = readData("test1.txt").length() ? 1 : 0;
    TestUtils t;
    t.yakshaAssert("ReadDataTrue", readedData, "boundary");    
    ASSERT_EQ(1, readedData);
}

TEST(CppFileHandlingProjectTest, OpenFileAndAppendDataTrue) {
    const string data = "\nextra data";
    const int appendData = openFileAndAppendData("test1.txt", data);
    TestUtils t;
    t.yakshaAssert("OpenFileAndAppendDataTrue", appendData, "boundary");    
    ASSERT_EQ(1, appendData);
}
