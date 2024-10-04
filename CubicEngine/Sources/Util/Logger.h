#pragma once

#include <string>
#include <vector>

namespace CubicEngine {
    enum class LogLevel {
        ERROR,
        WARNING,
        MESSAGE
    };

    class LogEntry {
    public:
        LogLevel level;
        std::string message;

        LogEntry(LogLevel lvl, const std::string& msg) : level(lvl), message(msg) {}
    };

    class Logger {
    public:
        static void log(LogLevel level, const std::string& message);
        static std::vector<LogEntry> search(LogLevel level);
        static void printLogs(LogLevel level);

    private:
        static std::vector<LogEntry> logs;
        static void saveToFile(const LogEntry& entry);
        static std::string logLevelToString(LogLevel level);
    };

}