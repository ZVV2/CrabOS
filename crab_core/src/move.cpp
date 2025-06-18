# include "move.hpp"

# include <Arduino.h>

namespace crab_core {
    namespace move {
        PCA9685 pwm_board_0 (I2C_ADDR_PWM_BOARD_0);
        PCA9685 pwm_board_1 (I2C_ADDR_PWM_BOARD_1);

        uint8_t servo_offset_list [CRABSY_LEG_COUNT][CRABSY_SERVOS_PER_LEG] = {
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 }
        };

        uint16_t convert_to_duty(int8_t angle, uint8_t leg_id, uint8_t servo_id) {
            // Invert if it's the last leg segment
            if (servo_id == 2) {
                return map((angle + servo_offset_list[leg_id][servo_id]), MIN_ANGLE, MAX_ANGLE, MAX_DUTY, MIN_DUTY);
            } else {
                return map((angle + servo_offset_list[leg_id][servo_id]), MIN_ANGLE, MAX_ANGLE, MIN_DUTY, MAX_DUTY);
            }
        }

        void setup() {
            Wire.begin();

            pwm_board_0.begin();
            pwm_board_1.begin();

            pwm_board_0.setFrequency(SERVO_FREQ);
            pwm_board_1.setFrequency(SERVO_FREQ);
        }
        
        /* GENERAL */
            void apply_default() {
                apply_to_all(NEUTRAL_ANGLE);
            }
        /**/

        /* TIER 1 */
            void apply_single(int8_t angle, uint8_t leg_id, uint8_t servo_id) {
                if (leg_id < 3) {
                    pwm_board_0.setPWM(leg_id*4 + servo_id, convert_to_duty(angle, leg_id, servo_id));
                } else {
                    pwm_board_1.setPWM((leg_id - 3)*4 + servo_id, convert_to_duty(angle, leg_id, servo_id));
                }
            }

            void apply_single_leg(int8_t* angle_list, uint8_t leg_id) {
                if (leg_id < 3) {
                    for (uint8_t servo_id = 0; servo_id < CRABSY_SERVOS_PER_LEG; servo_id++) {
                        pwm_board_0.setPWM(leg_id*4 + servo_id, convert_to_duty(angle_list[servo_id], leg_id, servo_id));
                    }
                } else {
                    for (uint8_t servo_id = 0; servo_id < CRABSY_SERVOS_PER_LEG; servo_id++) {
                        pwm_board_0.setPWM((leg_id - 3)*4 + servo_id, convert_to_duty(angle_list[servo_id], leg_id, servo_id));
                    }
                }
            }

            void apply_to_all_legs(int8_t* angle_list) {
                for (uint8_t leg_id = 0; leg_id < 3; leg_id++) {
                    for (uint8_t servo_id = 0; servo_id < CRABSY_SERVOS_PER_LEG; servo_id++) {
                        pwm_board_0.setPWM(leg_id*4 + servo_id, convert_to_duty(angle_list[servo_id], leg_id, servo_id));
                    }
                }

                for (uint8_t leg_id = 3; leg_id < 6; leg_id++) {
                    for (uint8_t servo_id = 0; servo_id < CRABSY_SERVOS_PER_LEG; servo_id++) {
                        pwm_board_1.setPWM((leg_id - 3)*4 + servo_id, convert_to_duty(angle_list[servo_id], leg_id, servo_id));
                    }
                }
            }

            void apply_to_all(int8_t angle) {
                for (uint8_t leg_id = 0; leg_id < 6; leg_id++) {
                    for (uint8_t servo_id = 0; servo_id < 3; servo_id++) {
                        apply_single(angle, leg_id, servo_id);
                    }
                }
            }

            void apply_config(crabsy::ServoConfig config) {
                for (uint8_t leg_id = 0; leg_id < 6; leg_id++) {
                    for (uint8_t servo_id = 0; servo_id < 3; servo_id++) {
                        apply_single(config[leg_id*CRABSY_LEG_COUNT + servo_id], leg_id, servo_id);
                    }
                }   
            }
        /**/

        /* TIER 2 */
            void apply_seg2_single(crabsy::Seg2Coords coords, uint8_t leg_id) {
                crabsy::Seg2Angles angles = crabsy::get_angles_seg2(coords);
                int8_t int_angles[3] = { 0, (int)(degrees(angles.ang2)), (int)(degrees(angles.ang3)) };

                apply_single_leg(int_angles, leg_id);
            }

            void apply_to_all_seg2(crabsy::Seg2Coords coords) {
                crabsy::Seg2Angles angles = crabsy::get_angles_seg2(coords);
                int8_t int_angles[3] = { 0, (int)(degrees(angles.ang2)), (int)(degrees(angles.ang3)) };

                apply_to_all_legs(int_angles);
            }

            void apply_height(float height) {
                apply_to_all_seg2(crabsy::Seg2Coords {
                    CRABSY_SEG2_RADIUS,
                    -height
                });
            }
        /* */
    }
}