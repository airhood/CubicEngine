#include "Logger.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <ctime>
#include <iomanip>

using namespace CubicEngine;

LogEntry::LogEntry(LogLevel lvl, const std::string& msg, const std::string& src)
    : level(lvl), message(msg), source(src), timestamp(Logger::currentTime()) {}

std::vector<LogEntry> Logger::logs;
std::mutex Logger::logMutex;
std::string Logger::logFile = "log.txt";

std::string Logger::currentTime() {
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

void Logger::log(LogLevel level, const std::string& message, const std::string& source) {
    LogEntry entry(level, message, source);
    {
        std::lock_guard<std::mutex> guard(logMutex);
        logs.push_back(entry);
    }
    saveToFile(entry);
}

std::vector<LogEntry> Logger::search(LogLevel level) {
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

void Logger::printLogs(LogLevel level) {
    {
        std::lock_guard<std::mutex> guard(logMutex);
        for (const auto& log : search(level)) {
            std::cout << "[" << log.timestamp << "] [" << logLevelToString(log.level)
                << "] [" << log.source << "] " << log.message << std::endl;
        }
    }
}

void Logger::saveToFile(const LogEntry& entry) {
    rotateLogFile();  // 로그 파일 회전 확인
    std::ofstream file(logFile, std::ios::app);
    if (file) {
        file << "[" << entry.timestamp << "] [" << logLevelToString(entry.level)
            << "] [" << entry.source << "] " << entry.message << std::endl;
    }
}

std::string Logger::logLevelToString(LogLevel level) {
    switch (level) {
        case LogLevel::DEBUG:  return "DEBUG";
        case LogLevel::INFO:   return "INFO";
        case LogLevel::WARNING: return "WARNING";
        case LogLevel::ERROR:  return "ERROR";
        case LogLevel::FATAL:  return "FATAL";
        default:               return "UNKNOWN";
    }
}

void Logger::rotateLogFile() {
    std::ifstream file(logFile, std::ios::ate | std::ios::binary);
    if (file.tellg() > 1024 * 1024) {  // 1MB 크기 제한
        file.close();
        std::string rotatedLogFile = logFile + ".old";
        std::rename(logFile.c_str(), rotatedLogFile.c_str());
    }
}

// 로그 파일을 설정하는 메서드
void Logger::setLogFile(const std::string& filename) {
    logFile = filename;
}

// 로그 목록을 초기화하는 메서드
void Logger::clearLogs() {
    {
        std::lock_guard<std::mutex> guard(logMutex);
        logs.clear();
    }
}
