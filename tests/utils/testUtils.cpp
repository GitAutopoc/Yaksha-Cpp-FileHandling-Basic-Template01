#include <fstream>
#include <iostream>
#include <map>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include "testResults.cpp"
#include "testCaseResult.cpp"

using json = nlohmann::json;
using namespace curlpp::options;
using namespace std;

class TestUtils {

	public:
        string testResult;
        const string URL = "https://yaksha-stage-sbfn-s2-vm.azurewebsites.net/api/YakshaMFAEnqueue?code=MLo1s4eRhiP_Z2EJr3Y38EDFPQ5NUfOu4snUcWTC5tU3AzFuQZCG2Q==";
        const string GUID = "778711fe-6b20-4f29-b4f2-3452dd8dc207";
        string customData;
	
		string readCustomFileData(string filePath) {
			ifstream inputFile(filePath);
			string line;
			string name;
			try {
				while (inputFile >> name) {
					line += name;
				}
			} catch(...) {
				cout<<"There was an error !\n";
			}
			return line;
		}

		void yakshaAssert(string testName, int result, string testType) {
			TestResults testResults;
			map<std::string, TestCaseResult> testCaseResults;
			customData = readCustomFileData("../custom.ih");
			string resultStatus = "Failed";
			int resultScore = 0;
			if (result) {
				resultScore = 1;
				resultStatus = "Passed";
			}
			string testTypeB = "functional";
			testCaseResults.insert(std::make_pair(GUID, TestCaseResult(testName, testType, 1, resultScore, resultStatus, true, "")));
			testResults.setTestCaseResults(testCaseResultAsJsonString(GUID, TestCaseResult(testName, testType, 1, resultScore, resultStatus, true, "")));
			testResults.setCustomData(customData);
			string finalResult = testResultsAsJsonString(testResults);
			curlpp::Cleanup cleanup;
			curlpp::Easy request;
			request.setOpt(curlpp::options::Url(std::string("https://yaksha-stage-sbfn-s2-vm.azurewebsites.net/api/YakshaMFAEnqueue?code=MLo1s4eRhiP_Z2EJr3Y38EDFPQ5NUfOu4snUcWTC5tU3AzFuQZCG2Q==")));
			std::list<std::string> header = {
				"Content-Type: application/json",
				"accept: application/json"
			}; 
			request.setOpt(new curlpp::options::HttpHeader(header));			
			std::string query = finalResult;
			request.setOpt(new curlpp::options::PostFields(query)); 
			// request.setOpt(new curlpp::options::WriteStream(&std::cout));
			request.perform();
		}

		string testCaseResultAsJsonString(string GUID, TestCaseResult testCaseResult) {
			json j = {
				{GUID, {
					{"methodName", testCaseResult.getMethodName()},
					{"methodType", testCaseResult.getMethodType()},
					{"actualScore", testCaseResult.getActualScore()},
					{"earnedScore", testCaseResult.getEarnedScore()},
					{"status", testCaseResult.getStatus()},
					{"isMandatory", testCaseResult.getIsMandatory()},
					{"errorMessage", testCaseResult.getErroMessage()}
				}},
			};
			return j.dump();
		}

		string testResultsAsJsonString(TestResults testResults) {
			json j = {
				{"testCaseResults", testResults.getTestCaseResults()},
				{"customData", testResults.getCustomData()}
			};
			return j.dump();
		}
};
