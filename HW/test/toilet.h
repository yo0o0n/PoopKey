typedef (unsigned char) uint8_t;
typedef (unsigned short) uint16_t;
typedef (unsigned int) uint32_t;



typedef struct ToiletStall {
    uint8_t is_occupied; // 원래 bool
    uint32_t last_open_time; // 원래 int
    float tissue_amount;
    uint8_t is_cover_down;  // 원래 bool
    uint32_t last_ir_time;  // 원래 int
    uint32_t last_flush_time;  // 원래 int
    uint8_t is_checked_broken; // 원래 bool
    uint32_t last_tissue_time; // 원래 int

    GI magnetic_door;
    GI sonar_tissue;
    GI sonar_water_tissue;
    GI sonar_toilet_broken;
    II ir_untact;
    GI led_usable;
    GI led_broken;
    GI led_tissue;
    TI servo_water_tissue;
    TI servo_toilet_cover;
    GI tilt_toilet_cover;
}TS;
