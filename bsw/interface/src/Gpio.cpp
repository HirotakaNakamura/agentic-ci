#include "interface/Gpio.h"
#include <iostream>

namespace bsw { namespace interface {

bool Gpio::configurePin(PinId pin, PinDirection dir) {
    const char* dirStr = (dir == PinDirection::OUTPUT) ? "OUTPUT" : "INPUT";
    std::cout << "[HAL ] GPIO pin " << static_cast<int>(pin)
              << " configured as " << dirStr << std::endl;
    return true;
}

bool Gpio::writePin(PinId pin, PinLevel level) {
    const char* lvlStr = (level == PinLevel::HIGH) ? "HIGH" : "LOW";
    std::cout << "[HAL ] GPIO pin " << static_cast<int>(pin)
              << " -> " << lvlStr << std::endl;
    return true;
}

PinLevel Gpio::readPin(PinId pin) const {
    return PinLevel::LOW;
}

}} // namespace bsw::interface
