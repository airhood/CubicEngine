#include "Logger.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <filesystem>

using namespace CubicEngine;

namespace {
    std::once_flag log_dir_flag;
}

bool Logger::log_console = false;
LogLevel Logger::log_level = LogLevel::INFO;

LogEntry::LogEntry(LogLevel level, const std::string& message, const std::string& source)
    : level(level), message(message), source(source), timestamp(Logger::CurrentTime()) {}

std::vector<LogEntry> Logger::logs;
std::mutex Logger::logMutex;
std::string Logger::logFileName = "runtime";

std::string Logger::CurrentTime() {
    using namespace std::chrono;
    auto now = system_clock::now();
    auto time = system_clock::to_time_t(now);

    thread_local char buffer[20]; // "YYYY-MM-DD HH:MM:SS" ¡æ 20ÀÚ
    struct tm local_time;

#if defined(_WIN32) || defined(_WIN64)
    localtime_s(&local_time, &time);
#else
    localtime_r(&time, &local_time);
#endif

    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &local_time);
    return std::string(buffer);
}

std::string Logger::CurrentTimeForFilename() {
    using namespace std::chrono;
    auto now = system_clock::now();
    auto time = system_clock::to_time_t(now);

    thread_local char buffer[20]; // "YYYY-MM-DD HH-MM-SS"
    struct tm local_time;

#if defined(_WIN32) || defined(_WIN64)
    localtime_s(&local_time, &time);
#else
    localtime_r(&time, &local_time);
#endif

    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d_%H-%M-%S", &local_time);
    return std::string(buffer);
}

void Logger::Init() {
#ifdef _DEBUG
    std::cout << "Logger initializing." << std::endl;
#endif

    static bool created = []() {
        return std::filesystem::create_directories("log");
    }();

    logFileName.append("_").append(CurrentTimeForFilename());
}

void Logger::Log(LogLevel level, const std::string& message, const std::string& source) {
    thread_local char buffer[1024];

    auto time = CurrentTime();
    auto it = fmt::format_to(buffer, "[{}] [{}] {} ({})\n",
        time,
        LogLevelToString(level),
        message,
        source);

    std::string_view formatted(buffer, it - buffer);
    LogEntry entry(level, message, source);
    if (level >= log_level) {
        if (log_console) {
            std::cout << formatted;
        }

        {
            std::lock_guard<std::mutex> guard(logMutex);
            logs.push_back(std::move(entry));
        }

        SaveToFile(logs.back());
    }
}

std::vector<LogEntry> Logger::Search(LogLevel level) {
    std::vector<LogEntry> results;
    {
        std::lock_guard<std::mutex> guard(logMutex);
        for (const auto& log : logs) {
            if (log.level == level) {
                results.push_back(log);
            }
        }
    }
    return results;
}

void Logger::PrintLogs(LogLevel level) {
    {
        std::lock_guard<std::mutex> guard(logMutex);
        for (const auto& log : Search(level)) {
            std::cout << "[" << log.timestamp << "] [" << LogLevelToString(log.level)
                << "] " << log.message << " (" << log.source << ")" << std::endl;
        }
    }
}

void Logger::ClearLogs() {
    {
        std::lock_guard<std::mutex> guard(logMutex);
        logs.clear();
    }
}

void Logger::LogConsole(bool state) {
    log_console = state;
}

void Logger::SetLogLevel(LogLevel level) {
    log_level = level;
}

void Logger::SaveToFile(const LogEntry& entry) {
    thread_local char buffer[1024];
    auto end = fmt::format_to(buffer, "[{}] [{}] {} ({})\n",
        entry.timestamp,
        LogLevelToString(entry.level),
        entry.message,
        entry.source);

    std::string formatted(buffer, end - buffer);

    std::ofstream file("log/" + logFileName + ".log", std::ios::app);
    if (file) {
        file << formatted;
    }
    std::string a = fmt::format("a");
}

std::string Logger::LogLevelToString(LogLevel level) {
    switch (level) {
        case LogLevel::TRACE:   return "TRACE";
        case LogLevel::DEBUG:   return "DEBUG";
        case LogLevel::INFO:    return "INFO";
        case LogLevel::WARNING: return "WARNING";
        case LogLevel::ERROR:   return "ERROR";
        case LogLevel::FATAL:   return "FATAL";
        default:                return "UNKNOWN";
    }
}