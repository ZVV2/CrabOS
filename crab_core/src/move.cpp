# include "move.hpp"

# include <Arduino.h>

namespace crab_core {
    namespace move {
        PCA9685 pwm_board_0 (I2C_ADDR_PWM_BOARD_0);
        PCA9685 pwm_board_1 (I2C_ADDR_PWM_BOARD_1);

        uint8_t servo_offsets [CRABSY_LEG_COUNT][CRABSY_SERVOS_PER_LEG] = {
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 }
        };

        uint16_t convert_to_duty(uint8_t angle, uint8_t leg_id, uint8_t servo_id) {
            return map((angle + servo_offsets[leg_id][servo_id]), MIN_ANGLE, MAX_ANGLE, MIN_DUTY, MAX_DUTY);
        }

        void setup() {
            Wire.begin();

            pwm_board_0.begin();
            pwm_board_1.begin();

            pwm_board_0.setFrequency(SERVO_FREQ);
            pwm_board_1.setFrequency(SERVO_FREQ);
        }

        void apply_single_angle(uint8_t angle, uint8_t leg_id, uint8_t servo_id) {
            if (leg_id < 3) {
                pwm_board_0.setPWM()
            } else {

            }
        }

        // extern void apply_angles_to_all_legs(uint8_t* angles);

        // extern void apply_angle_to_all(uint8_t angle);

        // extern void apply_config(crabsy::ServoConfig config);
    }
}