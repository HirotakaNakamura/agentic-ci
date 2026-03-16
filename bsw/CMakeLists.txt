add_library(bsw_os
    os/src/Task.cpp
    os/src/Scheduler.cpp
)
target_include_directories(bsw_os PUBLIC os/include)

add_library(bsw_middleware
    middleware/src/CanDriver.cpp
    middleware/src/UdsDiag.cpp
)
target_include_directories(bsw_middleware PUBLIC middleware/include)

add_library(bsw_interface
    interface/src/Gpio.cpp
    interface/src/Adc.cpp
    interface/src/Pwm.cpp
)
target_include_directories(bsw_interface PUBLIC interface/include)

# Umbrella target
add_library(bsw INTERFACE)
target_link_libraries(bsw INTERFACE bsw_os bsw_middleware bsw_interface)
