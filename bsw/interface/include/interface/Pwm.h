#pragma once
#include "interface/HalTypes.h"

namespace bsw { namespace interface {

class Pwm {
public:
    bool init(PwmChannel channel, uint32_t frequencyHz);
    bool setDutyCycle(PwmChannel channel, float dutyCyclePercent);
};

}} // namespace bsw::interface
