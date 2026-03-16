#pragma once
#include "interface/HalTypes.h"

namespace bsw { namespace interface {

class Gpio {
public:
    bool configurePin(PinId pin, PinDirection dir);
    bool writePin(PinId pin, PinLevel level);
    PinLevel readPin(PinId pin) const;
};

}} // namespace bsw::interface
