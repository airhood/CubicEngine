#pragma once

#include <string>
#include <vector>

namespace CubicEngine {
    enum class LogLevel {
        ERROR,
        WARNING,
        MESSAGE
    };

    struct LogEntry {
        LogLevel level;
        std::string message;

        LogEntry(LogLevel lvl, const std::string& msg);
    };

    class Logger {
    public:
        void log(LogLevel level, const std::string& message);
        std::vector<LogEntry> search(LogLevel level) const;
        void printLogs(LogLevel level) const;

    private:
        std::vector<LogEntry> logs;
        void saveToFile(const LogEntry& entry);
        std::string logLevelToString(LogLevel level) const;
    };

}