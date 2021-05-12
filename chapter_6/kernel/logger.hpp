#pragma once

enum class LogLevel {
    Error = 3,
    Warn = 4,
    Info = 6,
    Debug = 7
};

// set logging level
void SetLogLevel(const LogLevel level);

// output log based on loglevel
int Log(const LogLevel level, const char* format, ...);