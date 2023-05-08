using namespace std;

class TestResults {

	private:
        string testCaseResults;
	    string customData;

	public:
        string getTestCaseResults() {
            return testCaseResults;
        }

        void setTestCaseResults(string testCaseResults) {
            this->testCaseResults = testCaseResults;
        }

        string getCustomData() {
            return customData;
        }

        void setCustomData(string customData) {
            this->customData = customData;
        }

};