# include "move.hpp"

# include <Arduino.h>

namespace crab_core {
    namespace move {
        PCA9685 pwm_board_0 (I2C_ADDR_PWM_BOARD_0);
        PCA9685 pwm_board_1 (I2C_ADDR_PWM_BOARD_1);

        uint16_t convert_to_duty(int8_t angle, uint8_t leg_id, uint8_t servo_id) {
            // Invert if it's the last leg segment
            if (servo_id == 2) {
                return map((angle + CRABSY_ANGLE_OFFSETS[leg_id][servo_id]), MIN_ANGLE, MAX_ANGLE, MAX_DUTY, MIN_DUTY);
            } else {
                return map((angle + CRABSY_ANGLE_OFFSETS[leg_id][servo_id]), MIN_ANGLE, MAX_ANGLE, MIN_DUTY, MAX_DUTY);
            }
        }

        void setup() {
            Wire.begin();

            pwm_board_0.begin();
            pwm_board_1.begin();

            pwm_board_0.setFrequency(SERVO_FREQ);
            pwm_board_1.setFrequency(SERVO_FREQ);
        }
        
        /* # GENERAL */
            void apply_default() {
                apply_to_all(NEUTRAL_ANGLE);
            }
        /**/

        /* # TIER-1 */
            void apply_single(int8_t angle, uint8_t leg_id, uint8_t servo_id) {
                if (leg_id < 3) {
                    pwm_board_0.setPWM(leg_id*4 + servo_id, convert_to_duty(angle, leg_id, servo_id));
                } else {
                    pwm_board_1.setPWM((leg_id - 3)*4 + servo_id, convert_to_duty(angle, leg_id, servo_id));
                }
            }

            void apply_single_leg(int8_t* angle_list, uint8_t leg_id) {
                // Evaluate if first or second PWM board
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

        /* # TIER 2 */
            void apply_seg2_single(crabsy::Seg2Coords coords, uint8_t leg_id) {
                crabsy::Seg2Angles angles = crabsy::get_angles_seg2(coords);
                int8_t int_angles[3] = { 0, (int8_t)(degrees(angles.ang2)), (int8_t)(degrees(angles.ang3)) };

                apply_single_leg(int_angles, leg_id);
            }

            void apply_seg2_to_all(crabsy::Seg2Coords coords) {
                crabsy::Seg2Angles angles = crabsy::get_angles_seg2(coords);
                int8_t int_angles[3] = { 0, (int8_t)(degrees(angles.ang2)), (int8_t)(degrees(angles.ang3)) };

                apply_to_all_legs(int_angles);
            }

            void apply_height(float height) {
                apply_seg2_to_all(crabsy::Seg2Coords {
                    CRABSY_SEG2_RADIUS,
                    -height
                });
            }
        /**/

        /* # ROUTINES
         *
         * Complex routines for different tasks
         */
            void stand_up() {
                // First move all legs into the air 
                apply_height(0.0);
                delay(750);
                // Apply default position
                apply_default();
                delay(750);
            }

            void lay_down() {
                apply_default();
                delay(800);
                
                for (int i = 1; i <= 20; i++) {
                    apply_seg2_to_all(crabsy::Seg2Coords {
                        CRABSY_SEG2_RADIUS,
                        CRABSY_SEG2_HEIGHT * (float)(20 - i) / (float)20.0
                    });
                    delay(75);
                }
            }

            void trunk_mode() {
                int8_t trunk_pos[3] = { 0, 90, -90 };
                apply_to_all_legs(trunk_pos);
                delay(750);

                // Narrow down legs
                apply_single(-45, 1, 0);
                apply_single(45, 2, 0);
                apply_single(-45, 4, 0);
                apply_single(45, 5, 0);
            }
        /**/
    }
}