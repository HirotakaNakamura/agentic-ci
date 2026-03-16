#include "interface/Pwm.h"
#include <iostream>
#include <iomanip>

namespace bsw { namespace interface {

bool Pwm::init(PwmChannel channel, uint32_t frequencyHz) {
    std::cout << "[HAL ] PWM channel " << static_cast<int>(channel)
              << " initialized (freq=" << frequencyHz << "Hz)" << std::endl;
    return true;
}

bool Pwm::setDutyCycle(PwmChannel channel, float dutyCyclePercent) {
    std::cout << "[HAL ] PWM ch" << static_cast<int>(channel)
              << " duty: " << std::fixed << std::setprecision(1)
              << dutyCyclePercent << "%" << std::endl;
    return true;
}

}} // namespace bsw::interface
