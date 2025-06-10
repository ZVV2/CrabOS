// ###################
// ##   CRAB_CORE   ##
// ###################
//
// Public data and structures relevant for communicating with the core MCU of the crabsy robot

# pragma once

# include <inttypes.h>

# include "defines.hpp"

/// Structures and functions concerning the Crabsy Robot
namespace crabsy {
    /// The status of the core MCU
    enum class CoreState : uint8_t {
        /// No state has been set yet
        NONE = 0x00,

        /// The controller is currently setting up
        SETUP = 0x10,
        /// The robot is in standby mode, saving power
        STANDBY = 0x11,

        /// The robot is active and ready to perform movements / protocols
        ACTIVE = 0x20,
        /// The controller is at full activity and running
        MOVING = 0x21,

        /// The controller has stopped due to a critical error
        ERROR = 0x80
    };

    /// Checks whether a state is operational or not
    /// @param state The state to check
    /// @return Wheither the state is operational or not
    static bool is_operational(CoreState state) {
        return (bool)(((uint8_t)state) & 0x20);
    }

    /// Command-codes that can be sent to the bugsy to cause actions / acquire data
    enum class Command : uint8_t {
        /// Test command for debug purposes
        /// @return The additional bytes given
        Test = 0x00,

        /// State command mainly for internal communication
        /// @return `0x00` - The current `State` (see `crabsy::State`)
        GetState = 0x01,

        /// Issue new angles for the servo motors
        /// @param `0x00-0x03` 4 byte `Movement` struct, will be parsed and applied directly, every sequence of bytes is valid!
        SetServos = 0x10,

        /// Internal command to set the stored state of the trader that will be communicated to external devices  
        /// The function also returns the current state of the Bugsy robot
        /// @param `0x00` The `bugsy_trader::State` to be stored in the core
        /// @return `0x00` The current `bugsy_core::State` of the core
        SetTraderState = 0x20,
        /// Get the (currently in the core registered) state of the trader MCU
        /// @return `0x00` The `bugsy_trader::State` value
        GetTraderState = 0x21,

        /// Internal command for publishing important (primary) sensor data to the core MCU
        /// @param `0x00-sizeof(bugsy_trader::PrimarySensorData)` the data to store
        PublishPrimarySensorData = 0x22,
        /// Returns the primary sensor data stored in the core
        /// @return `bugsy_trader::PrimarySensorData`
        GetPrimarySensorData = 0x23,
        /// Internal command for publishing less important (secondary) sensor data to the core MCU
        PublishSecondarySensorData = 0x24,
        GetSecondarySensorData = 0x25,

        /// Internal command to signal that the RPi is ready
        SetRPiReady = 0x28,
        /// Get whether the raspberry pi is ready or not
        IsRPiReady = 0x29,

        /// Returns the current remote configuration
        /// @return `0x00` - The current remote mode
        Remotes = 0x40,
        /// Reconfigures the remote settings made
        /// @param 0x00 The new `Remotes`
        RemoteConfigure = 0x41,

        /// Safe the configuration to the EEPROM
        SaveConfig = 0x80,

        /// Get the current SSID for the WiFi connection
        /// @return The WiFi SSID as null terminated string (for max len see `WIFI_BUFFER_SIZE`)
        GetWiFiSSID = 0xA0, 
        /// Set the current SSID for the WiFi connection
        /// @param 0x00-? The WiFi SSID as null terminated string (for max len see `WIFI_BUFFER_SIZE`)
        SetWiFiSSID = 0xA1,
        
        /// Get the current password for the WiFi connection
        /// @return The WiFi password as null terminated string (for max len see `WIFI_BUFFER_SIZE`)
        GetWiFiPwd = 0xA2,
        /// Set the current password for the WiFi connection
        /// @param 0x00-? The WiFi password as null terminated string (for max len see `WIFI_BUFFER_SIZE`)
        SetWiFiPwd = 0xA3
    }; 

    /// All the possible remotes, assigning them IDs  
    /// Used as a kind of network address to determine where a piece of data was retrieved from or where it has to be sent 
    enum class Remote : uint8_t {
        /// Errorful `None` address, indicates that something went wrong
        NONE = 0x00,

        /// Bluetooth, the main source of remote configuration
        BLUETOOTH = 0x01,

        // Local
        /// Direct UART connection via the USB port
        USB = 0x04,
        /// Direct UART connection to the Trader MCU
        TRADER = 0x08,
        /// Direct UART connection to the RPi 
        RPI = 0x10,

        // Wifi
        /// Wifi data, transfered by a TCP socket
        WIFI_TCP = 0x20,
        /// Wifi data, transfered using MQTT  
        WIFI_MQTT = 0x40,

        /// Any WiFi source (all when sending)
        ANY_WIFI = 0x60,

        /// Communication with the Mod-slot
        MOD = 0x80
    };

    /* ERRORS */
        /// General error codes for the core MCU
        enum class CoreError : uint8_t {
            /// No error as occured
            None = 0x00,
            /// No WiFi data has been set yet, while being required for this operation though
            NoWiFiDataSet = 0x10
        };
    /**/

    /* ANGLES */
        /// An array of angles for the Servomotors
        /// - The angles are in pairs of 3 for each leg
        typedef int8_t* ServoConfig;

        /// Returns a single servo angle out of a configuration
        /// @param config The `ServoConfig`
        /// @param leg_id The id of the leg which the servo is part of
        /// @param motor_id The motor id of the leg
        /// @return The servo angle
        static int8_t get_servo_angle(ServoConfig config, uint8_t leg_id, uint8_t motor_id) {
            return config[leg_id * 3 + motor_id];
        }
    /**/

    /* CONFIGURATION */
        struct Configuration {
            /// The remote stored in the configuration, not representing the current mode!
            crabsy::Remote saved_remote_mode;

            /// The WIFI SSID used, parsed from the configuration on setup
            char wifi_ssid [CRABSY_WIFI_CRED_BUFFER_SIZE];
            /// The WIFI Password used, parsed from the configuration on setup
            char wifi_password [CRABSY_WIFI_CRED_BUFFER_SIZE];
        };
    /**/

    /* SENSOR DATA */
        struct PrimarySensorData {

        };

        struct SecondarySensorData {

        };
    /**/

    /* STATICS */
        /// The MAC address of the core controller
        static uint8_t CORE_MAC [6] = { 0xB0, 0xa7, 0x32, 0x2D, 0x6F, 0x5A };
    /**/
}