#include <sstream>
#include <string>
#include "test_runner.h"
using namespace std;

class Logger {
public:
    explicit Logger(ostream& output_stream) : os(output_stream) {}

    void SetLogLine(bool value) { log_line = value; }
    void SetLogFile(bool value) { log_file = value; }
    void SetFile(const string& file) { file_name = file; }
    void SetLine(int line) { line_number = line; }
    void Log(const string& message);

private:
    ostream& os;
    bool log_line = false;
    bool log_file = false;
    string file_name;
    int line_number = 0;
};

void Logger::Log(const string& message) {
    if (log_file && log_line) {
        os << file_name << ":" << line_number << " " << message << endl;
    }
    else if (log_file) {
        os << file_name << " " << message << endl;
    }
    else if (log_line) {
        os << "Line " << line_number << " " << message << endl;
    }
    else {
        os << message << endl;
    }
}

#define LOG(logger, message) \
do { \
    (logger).SetLine(__LINE__); \
    (logger).SetFile(__FILE__); \
    (logger).SetLogLine(true); \
    (logger).SetLogFile(true); \
    (logger).Log(message); \
} while(0)

void TestLog() {
    ostringstream logs;
    Logger l(logs);
    LOG(l, "hello");

    l.SetLogFile(true);
    LOG(l, "hello");

    l.SetLogLine(true);
    LOG(l, "hello");

    l.SetLogFile(false);
    LOG(l, "hello");

    string result = logs.str();
    ASSERT(result.find("hello") != string::npos);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestLog);
}
