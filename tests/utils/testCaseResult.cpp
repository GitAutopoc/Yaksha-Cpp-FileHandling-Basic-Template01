using namespace std;

class TestCaseResult {

	private:
        string methodName;
        string methodType;
        int actualScore;
        int earnedScore;
        string status;
        bool isMandatory;
        string erroMessage;

	public:
        TestCaseResult(string methodName, string methodType, int actualScore, int earnedScore, string status,
                bool isMandatory, string erroMessage) {
            // super();
            this->methodName = methodName;
            this->methodType = methodType;
            this->actualScore = actualScore;
            this->earnedScore = earnedScore;
            this->status = status;
            this->isMandatory = isMandatory;
            this->erroMessage = erroMessage;
        }

        string getMethodName() {
            return methodName;
        }

        void setMethodName(string methodName) {
            this->methodName = methodName;
        }

        string getMethodType() {
            return methodType;
        }

        void setMethodType(string methodType) {
            this->methodType = methodType;
        }

        int getActualScore() {
            return actualScore;
        }

        void setActualScore(int actualScore) {
            this->actualScore = actualScore;
        }

        int getEarnedScore() {
            return earnedScore;
        }

        void setEarnedScore(int earnedScore) {
            this->earnedScore = earnedScore;
        }

        string getStatus() {
            return status;
        }

        void setStatus(string status) {
            this->status = status;
        }

        bool getIsMandatory() {
            return isMandatory;
        }

        void setIsMandatory(bool isMandatory) {
            this->isMandatory = isMandatory;
        }

        string getErroMessage() {
            return erroMessage;
        }

        void setErroMessage(string erroMessage) {
            this->erroMessage = erroMessage;
        }
};