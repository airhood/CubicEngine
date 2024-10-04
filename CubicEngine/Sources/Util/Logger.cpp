#include "Logger.h"
#include <iostream>
#include <fstream>

using namespace CubicEngine;

std::vector<LogEntry> Logger::logs;

void Logger::log(LogLevel level, const std::string& message) {
    LogEntry entry(level, message);
    logs.push_back(entry);
    saveToFile(entry);
}

std::vector<LogEntry> Logger::search(LogLevel level) {
    std::vector<LogEntry> results;
    for (const auto& log : logs) {
        if (log.level == level) {
            results.push_back(log);
        }
    }
    return results;
}

void Logger::printLogs(LogLevel level) {
    for (const auto& log : search(level)) {
        std::cout << "[" << logLevelToString(log.level) << "] " << log.message << std::endl;
    }
}

void Logger::saveToFile(const LogEntry& entry) {
    std::ofstream file("log.txt", std::ios::app);
    if (file) {
        file << "[" << logLevelToString(entry.level) << "] " << entry.message << std::endl;
    }
}

std::string Logger::logLevelToString(LogLevel level) {
    switch (level) {
        case LogLevel::ERROR:   return "ERROR";
        case LogLevel::WARNING: return "WARNING";
        case LogLevel::MESSAGE: return "MESSAGE";
        default:               return "UNKNOWN";
    }
}
