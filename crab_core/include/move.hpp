# pragma once

# include <PCA9685.h>
# include <inttypes.h>

# include <crabsy/core.hpp>

# include "crab_core.hpp"

# define MIN_ANGLE 0
# define NEUTRAL_ANGLE ((MAX_ANGLE + MIN_ANGLE) / 2)
# define MAX_ANGLE 180

# define MIN_DUTY ((uint16_t)((1.0 / 20.0) * 4096))
# define NEUTRAL_DUTY ((MAX_DUTY + MIN_DUTY) / 2)
# define MAX_DUTY ((uint16_t)((2.0 / 20.0) * 4096))

namespace crab_core {
    namespace move {
        extern PCA9685 pwm_board_0;
        extern PCA9685 pwm_board_1;

        extern uint8_t servo_offsets [CRABSY_LEG_COUNT][CRABSY_SERVOS_PER_LEG];

        extern uint16_t convert_to_duty(uint8_t angle, uint8_t leg_id, uint8_t servo_id);

        extern void setup();

        extern void apply_single_angle(uint8_t angle, uint8_t leg_id, uint8_t servo_id);

        extern void apply_angles_to_all_legs(uint8_t* angles);

        extern void apply_angle_to_all(uint8_t angle);

        extern void apply_config(crabsy::ServoConfig config);
    }
}