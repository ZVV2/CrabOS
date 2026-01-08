# pragma once

# include <PCA9685.h>
# include <inttypes.h>

# include <crabsy/core.hpp>
# include <crabsy/dimensions.hpp>

# include "crab_core.hpp"

# define MIN_ANGLE -90
# define NEUTRAL_ANGLE ((MAX_ANGLE + MIN_ANGLE) / 2)
# define MAX_ANGLE 90

# define MIN_DUTY ((uint16_t)((1.0 / 20.0) * 4096))
# define NEUTRAL_DUTY ((MAX_DUTY + MIN_DUTY) / 2)
# define MAX_DUTY ((uint16_t)((2.0 / 20.0) * 4096))

namespace crab_core {
    namespace move {
        /// First PCA9685 PWM board, connected to legs 1, 2 and 3
        extern PCA9685 pwm_board_0;
        /// Second PCA9685 PWM board, connected to legs 4, 5 and 6
        extern PCA9685 pwm_board_1;

        /// Converts the given integer `angle` (in degrees) to a PWM duty for the servo with the given `leg_id` and `servo_id`
        extern uint16_t convert_to_duty(int8_t angle, uint8_t leg_id, uint8_t servo_id);

        /// Sets up everything movement related from the core
        extern void setup();

        /* # GENERAL
         * 
         * General purpose functions for frequently used states 
         */
            /// Applies the default state to all motorss
            extern void apply_default();
        /**/

        /* # TIER-1 
         *
         * These functions are the basic angle assignments to motors and control
         */
            /// Applies an `angle` (in degrees) to a single servo motor with the given `leg_id` and `servo_id`
            extern void apply_single(int8_t angle, uint8_t leg_id, uint8_t servo_id);

            /// Applies an array of angles (`angle_list`, degrees) to the leg with the given `leg_id`
            extern void apply_single_leg(int8_t* angle_list, uint8_t leg_id);

            /// Applies an array of angles (`angle_list`, degrees) to all legs
            extern void apply_to_all_legs(int8_t* angle_list);

            /// Applies a single `angle` to all servos
            extern void apply_to_all(int8_t angle);

            /// Applies a full configuration to all servos (custom angle in degrees for all servos, see `crabsy::ServoConfig`)
            extern void apply_config(crabsy::ServoConfig config);
        /**/

        /* # TIER 2 
         * 
         * These function enable controlling parts of the robot with coordinates and utilizing real world dimensions
         */
            /// Applies a single set of `Seg2Coords` to the leg with the given `leg_id`
            extern void apply_seg2_single(crabsy::Seg2Coords coords, uint8_t leg_id);

            /// Applies a set of `Seg2Coords` to all legs
            extern void apply_seg2_to_all(crabsy::Seg2Coords coords);

            /// Places all legs of the robot to their default radius and a certain height above their default position
            /// 
            /// # Note
            ///
            /// Height is inversed, not like the TCPs of the legs, meaning a positive height will result in the robot standing
            extern void apply_height(float height);
        /**/

        /* TIER-3 */
            // extern void apply_seg3_single()
        /**/

        /* # ROUTINES
         *
         * Complex routines for different tasks
         */
            /// This routine enables the robot a clean stand-up from lying on the ground face up (as it is supposed to be)
            extern void stand_up(); 

            extern void lay_down();

            /// Positions the robot so it can easily be placed into the trunk
            extern void trunk_mode();
        /**/
    }
}