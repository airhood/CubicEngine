#include "Logger.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <ctime>
#include <iomanip>

using namespace CubicEngine;

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

    thread_local char buffer[20]; // "YYYY-MM-DD HH:MM:SS" → 20자
    struct tm local_time;

#if defined(_WIN32) || defined(_WIN64)
    localtime_s(&local_time, &time);
#else
    localtime_r(&time, &local_time);
#endif

    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &local_time);
    return std::string(buffer);
}

void Logger::Init() {
#ifdef _DEBUG
    std::cout << "Logger initializing." << std::endl;
#endif
    RotateLogFile();
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
    LogEntry entry(level, std::string(formatted), source);

    if (log_console && level >= log_level) {
        std::cout << entry.message;
    }

    {
        std::lock_guard<std::mutex> guard(logMutex);
        logs.push_back(std::move(entry));
    }

    SaveToFile(logs.back());
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

    std::ofstream file(logFileName + ".log", std::ios::app);
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

void Logger::RotateLogFile() {
    auto file_exists = [](const std::string& filename) -> bool {
        struct stat buffer;
        return (stat(filename.c_str(), &buffer) == 0);
    };

    bool file_state = file_exists("log.meta");

    std::fstream meta_file("log.meta", std::ios::in | std::ios::out | std::ios::app);

    if (!file_state) {
        meta_file << "0";
        meta_file.close();
        return;
    }

    std::string file_index_s;
    std::getline(meta_file, file_index_s);

    int file_index = std::stoi(file_index_s);

    if (!file_exists(logFileName + ".log")) {
        meta_file.close();
        return;
    }

    std::ifstream file(logFileName + ".log", std::ios::ate | std::ios::binary);
    file.close();
    std::string rotatedLogFile = logFileName + "-" + std::to_string(file_index + 1) + ".log";
    std::rename((logFileName + ".log").c_str(), rotatedLogFile.c_str());
    
    meta_file << std::to_string(file_index + 1);
    meta_file.close();

    //if (file.tellg() > 1024 * 1024) {  // 1MB 크기 제한
    //    file.close();
    //    std::string rotatedLogFile = logFileName + "-old" + ".log";
    //    std::rename((logFileName + ".log").c_str(), rotatedLogFile.c_str());
    //}
}
