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
    t.yakshaAssert("FilePresentTrue", filePresent == 1 ? true : false, "boundary");    
    ASSERT_EQ(1, filePresent);
}

TEST(CppFileHandlingProjectTest, FilePresentFalse) {
    const int filePresent = isFilePresent("noFile.txt");
    TestUtils t;
    t.yakshaAssert("FilePresentFalse", filePresent == 1 ? true : false, "boundary");    
    ASSERT_EQ(0, filePresent);
}

TEST(CppFileHandlingProjectTest, CreateFileAndWriteDataTrue) {
    const int dataWritten = createFileAndWriteData("test1.txt", "some sample data");
    const int fileCreated = dataWritten ? readData("test1.txt").length() ? 1 : 0 : 0;
    TestUtils t;
    t.yakshaAssert("CreateFileAndWriteDataTrue", dataWritten == 1 ? true : false, "boundary");    
    ASSERT_EQ(1, dataWritten);
}

TEST(CppFileHandlingProjectTest, CreateFileAndWriteDataFalse) {
    const int dataWritten = createFileAndWriteData("test1.txt", "some sample data");
    const int dataRead = isFilePresent("test3.txt") ? readData("test3.txt").length() > 0 ? 1 : 0 : 0;
    TestUtils t;
    t.yakshaAssert("CreateFileAndWriteDataFalse", dataRead == 1 ? true : false, "boundary");    
    ASSERT_EQ(0, dataRead);
}

TEST(CppFileHandlingProjectTest, SearchTextTrue) {
    const int textPresent = searchText("test1.txt", "string search") ? 1 : 0;
    TestUtils t;
    t.yakshaAssert("SearchTextTrue", textPresent == 1 ? true : false, "boundary");    
    ASSERT_EQ(1, textPresent);
}

TEST(CppFileHandlingProjectTest, SearchTextFalse) {
    const int textPresent = searchText("test3.txt", "string search") ? 1 : 0;
    TestUtils t;
    t.yakshaAssert("SearchTextFalse", textPresent == 1 ? true : false, "boundary");    
    ASSERT_EQ(0, textPresent);
}

TEST(CppFileHandlingProjectTest, ReadDataTrue) {
    const int readedData = readData("test1.txt").length() ? 1 : 0;
    TestUtils t;
    t.yakshaAssert("ReadDataTrue", readedData == 1 ? true : false, "boundary");    
    ASSERT_EQ(1, readedData);
}

TEST(CppFileHandlingProjectTest, ReadDataFalse) {
    const int readedData = readData("test3.txt").length() ? 1 : 0;
    TestUtils t;
    t.yakshaAssert("ReadDataFalse", readedData == 1 ? true : false, "boundary");    
    ASSERT_EQ(0, readedData);
}

TEST(CppFileHandlingProjectTest, OpenFileAndAppendDataTrue) {
    const string data = "\nextra data";
    const int appendData = openFileAndAppendData("test1.txt", data);
    TestUtils t;
    t.yakshaAssert("OpenFileAndAppendDataTrue", appendData == 1 ? true : false, "boundary");    
    ASSERT_EQ(0, appendData);
}

TEST(CppFileHandlingProjectTest, OpenFileAndAppendDataFalse) {
    const string data = "\nextra data";
    const int appendData = isFilePresent("no_file.txt") ? openFileAndAppendData("no_file.txt", data) : 0;
    TestUtils t;
    t.yakshaAssert("OpenFileAndAppendDataFalse", appendData == 1 ? true : false, "boundary");    
    ASSERT_EQ(0, appendData);
}
