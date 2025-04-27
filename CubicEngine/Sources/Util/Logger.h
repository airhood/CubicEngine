#pragma once

#include <string>
#include <vector>
#include <mutex>
#include <fmt/format.h>
#include <fmt/core.h>
#include <new>

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
        static std::string CurrentTimeForFilename();

        static void Log(LogLevel level, const std::string& message, const std::string& source = "Unknown");
        static std::vector<LogEntry> Search(LogLevel level);
        static void PrintLogs(LogLevel level);
        static void ClearLogs();

        static void LogConsole(bool state);
        static void SetLogLevel(LogLevel level);

    private:
        static void* operator new(std::size_t size) {
            return ::operator new(size);
        }

        static void* operator new[](std::size_t size) {
            return ::operator new[](size);
        }

        static void operator delete(void* pointer) {
            ::operator delete(pointer);
        }

        static void operator delete[](void* pointer) {
            ::operator delete[](pointer);
        }

    private:
        static std::vector<LogEntry> logs;
        static std::mutex logMutex;
        static std::string logFileName;

        static void SaveToFile(const LogEntry& entry);
        static std::string LogLevelToString(LogLevel level);

        static bool log_console;
        static LogLevel log_level;

        Logger() = default;
        ~Logger() = default;
    };

}
