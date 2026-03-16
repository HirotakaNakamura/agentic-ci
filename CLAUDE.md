# Automotive BSW + OEM Integration Project

## Project Structure
- `bsw/` - BSW (Basic Software) vendor code. DO NOT MODIFY these files.
  - `bsw/os/` - RTOS layer (Task, Scheduler)
  - `bsw/middleware/` - Communication stack (CAN), UDS diagnostics
  - `bsw/interface/` - HAL layer (GPIO, ADC, PWM)
- `oem_app/` - OEM application code. This is what you should fix when build errors occur.
- `test_data/` - CSV test data for simulation

## Build Commands
```
cmake -B build -S . && cmake --build build 2>&1
```

## Run
```
./build/oem_app/vehicle_app test_data/driving_scenario.csv
```

## Rules
- Only modify files under `oem_app/`.
- BSW headers define the correct API. Read them to understand expected types and signatures.
- C++17 standard.
- When fixing build errors, read the BSW header files to understand the correct API signatures and types.
