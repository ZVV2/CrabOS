# pragma once

# include <crabsy/core.hpp>

# define UART_CORE_DEBUG_BAUD 115200

# define I2C_ADDR_PWM_BOARD_0 0x40
# define I2C_ADDR_PWM_BOARD_1 0x41

# define SERVO_FREQ 50

namespace crab_core {
    extern crabsy::Remote remote;
    extern crabsy::CoreState state;

    extern crabsy::Configuration configuration;

    extern crabsy::PrimarySensorData primary_sensor_data;
    extern crabsy::SecondarySensorData secondary_sensor_data;
}