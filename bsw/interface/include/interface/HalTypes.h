#pragma once
#include <cstdint>

namespace bsw { namespace interface {

using PinId = uint8_t;
using AdcChannel = uint8_t;
using PwmChannel = uint8_t;

enum class PinDirection : uint8_t {
    INPUT,
    OUTPUT
};

enum class PinLevel : uint8_t {
    LOW  = 0,
    HIGH = 1
};

}} // namespace bsw::interface
