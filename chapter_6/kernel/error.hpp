#pragma once

#include <array>

class Error {
public:
    enum Code {
        kSuccess,
        kFull,
        kEmpty,
        LastOfCode,
    };

    Error(const Code code): m_code{code} {}

    operator bool() const {
        return this->m_code != Success;
    }

    const char* Name() const {
        return code_names[static_cast<size_t>(this->m_code)];
    }

private:
    static constexpr std::array<const char*, static_cast<size_t>(LastOfCode)> code_names = {
        "Success",
        "Full",
        "Empty",
    };

    Code m_code;
};