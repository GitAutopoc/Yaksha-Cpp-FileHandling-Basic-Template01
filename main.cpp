#include <iostream>
#include <string>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include "tests/test_cases.cpp"
#include <gtest/gtest.h>
#include <fstream>
#include <sstream>

using namespace curlpp::options;
using namespace std;

int main(int argc, char **argv) {
    // write your code here for menu driven program
    // feel free to add files as per requirement
    
    // mandatory code to run test cases, please do not remove it
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
