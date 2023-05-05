#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <iostream>
#include <gtest/gtest.h>
#include "../fileOperations.cpp"

using namespace curlpp::options;

TEST(CppFileHandlingProjectTest, FilePresentTrue) {
    curlpp::Cleanup cleanup;
    curlpp::Easy request;
    request.setOpt(curlpp::options::Url(std::string("https://jsonplaceholder.typicode.com/posts")));
    std::list<std::string> header = {
        "Content-Type: application/json",
        "accept: application/json"
    }; 
    request.setOpt(new curlpp::options::HttpHeader(header));
    const int filePresent = isFilePresent("sample.txt");
    std::string query = filePresent ? "[{\"FilePresentTrue\":1}]" : "[{\"FilePresentTrue\":0}]";
    request.setOpt(new curlpp::options::PostFields(query)); 
    // request.setOpt(new curlpp::options::WriteStream(&std::cout));
    // request.perform();
    ASSERT_EQ(1, filePresent);
}

TEST(CppFileHandlingProjectTest2, FilePresentFalse) {
    curlpp::Cleanup cleanup;
    curlpp::Easy request;
    request.setOpt(curlpp::options::Url(std::string("https://jsonplaceholder.typicode.com/posts")));
    std::list<std::string> header = {
        "Content-Type: application/json",
        "accept: application/json"
    }; 
    request.setOpt(new curlpp::options::HttpHeader(header)); 
    const int filePresent = isFilePresent("noFile.txt");
    std::string query = filePresent ? "[{\"FilePresentFalse\":1}]" : "[{\"FilePresentFalse\":0}]";
    request.setOpt(new curlpp::options::PostFields(query)); 
    // request.setOpt(new curlpp::options::WriteStream(&std::cout));
    // request.perform();
    ASSERT_EQ(0, filePresent);
}

TEST(CppFileHandlingProjectTest, CreateFileAndWriteDataTrue) {
    curlpp::Cleanup cleanup;
    curlpp::Easy request;
    request.setOpt(curlpp::options::Url(std::string("https://jsonplaceholder.typicode.com/posts")));
    std::list<std::string> header = {
        "Content-Type: application/json",
        "accept: application/json"
    };
    request.setOpt(new curlpp::options::HttpHeader(header));
    const int dataWritten = createFileAndWriteData("test1.txt", "some sample data");
    const int fileCreated = dataWritten ? readData("test1.txt").length() ? 1 : 0 : 0;
    std::string query = dataWritten ? "[{\"CreateFileAndWriteDataTrue\":1}]" : "[{\"CreateFileAndWriteDataTrue\":0}]";
    request.setOpt(new curlpp::options::PostFields(query)); 
    // request.setOpt(new curlpp::options::WriteStream(&std::cout));
    // request.perform();
    ASSERT_EQ(1, dataWritten);
}

TEST(CppFileHandlingProjectTest, CreateFileAndWriteDataFalse) {
    curlpp::Cleanup cleanup;
    curlpp::Easy request;
    request.setOpt(curlpp::options::Url(std::string("https://jsonplaceholder.typicode.com/posts")));
    std::list<std::string> header = {
        "Content-Type: application/json",
        "accept: application/json"
    };
    request.setOpt(new curlpp::options::HttpHeader(header));
    const int dataWritten = createFileAndWriteData("test1.txt", "some sample data");
    const int dataRead = isFilePresent("test3.txt") ? readData("test3.txt").length() > 0 ? 1 : 0 : 0;
    std::string query = dataRead ? "[{\"CreateFileAndWriteDataFalse\":1}]" : "[{\"CreateFileAndWriteDataFalse\":0}]";
    request.setOpt(new curlpp::options::PostFields(query)); 
    // request.setOpt(new curlpp::options::WriteStream(&std::cout));
    // request.perform();
    ASSERT_EQ(0, dataRead);
}

TEST(CppFileHandlingProjectTest, SearchTextTrue) {
    curlpp::Cleanup cleanup;
    curlpp::Easy request;
    request.setOpt(curlpp::options::Url(std::string("https://jsonplaceholder.typicode.com/posts")));
    std::list<std::string> header = {
        "Content-Type: application/json",
        "accept: application/json"
    };
    request.setOpt(new curlpp::options::HttpHeader(header));
    const int textPresent = searchText("test1.txt", "string search") ? 1 : 0;
    std::string query = textPresent ? "[{\"SearchTextTrue\":1}]" : "[{\"SearchTextTrue\":0}]";
    request.setOpt(new curlpp::options::PostFields(query)); 
    // request.setOpt(new curlpp::options::WriteStream(&std::cout));
    // request.perform();
    ASSERT_EQ(1, textPresent);
}

