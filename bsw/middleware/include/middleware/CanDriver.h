#pragma once
#include "middleware/CanMessage.h"

namespace bsw { namespace middleware {

class CanDriver {
public:
    bool init(uint32_t baudRate);
    bool send(const CanMessage& msg);
    bool receive(CanMessage& outMsg);

private:
    bool initialized_ = false;
    uint32_t baudRate_ = 0;
    CanMessage rxBuffer_;
    bool hasRxData_ = false;
};

}} // namespace bsw::middleware
