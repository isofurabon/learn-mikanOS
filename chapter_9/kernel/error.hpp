#pragma once

#include <cstdio>
#include <array>

class Error {
public:
    enum Code {
        kSuccess,
        kFull,
        kEmpty,
        kNoEnoughMemory,
        kIndexOutOfRange,
        kHostControllerNotHalted,
        kInvalidSlotID,
        kPortNotConnected,
        kInvalidEndpointNumber,
        kTransferRingNotSet,
        kAlreadyAllocated,
        kNotImplemented,
        kInvalidDescriptor,
        kBufferTooSmall,
        kUnknownDevice,
        kNoCorrespondingSetupStage,
        kTransferFailed,
        kInvalidPhase,
        kUnknownXHCISpeedID,
        kNoWaiter,
        kNoPCIMSI,
        kUnknownPixelFormat,
        kLastOfCode,
    };

private:
    static constexpr std::array m_code_names{
        "kSuccess",
        "kFull",
        "kEmpty",
        "kNoEnoughMemory",
        "kIndexOutOfRange",
        "kHostControllerNotHalted",
        "kInvalidSlotID",
        "kPortNotConnected",
        "kInvalidEndpointNumber",
        "kTransferRingNotSet",
        "kAlreadyAllocated",
        "kNotImplemented",
        "kInvalidDescriptor",
        "kBufferTooSmall",
        "kUnknownDevice",
        "kNoCorrespondingSetupStage",
        "kTransferFailed",
        "kInvalidPhase",
        "kUnknownXHCISpeedID",
        "kNoWaiter",
        "kNoPCIMSI",
        "kUnknownPixelFormat",
    };
    static_assert(Error::Code::kLastOfCode == m_code_names.size());;

public:
    Error(Code code, const char* file, int line): m_code{code}, m_file{file}, m_line{line} {}

    Code Cause() const {
        return this->m_code;
    }

    operator bool() const {
        return this->m_code != kSuccess;
    }

    const char* File() const {
        return this->m_file;
    }

    const char* Name() const {
        return m_code_names[static_cast<size_t>(this->m_code)];
    }

    int Line() const {
        return this->m_line;
    }

    private:
        Code m_code;
        int m_line;
        const char* m_file;
};

#define MAKE_ERROR(code) Error((code), __FILE__, __LINE__)

template <typename T>
struct WithError {
    T value;
    Error error;
};