#pragma once
#include <cstdint>
#include <vector>

namespace bsw { namespace middleware {

enum class DiagSession : uint8_t {
    DEFAULT      = 0x01,
    PROGRAMMING  = 0x02,
    EXTENDED     = 0x03
};

class UdsDiag {
public:
    bool init();
    bool startSession(DiagSession session);
    bool readDataById(uint16_t did, std::vector<uint8_t>& outBuffer);
    DiagSession getCurrentSession() const;

private:
    DiagSession currentSession_ = DiagSession::DEFAULT;
    bool initialized_ = false;
};

}} // namespace bsw::middleware
