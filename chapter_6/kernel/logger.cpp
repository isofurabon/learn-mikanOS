#include "logger.hpp"

#include <cstddef>
#include <cstdio>

#include "console.hpp"

namespace {
    LogLevel log_level = LogLevel::Warn;
}

extern Console* console;

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

    console->PutString(s);
    return result;
}