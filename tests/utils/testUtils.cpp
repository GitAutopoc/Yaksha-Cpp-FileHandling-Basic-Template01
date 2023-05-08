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
        const string URL = "https://yaksha-stage-sbfn.azurewebsites.net/api/TestCaseResultsEnqueue?code=AjU0mofZlYs9oYbZnJpVwJWRY1dRKkDyS3QDY8aJAvrcjJvgBAXVDg==";
        const string GUID = "6ed39465-d6d3-4ec4-b27d-1dcb870b2992";
        string customData;
	
		string readCustomFileData(string filePath) {
			ifstream inputFile(filePath);
			string line;
			string name;
			try {
				while (inputFile >> name) {
					cout<<name;
					line += name;
				}
			} catch(...) {
				cout<<"There was an error !\n";
			}
			return line;
		}

		void yakshaAssert(string testName, bool result, string testType) {
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
			request.setOpt(curlpp::options::Url(std::string("https://yaksha-prod-sbfn.azurewebsites.net/api/YakshaMFAEnqueue?code=jSTWTxtQ8kZgQ5FC0oLgoSgZG7UoU9Asnmxgp6hLLvYId/GW9ccoLw==")));
			std::list<std::string> header = {
				"Content-Type: application/json",
				"accept: application/json"
			}; 
			request.setOpt(new curlpp::options::HttpHeader(header));			
			std::string query = finalResult;
			request.setOpt(new curlpp::options::PostFields(query)); 
			request.setOpt(new curlpp::options::WriteStream(&std::cout));
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