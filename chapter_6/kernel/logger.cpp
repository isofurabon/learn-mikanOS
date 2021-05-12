#include "logger.hpp"

#include <cstddef>
#include <cstdio>
#include <array>

#include "console.hpp"

namespace {
    LogLevel log_level = LogLevel::Warn;
}

extern Console* console;

static constexpr std::array<const char*, static_cast<size_t>(LogLevel::LastOfLogLevel)> logLevelsName = {
    "Error",
    "Warn",
    "Info",
    "Debug"
};
static const char* GetLogLevel(const LogLevel level) {
    return logLevelsName[static_cast<size_t>(level)];
}

void SetLogLevel(const LogLevel level) {
    log_level = level;
}

int Log(const LogLevel level, const char* format, ...) {
    if (level > log_level){
        return 0;
    }

    va_list ap;
    int result = 0;
    char s[1024];
    
    va_start(ap, format);
    result = vsprintf(s, format, ap);
    va_end(ap);

    console->PutString(GetLogLevel(level));
    console->PutString(s);
    return result;
}