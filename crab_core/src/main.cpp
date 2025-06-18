// #####################
// ##   CRABSY-CORE   ##
// #####################
//
// Code for the main ESP32 controller of the Crabsy robot!

# include <Arduino.h>

# include <crabsy/core.hpp>
# include <crabsy/dimensions.hpp>
# include <sylo/logging.hpp>

# define LOG_LEVEL LOG_LEVEL_TRACE

// Local headers
# include "crab_core.hpp"
# include "move.hpp"

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

    log_info("> Starting setup ... ");

    crab_core::move::setup();

    log_infoln("| > Setup done!");

    crab_core::move::apply_default();

    auto angles = crabsy::get_angles_seg2(crabsy::Seg2Coords {
        CRABSY_SEG2_RADIUS,
        -70.0
    });

    log_info("> Angles: Ang2: ");
    log_info(angles.ang2);
    log_info(", Ang3: ");
    log_infoln(angles.ang3);

    auto coords = crabsy::get_coords_seg2(angles);

    log_info("> Coord: R: ");
    log_info(coords.r);
    log_info(", H: ");
    log_infoln(coords.h);
}

void loop() {
    // Going from 90 to 50
    for (int i = 0; i < 10; i++) {
        crab_core::move::apply_height(90 - i*4);
        delay(100);
    }

    // Going from 50 to 130
    for (int i = 0; i < 20; i++) {
        crab_core::move::apply_height(50 + i*4);
        delay(100);
    }

    // Going from 130 to 90
    for (int i = 0; i < 10; i++) {
        crab_core::move::apply_height(130 - i*4);
        delay(100);
    }
}
