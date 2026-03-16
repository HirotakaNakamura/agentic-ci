add_executable(vehicle_app
    src/main.cpp
    src/VehicleController.cpp
)
target_include_directories(vehicle_app PRIVATE include)
target_link_libraries(vehicle_app PRIVATE bsw)
