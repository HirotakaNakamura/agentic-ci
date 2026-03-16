// VehicleController.cpp - OEM Vehicle Control Application
// This file integrates with BSW layers to implement vehicle control logic.

#include "VehicleController.h"
#include <fstream>
#include <sstream>
#include <string>

// BUG #2: Missing #include <iostream> - uses std::cout without it

namespace oem {

bool VehicleController::loadTestData(const std::string& csvPath) {
    std::ifstream file(csvPath);
    if (!file.is_open()) {
        return false;
    }

    std::string line;
    std::getline(file, line); // skip header

    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string token;
        SensorData data{};

        std::getline(ss, token, ','); // cycle (skip)
        std::getline(ss, token, ','); data.throttle_adc = static_cast<uint16_t>(std::stoi(token));
        std::getline(ss, token, ','); data.engine_rpm = static_cast<uint16_t>(std::stoi(token));
        std::getline(ss, token, ','); data.vehicle_speed_kmh = static_cast<uint16_t>(std::stoi(token));
        std::getline(ss, token, ','); data.brake_pressure = static_cast<uint16_t>(std::stoi(token));

        testData_.push_back(data);
    }

    std::cout << "Loaded " << testData_.size() << " test data cycles from: " << csvPath << std::endl;
    return !testData_.empty();
}

void VehicleController::init() {
    std::cout << std::endl;

    // Initialize RTOS
    scheduler_.init();

    // Initialize HAL
    gpio_.configurePin(13, bsw::interface::PinDirection::OUTPUT);  // Engine indicator LED
    gpio_.configurePin(14, bsw::interface::PinDirection::OUTPUT);  // Brake indicator LED
    adc_.init(0);   // Throttle sensor ADC channel
    pwm_.init(1, 1000); // Throttle actuator PWM at 1kHz

    // Initialize Middleware
    canBus_.init(500000);  // CAN bus at 500kbps
    diag_.init();
    diag_.startSession(bsw::middleware::DiagSession::DEFAULT);

    std::cout << std::endl;
}

void VehicleController::run() {
    std::cout << "--- Starting vehicle control loop ---" << std::endl;
    std::cout << std::endl;

    for (size_t i = 0; i < testData_.size(); ++i) {
        std::cout << "--- Cycle " << (i + 1) << "/" << testData_.size()
                  << " ---" << std::endl;

        readSensors(i);
        processCanMessages(i);
        controlActuators(i);

        if (i == 0) {
            runDiagnostics();
        }

        std::cout << std::endl;
    }

    std::cout << "=== Simulation complete: " << testData_.size()
              << " cycles executed ===" << std::endl;
}

void VehicleController::readSensors(size_t cycleIndex) {
    const auto& data = testData_[cycleIndex];

    // Set simulated ADC value from CSV and read it
    adc_.setSimValue(0, data.throttle_adc);
    uint16_t throttle = adc_.read(0);

    float throttlePercent = (static_cast<float>(throttle) / 4095.0f) * 100.0f;
    std::cout << "[OEM ] Throttle position: " << throttlePercent << "%" << std::endl;
    std::cout << "[OEM ] Vehicle speed: " << data.vehicle_speed_kmh << " km/h" << std::endl;
}

void VehicleController::processCanMessages(size_t cycleIndex) {
    const auto& data = testData_[cycleIndex];

    // Send throttle position via CAN
    bsw::middleware::CanMessage txMsg;
    txMsg.id = 0x100;
    txMsg.dlc = 4;
    txMsg.data[0] = static_cast<uint8_t>(data.throttle_adc >> 8);
    txMsg.data[1] = static_cast<uint8_t>(data.throttle_adc & 0xFF);
    txMsg.data[2] = static_cast<uint8_t>(data.vehicle_speed_kmh >> 8);
    txMsg.data[3] = static_cast<uint8_t>(data.vehicle_speed_kmh & 0xFF);

    // BUG #3: Wrong API usage - passing extra argument
    // CanDriver::send() takes only (const CanMessage&), not (CanId, const CanMessage&)
    canBus_.send(0x100, txMsg);
}

void VehicleController::controlActuators(size_t cycleIndex) {
    const auto& data = testData_[cycleIndex];

    // Calculate throttle duty cycle from ADC value
    float dutyCycle = (static_cast<float>(data.throttle_adc) / 4095.0f) * 100.0f;
    pwm_.setDutyCycle(1, dutyCycle);

    // Engine indicator: ON when RPM > 1000
    if (data.engine_rpm > 1000) {
        // BUG #1: Type mismatch - passing int literal instead of PinLevel enum
        // Should be bsw::interface::PinLevel::HIGH
        gpio_.writePin(13, 1);
    } else {
        gpio_.writePin(13, 0);
    }

    // Brake indicator: ON when braking
    if (data.brake_pressure > 0) {
        gpio_.writePin(14, bsw::interface::PinLevel::HIGH);
    } else {
        gpio_.writePin(14, bsw::interface::PinLevel::LOW);
    }
}

void VehicleController::runDiagnostics() {
    std::cout << "[OEM ] Running initial diagnostics..." << std::endl;

    // Read VIN
    std::vector<uint8_t> vinData;
    if (diag_.readDataById(0xF190, vinData)) {
        std::string vin(vinData.begin(), vinData.end());
        std::cout << "[OEM ] VIN: " << vin << std::endl;
    }

    // Read ECU Serial
    std::vector<uint8_t> serialData;
    if (diag_.readDataById(0xF101, serialData)) {
        std::string serial(serialData.begin(), serialData.end());
        std::cout << "[OEM ] ECU Serial: " << serial << std::endl;
    }
}

} // namespace oem
