# pragma once

# include <crabsy/core.hpp>

# define UART_CORE_DEBUG_BAUD 115200

namespace crab_core {
    extern crabsy::Remote remote;
    extern crabsy::CoreState state;

    extern crabsy::Configuration configuration;

    extern crabsy::PrimarySensorData primary_sensor_data;
    extern crabsy::SecondarySensorData secondary_sensor_data;
}