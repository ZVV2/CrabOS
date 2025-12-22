namespace crabsy {
    static bool is_operational(CoreState state) {
        return (bool)(((uint8_t)state) & 0x20);
    }

    int8_t get_servo_angle(ServoConfig config, uint8_t leg_id, uint8_t motor_id) {
        return config[leg_id * 3 + motor_id];
    }
}