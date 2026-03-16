#include "interface/Adc.h"
#include <iostream>

namespace bsw { namespace interface {

bool Adc::init(AdcChannel channel) {
    std::cout << "[HAL ] ADC channel " << static_cast<int>(channel) << " initialized" << std::endl;
    simValues_[channel % 16] = 0;
    return true;
}

uint16_t Adc::read(AdcChannel channel) const {
    uint16_t val = simValues_[channel % 16];
    std::cout << "[HAL ] ADC ch" << static_cast<int>(channel) << " read: " << val << std::endl;
    return val;
}

void Adc::setSimValue(AdcChannel channel, uint16_t value) {
    simValues_[channel % 16] = value;
}

}} // namespace bsw::interface
