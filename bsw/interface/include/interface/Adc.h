#pragma once
#include "interface/HalTypes.h"

namespace bsw { namespace interface {

class Adc {
public:
    bool init(AdcChannel channel);
    uint16_t read(AdcChannel channel) const;
    void setSimValue(AdcChannel channel, uint16_t value);

private:
    uint16_t simValues_[16] = {};
};

}} // namespace bsw::interface
