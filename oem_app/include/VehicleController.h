#pragma once

#include "os/Scheduler.h"
#include "os/Task.h"
#include "middleware/CanDriver.h"
#include "middleware/CanMessage.h"
#include "middleware/UdsDiag.h"
#include "interface/Gpio.h"
#include "interface/Adc.h"
#include "interface/Pwm.h"

#include <string>
#include <vector>

namespace oem {

struct SensorData {
    uint16_t throttle_adc;
    uint16_t engine_rpm;
    uint16_t vehicle_speed_kmh;
    uint16_t brake_pressure;
};

class VehicleController {
public:
    bool loadTestData(const std::string& csvPath);
    void init();
    void run();

private:
    void readSensors(size_t cycleIndex);
    void processCanMessages(size_t cycleIndex);
    void controlActuators(size_t cycleIndex);
    void runDiagnostics();

    bsw::os::Scheduler scheduler_;
    bsw::middleware::CanDriver canBus_;
    bsw::middleware::UdsDiag diag_;
    bsw::interface::Gpio gpio_;
    bsw::interface::Adc adc_;
    bsw::interface::Pwm pwm_;

    std::vector<SensorData> testData_;
};

} // namespace oem
