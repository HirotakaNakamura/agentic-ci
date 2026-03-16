#include "VehicleController.h"
#include <iostream>

int main(int argc, char* argv[]) {
    std::string csvPath = "test_data/driving_scenario.csv";
    if (argc > 1) {
        csvPath = argv[1];
    }

    std::cout << "=== Automotive BSW + OEM Integration Demo ===" << std::endl;
    std::cout << std::endl;

    oem::VehicleController controller;

    if (!controller.loadTestData(csvPath)) {
        std::cerr << "Failed to load test data from: " << csvPath << std::endl;
        return 1;
    }

    controller.init();
    controller.run();

    return 0;
}
