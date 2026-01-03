# pragma once

# include <crabsy/core.hpp>

/// @brief Baud rate to USB-UART with an external device for debugging
# define UART_CORE_DEBUG_BAUD 115200

/// @brief I2C Address of the first PWM-Board
# define I2C_ADDR_PWM_BOARD_0 0x40
/// @brief I2C Address of the second PWM-Board
# define I2C_ADDR_PWM_BOARD_1 0x41

/// @brief PWM frequency of the servos
# define SERVO_FREQ 50

namespace crab_core {
    /// @brief Current remote configuration used
    extern crabsy::Remote remote;
    /// @brief Current state of the core microcontroller
    extern crabsy::CoreState state;

    /// @brief Configuration structure with setting fields
    extern crabsy::Configuration configuration;

    /// @brief Main sensor data stored in the core (updates frequently)
    extern crabsy::PrimarySensorData primary_sensor_data;
    /// @brief Secondary sensor data stored in the core (updates every now and then)
    extern crabsy::SecondarySensorData secondary_sensor_data;
}