#pragma once
#include <cstdint>

namespace bsw { namespace os {

using TaskId = uint16_t;

enum class TaskState : uint8_t {
    SUSPENDED,
    READY,
    RUNNING
};

enum class Priority : uint8_t {
    LOW      = 0,
    MEDIUM   = 1,
    HIGH     = 2,
    CRITICAL = 3
};

using TickType = uint32_t;

}} // namespace bsw::os
