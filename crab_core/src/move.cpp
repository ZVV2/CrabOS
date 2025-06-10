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

        uint16_t convert_to_duty(int8_t angle, uint8_t leg_id, uint8_t servo_id) {
            return map((angle + servo_offsets[leg_id][servo_id]), MIN_ANGLE, MAX_ANGLE, MIN_DUTY, MAX_DUTY);
        }

        void setup() {
            Wire.begin();

            pwm_board_0.begin();
            pwm_board_1.begin();

            pwm_board_0.setFrequency(SERVO_FREQ);
            pwm_board_1.setFrequency(SERVO_FREQ);
        }

        void apply_single_angle(int8_t angle, uint8_t leg_id, uint8_t servo_id) {
            if (leg_id < 3) {
                pwm_board_0.setPWM(leg_id*4 + servo_id, convert_to_duty(angle, leg_id, servo_id));
            } else {
                pwm_board_1.setPWM((leg_id - 3)*4 + servo_id, convert_to_duty(angle, leg_id, servo_id));
            }
        }

        void apply_angles_to_all_legs(int8_t* angles) {
            for (uint8_t leg_id = 0; leg_id < 3; leg_id++) {
                for (uint8_t servo_id = 0; servo_id < CRABSY_SERVOS_PER_LEG; servo_id++) {
                    pwm_board_0.setPWM(leg_id*4 + servo_id, convert_to_duty(angles[servo_id], leg_id, servo_id));
                }
            }

            for (uint8_t leg_id = 3; leg_id < 6; leg_id++) {
                for (uint8_t servo_id = 0; servo_id < CRABSY_SERVOS_PER_LEG; servo_id++) {
                    pwm_board_1.setPWM((leg_id - 3)*4 + servo_id, convert_to_duty(angles[servo_id], leg_id, servo_id));
                }
            }
        }

        void apply_angle_to_all(int8_t angle) {
            for (uint8_t leg_id = 0; leg_id < 6; leg_id++) {
                for (uint8_t servo_id = 0; servo_id < 3; servo_id++) {
                    apply_single_angle(angle, leg_id, servo_id);
                }
            }
        }

        // extern void apply_config(crabsy::ServoConfig config);
    }
}