#include "Logger.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <ctime>
#include <iomanip>

using namespace CubicEngine;

LogEntry::LogEntry(LogLevel level, const std::string& message, const std::string& source)
    : level(level), message(message), source(source), timestamp(Logger::CurrentTime()) {}

std::vector<LogEntry> Logger::logs;
std::mutex Logger::logMutex;
std::string Logger::logFileName = "runtime";

std::string Logger::CurrentTime() {
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    std::ostringstream oss;

    struct tm local_time;
#if defined(_WIN32) || defined(_WIN64)
    localtime_s(&local_time, &time);  // Windows
#else
    localtime_r(&time, &local_time);  // POSIX (Mac, Linux)
#endif

        // Format the time as "YYYY-MM-DD HH:MM:SS"
    oss << std::put_time(&local_time, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

void Logger::Init() {
    RotateLogFile();
}

void Logger::Log(LogLevel level, const std::string& message, const std::string& source) {
    LogEntry entry(level, message, source);
    {
        std::lock_guard<std::mutex> guard(logMutex);
        logs.push_back(entry);
    }
    SaveToFile(entry);
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

void Logger::SaveToFile(const LogEntry& entry) {
    std::ofstream file(logFileName + ".log", std::ios::app);
    if (file) {
        file << "[" << entry.timestamp << "] [" << LogLevelToString(entry.level)
            << "] " << entry.message << " (" << entry.source << ")" << std::endl;
    }
}

std::string Logger::LogLevelToString(LogLevel level) {
    switch (level) {
        case LogLevel::TRACE: return "TRACE";
        case LogLevel::DEBUG:  return "DEBUG";
        case LogLevel::INFO:   return "INFO";
        case LogLevel::WARNING: return "WARNING";
        case LogLevel::ERROR:  return "ERROR";
        case LogLevel::FATAL:  return "FATAL";
        default:               return "UNKNOWN";
    }
}

void Logger::RotateLogFile() {
    auto file_exists = [](const std::string& filename) -> bool {
        struct stat buffer;
        return (stat(filename.c_str(), &buffer) == 0);
    };

    bool file_state = file_exists("log.meta");

    std::fstream meta_file("log.meta", std::ios::in, std::ios::out);

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

void Logger::ClearLogs() {
    {
        std::lock_guard<std::mutex> guard(logMutex);
        logs.clear();
    }
}
