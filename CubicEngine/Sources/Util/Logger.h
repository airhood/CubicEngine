#pragma once

#include <string>
#include <vector>
#include <mutex>

namespace CubicEngine {

    enum class LogLevel {
        DEBUG,
        INFO,
        WARNING,
        ERROR,
        FATAL
    };

    class LogEntry {
    public:
        LogEntry(LogLevel lvl, const std::string& msg, const std::string& src);

        LogLevel level;
        std::string message;
        std::string timestamp;
        std::string source;
    };

    class Logger {
    public:
        static std::string currentTime();

        static void log(LogLevel level, const std::string& message, const std::string& source = "Unknown");
        static std::vector<LogEntry> search(LogLevel level);
        static void printLogs(LogLevel level);
        static void clearLogs();
        static void setLogFile(const std::string& filename);

    private:
        static std::vector<LogEntry> logs;
        static std::mutex logMutex;
        static std::string logFile;

        static void saveToFile(const LogEntry& entry);
        static std::string logLevelToString(LogLevel level);
        static void rotateLogFile();
    };

}