TEST(CppFileHandlingProjectTest, SearchTextFalse) {
    curlpp::Cleanup cleanup;
    curlpp::Easy request;
    request.setOpt(curlpp::options::Url(std::string("https://jsonplaceholder.typicode.com/posts")));
    std::list<std::string> header = {
        "Content-Type: application/json",
        "accept: application/json"
    };
    request.setOpt(new curlpp::options::HttpHeader(header));
    const int textPresent = searchText("test3.txt", "string search") ? 1 : 0;
    std::string query = textPresent ? "[{\"SearchTextFalse\":1}]" : "[{\"SearchTextFalse\":0}]";
    request.setOpt(new curlpp::options::PostFields(query)); 
    // request.setOpt(new curlpp::options::WriteStream(&std::cout));
    // request.perform();
    ASSERT_EQ(0, textPresent);
}

TEST(CppFileHandlingProjectTest, ReadDataTrue) {
    curlpp::Cleanup cleanup;
    curlpp::Easy request;
    request.setOpt(curlpp::options::Url(std::string("https://jsonplaceholder.typicode.com/posts")));
    std::list<std::string> header = {
        "Content-Type: application/json",
        "accept: application/json"
    };
    request.setOpt(new curlpp::options::HttpHeader(header));
    const int readedData = readData("test1.txt").length() ? 1 : 0;
    std::string query = readedData ? "[{\"ReadDataTrue\":1}]" : "[{\"ReadDataTrue\":0}]";
    request.setOpt(new curlpp::options::PostFields(query)); 
    // request.setOpt(new curlpp::options::WriteStream(&std::cout));
    // request.perform();
    ASSERT_EQ(1, readedData);
}

TEST(CppFileHandlingProjectTest, ReadDataFalse) {
    curlpp::Cleanup cleanup;
    curlpp::Easy request;
    request.setOpt(curlpp::options::Url(std::string("https://jsonplaceholder.typicode.com/posts")));
    std::list<std::string> header = {
        "Content-Type: application/json",
        "accept: application/json"
    };
    request.setOpt(new curlpp::options::HttpHeader(header));
    const int readedData = readData("test3.txt").length() ? 1 : 0;
    std::string query = readedData ? "[{\"ReadDataFalse\":1}]" : "[{\"ReadDataFalse\":0}]";
    request.setOpt(new curlpp::options::PostFields(query)); 
    // request.setOpt(new curlpp::options::WriteStream(&std::cout));
    // request.perform();
    ASSERT_EQ(0, readedData);
}

TEST(CppFileHandlingProjectTest, OpenFileAndAppendDataTrue) {
    curlpp::Cleanup cleanup;
    curlpp::Easy request;
    request.setOpt(curlpp::options::Url(std::string("https://jsonplaceholder.typicode.com/posts")));
    std::list<std::string> header = {
        "Content-Type: application/json",
        "accept: application/json"
    };
    request.setOpt(new curlpp::options::HttpHeader(header));
    const string data = "\nextra data";
    createFileAndWriteData("test1.txt", "some sample data");
    const int appendData = openFileAndAppendData("test1.txt", data);
    std::string query = appendData ? "[{\"OpenFileAndAppendDataTrue\":1}]" : "[{\"OpenFileAndAppendDataTrue\":0}]";
    request.setOpt(new curlpp::options::PostFields(query)); 
    // request.setOpt(new curlpp::options::WriteStream(&std::cout));
    // request.perform();
    ASSERT_EQ(1, appendData);
}

TEST(CppFileHandlingProjectTest, OpenFileAndAppendDataFalse) {
    curlpp::Cleanup cleanup;
    curlpp::Easy request;
    request.setOpt(curlpp::options::Url(std::string("https://jsonplaceholder.typicode.com/posts")));
    std::list<std::string> header = {
        "Content-Type: application/json",
        "accept: application/json"
    };
    request.setOpt(new curlpp::options::HttpHeader(header));
    const string data = "\nextra data";
    const int appendData = isFilePresent("no_file.txt") ? openFileAndAppendData("no_file.txt", data) : 0;
    std::string query = appendData ? "[{\"OpenFileAndAppendDataFalse\":1}]" : "[{\"OpenFileAndAppendDataFalse\":0}]";
    request.setOpt(new curlpp::options::PostFields(query)); 
    // request.setOpt(new curlpp::options::WriteStream(&std::cout));
    // request.perform();
    ASSERT_EQ(0, appendData);
}
