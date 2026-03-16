#pragma once
#include <cstdint>
#include <array>

namespace bsw { namespace middleware {

using CanId = uint32_t;

struct CanMessage {
    CanId id;
    uint8_t dlc;
    std::array<uint8_t, 8> data;
};

}} // namespace bsw::middleware
