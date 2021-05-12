#pragma once

enum class LogLevel {
    Error = 0,
    Warn,
    Info,
    Debug,
    LastOfLogLevel 
};

// set logging level
void SetLogLevel(const LogLevel level);

// output log based on loglevel
int Log(const LogLevel level, const char* format, ...);