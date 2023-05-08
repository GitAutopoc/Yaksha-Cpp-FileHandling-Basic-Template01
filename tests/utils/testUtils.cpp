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
			// try {
				string testTypeB = "functional";
				// if (file.getName().contains("boundary"))
				// 	testType = "boundary";
				// if (file.getName().contains("exception"))
				// 	testType = "exception";
				// map["one"] = 1;
				// TestCaseResult testCaseResultObj(testName, testType, 1, resultScore, resultStatus, true, "");
				testCaseResults.insert(std::make_pair(GUID, TestCaseResult(testName, testType, 1, resultScore, resultStatus, true, "")));
				// cout<<testCaseResults.size();
				// map<std::string, TestCaseResult>::iterator it;
				// for (it = testCaseResults.begin(); it != testCaseResults.end(); it++) {
				// 	std::cout << it->first    // string (key)
				// 			<< ':'
				// 			<< it->second.getMethodName()   // string's value 
				// 			<< std::endl;
				// }

			// } catch (...) {
			// // TODO Auto-generated catch block
			// 	cout<<"error in assertion";
			// }
			testResults.setTestCaseResults(testCaseResultAsJsonString(GUID, TestCaseResult(testName, testType, 1, resultScore, resultStatus, true, "")));
			testResults.setCustomData(customData);
			string finalResult = testResultsAsJsonString(testResults);
			
			curlpp::Cleanup cleanup;
			curlpp::Easy request;
			request.setOpt(curlpp::options::Url(std::string("https://jsonplaceholder.typicode.com/posts")));
			std::list<std::string> header = {
				"Content-Type: application/json",
				"accept: application/json"
			}; 
			request.setOpt(new curlpp::options::HttpHeader(header));
			
			std::string query = finalResult;// filePresent ? "[{\"FilePresentTrue\":1}]" : "[{\"FilePresentTrue\":0}]";
			request.setOpt(new curlpp::options::PostFields(query)); 
			request.setOpt(new curlpp::options::WriteStream(&std::cout));
			request.perform();
			
			// cout<<finalResult;
			// System.out.println(finalResult);
			// HttpClient client = HttpClient.newHttpClient();
		}

    /*
	public static void yakshaAssert(String testName, Object result, File file) throws IOException {
		TestResults testResults = new TestResults();
		Map<String, TestCaseResultDto> testCaseResults = new HashMap<String, TestCaseResultDto>();

		customData = readData("../custom.ih");
		String resultStatus = "Failed";
		int resultScore = 0;
		if (result.toString().equals("true")) {
			resultScore = 1;
			resultStatus = "Passed";
		}
		try {
			String testType = "functional";
			if (file.getName().contains("boundary"))
				testType = "boundary";
			if (file.getName().contains("exception"))
				testType = "exception";
			testCaseResults.put(GUID,
					new TestCaseResultDto(testName, testType, 1, resultScore, resultStatus, true, ""));
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			System.out.println(e.getMessage());
		}
		testResults.setTestCaseResults(asJsonString(testCaseResults));
		testResults.setCustomData(customData);

		String finalResult = asJsonString(testResults);
		System.out.println(finalResult);
//		HttpClient client = HttpClient.newHttpClient();
//	        HttpRequest request = HttpRequest.newBuilder()
//	                .uri(URI.create(URL))
//	                .POST(HttpRequest.BodyPublishers.ofString(finalResult, Charset.defaultCharset()))
//	                .build();
//
//	        try {
//				HttpResponse<String> response = client.send(request,
//				        HttpResponse.BodyHandlers.ofString());
//			} catch (IOException | InterruptedException e) {
//				// TODO Auto-generated catch block
//				e.printStackTrace();
//				System.out.println(e);
//			}

		URL url = new URL(URL);
		HttpURLConnection conn = (HttpURLConnection) url.openConnection();
		conn.setDoOutput(true);
		conn.setRequestMethod("POST");
		conn.setRequestProperty("Content-Type", "application/json");

		String input = asJsonString(testResults);

		OutputStream os = conn.getOutputStream();
		os.write(input.getBytes());
		os.flush();

		if (conn.getResponseCode() != HttpURLConnection.HTTP_CREATED) {
			throw new RuntimeException("Failed : HTTP error code : " + conn.getResponseCode());
		}

		BufferedReader br = new BufferedReader(new InputStreamReader((conn.getInputStream())));

		String output;
		System.out.println("Output from Server .... \n");
		while ((output = br.readLine()) != null) {
			System.out.println(output);
		}

		total++;
		String[] r = testName.split("(?=\\p{Upper})");
		System.out.print("\n" + BLUE_BOLD_BRIGHT + "=>");
		// testResult = testResult + "\n" + BLUE_BOLD_BRIGHT + "=>";

		System.out.print(YELLOW_BOLD_BRIGHT + "Test For : ");
		// testResult = testResult + YELLOW_BOLD_BRIGHT + "Test For : ";

		for (int i = 1; i < r.length; i++) {
			System.out.print(YELLOW_BOLD_BRIGHT + r[i] + " ");
			// testResult = testResult + YELLOW_BOLD_BRIGHT + r[i] + " ";
		}
		System.out.print(" : ");
		// testResult = testResult + " : ";
		if (result.toString().equals("true")) {
			System.out.println(GREEN_BOLD_BRIGHT + "PASSED" + TEXT_RESET);
			// testResult = testResult + GREEN_BOLD_BRIGHT + "PASSED" + TEXT_RESET;
			passed++;
		} else {
			System.out.println(RED_BOLD_BRIGHT + "FAILED" + TEXT_RESET);
			// testResult = testResult + RED_BOLD_BRIGHT + "FAILED" + TEXT_RESET;
			failed++;
		}
//			FileWriter writer = new FileWriter(file,true);
//			writer.append("\n" + testName + "=" + result);
//			writer.flush();
//			writer.close();
		// createXML(testName, file);

	}
    */

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
		// return j.dump(4);
		return j.dump();
	}

	string testResultsAsJsonString(TestResults testResults) {
		json j = {
			{"testCaseResults", testResults.getTestCaseResults()},
			{"customData", testResults.getCustomData()}
		};
		return j.dump(4);
		// return j.dump();
	}
};