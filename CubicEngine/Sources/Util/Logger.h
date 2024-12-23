#pragma once

#include <string>
#include <vector>
#include <mutex>

namespace CubicEngine {

    enum class LogLevel {
        TRACE,
        DEBUG,
        INFO,
        WARNING,
        ERROR,
        FATAL
    };

    class LogEntry {
    public:
        LogEntry(LogLevel level, const std::string& message, const std::string& source);

        LogLevel level;
        std::string message;
        std::string timestamp;
        std::string source;
    };

    class Logger {
    public:
        static void Init();

        static std::string CurrentTime();

        static void Log(LogLevel level, const std::string& message, const std::string& source = "Unknown");
        static std::vector<LogEntry> Search(LogLevel level);
        static void PrintLogs(LogLevel level);
        static void ClearLogs();

    private:
        static std::vector<LogEntry> logs;
        static std::mutex logMutex;
        static std::string logFileName;

        static void SaveToFile(const LogEntry& entry);
        static std::string LogLevelToString(LogLevel level);
        static void RotateLogFile();
    };

}
