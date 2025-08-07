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
        extern PCA9685 pwm_board_0;
        extern PCA9685 pwm_board_1;

        extern uint8_t servo_offset_list [CRABSY_LEG_COUNT][CRABSY_SERVOS_PER_LEG];

        extern uint16_t convert_to_duty(int8_t angle, uint8_t leg_id, uint8_t servo_id);

        extern void setup();

        /* GENERAL */
            extern void apply_default();
        /**/

        /* TIER-1 */
            extern void apply_single(int8_t angle, uint8_t leg_id, uint8_t servo_id);

            extern void apply_single_leg(int8_t* angle_list, uint8_t leg_id);

            extern void apply_to_all_legs(int8_t* angle_list);

            extern void apply_to_all(int8_t angle);

            extern void apply_config(crabsy::ServoConfig config);
        /**/

        /* TIER-2 */
            extern void apply_seg2_single(crabsy::Seg2Coords coords, uint8_t leg_id);

            extern void apply_seg2_to_all(crabsy::Seg2Coords coords);

            extern void apply_height(float height);
        /**/

        /* TIER-3 */
            // extern void apply_seg3_single()
        /**/

        /* ROUTINES */
            extern void stand_up(); 
        /**/
    }
}