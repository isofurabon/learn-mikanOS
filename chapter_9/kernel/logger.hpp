#pragma once

enum LogLevel {
    kError = 0,
    kWarn,
    kInfo,
    kDebug,
    LastOfLogLevel 
};

// set logging level
void SetLogLevel(const LogLevel level);

// output log based on loglevel
int Log(const LogLevel level, const char* format, ...);