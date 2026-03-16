#include "middleware/UdsDiag.h"
#include <iostream>
#include <iomanip>

namespace bsw { namespace middleware {

bool UdsDiag::init() {
    initialized_ = true;
    currentSession_ = DiagSession::DEFAULT;
    std::cout << "[DIAG] UDS diagnostics initialized" << std::endl;
    return true;
}

bool UdsDiag::startSession(DiagSession session) {
    if (!initialized_) return false;
    currentSession_ = session;
    const char* name = "UNKNOWN";
    switch (session) {
        case DiagSession::DEFAULT:     name = "DEFAULT"; break;
        case DiagSession::PROGRAMMING: name = "PROGRAMMING"; break;
        case DiagSession::EXTENDED:    name = "EXTENDED"; break;
    }
    std::cout << "[DIAG] Session changed to: " << name << std::endl;
    return true;
}

bool UdsDiag::readDataById(uint16_t did, std::vector<uint8_t>& outBuffer) {
    if (!initialized_) return false;

    // Simulate DID responses
    outBuffer.clear();
    switch (did) {
        case 0xF190: // VIN
            outBuffer = {0x56, 0x45, 0x48, 0x49, 0x43, 0x4C, 0x45, 0x30, 0x30, 0x31};
            break;
        case 0xF101: // ECU Serial Number
            outBuffer = {0x45, 0x43, 0x55, 0x2D, 0x30, 0x30, 0x31};
            break;
        default:
            return false;
    }

    std::cout << "[DIAG] DID 0x" << std::hex << std::setfill('0') << std::setw(4) << did
              << " read: ";
    for (auto b : outBuffer) {
        std::cout << std::hex << std::setfill('0') << std::setw(2) << static_cast<int>(b) << " ";
    }
    std::cout << std::dec << std::endl;
    return true;
}

DiagSession UdsDiag::getCurrentSession() const {
    return currentSession_;
}

}} // namespace bsw::middleware
