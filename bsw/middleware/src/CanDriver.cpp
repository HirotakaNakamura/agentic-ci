#include "middleware/CanDriver.h"
#include <iostream>
#include <iomanip>

namespace bsw { namespace middleware {

bool CanDriver::init(uint32_t baudRate) {
    baudRate_ = baudRate;
    initialized_ = true;
    std::cout << "[CAN ] CAN bus initialized (baudrate=" << baudRate << ")" << std::endl;
    return true;
}

bool CanDriver::send(const CanMessage& msg) {
    if (!initialized_) return false;

    std::cout << "[CAN ] TX [0x" << std::hex << std::setfill('0') << std::setw(3) << msg.id << "] "
              << "DLC=" << std::dec << static_cast<int>(msg.dlc) << " Data:";
    for (uint8_t i = 0; i < msg.dlc && i < 8; ++i) {
        std::cout << " " << std::hex << std::setfill('0') << std::setw(2)
                  << static_cast<int>(msg.data[i]);
    }
    std::cout << std::dec << std::endl;
    return true;
}

bool CanDriver::receive(CanMessage& outMsg) {
    if (!initialized_ || !hasRxData_) return false;
    outMsg = rxBuffer_;
    hasRxData_ = false;
    std::cout << "[CAN ] RX [0x" << std::hex << std::setfill('0') << std::setw(3) << outMsg.id << "] "
              << "DLC=" << std::dec << static_cast<int>(outMsg.dlc) << " Data:";
    for (uint8_t i = 0; i < outMsg.dlc && i < 8; ++i) {
        std::cout << " " << std::hex << std::setfill('0') << std::setw(2)
                  << static_cast<int>(outMsg.data[i]);
    }
    std::cout << std::dec << std::endl;
    return true;
}

}} // namespace bsw::middleware
