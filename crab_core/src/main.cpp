// #####################
// ##   CRABSY-CORE   ##
// #####################
//
// Code for the main ESP32 controller of the Crabsy robot!

# include <Arduino.h>

# include <crabsy/core.hpp>
# include <sylo/logging.hpp>

// Local headers
# include "crab_core.hpp"

using crabsy::Configuration;
using crabsy::CoreState;
using crabsy::PrimarySensorData;
using crabsy::SecondarySensorData;
using crabsy::Remote;

// Define global events
namespace bugsy_core {
    Remote remotes = Remote::NONE;
    CoreState state = CoreState::NONE;

    Configuration configuration = {     // Default configuration if loading fails
        /* saved_remote_mode: */    Remote::NONE,

        /* wifi_ssid: */            "",
        /* wifi_pwd: */             ""
    };

    PrimarySensorData primary_sensor_data;
    SecondarySensorData secondary_sensor_data;
}

void setup() {
    // Start logging and print header
    init_logging(UART_CORE_DEBUG_BAUD);

    log_infoln("");
    log_debugln("###################");
    log_debugln("##   CRAB-CORE   ##");
    log_debugln("###################");
    log_debugln("|");
    log_info("> Crabsy Software Version: '");
    log_info(CRABSY_SOFTWARE_VERSION);
    log_debugln("'");
    log_debugln("|");
}

void loop() {

}