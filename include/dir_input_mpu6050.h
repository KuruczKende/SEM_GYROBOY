#ifndef DIR_INPUT_MPU6050
#define DIR_INPUT_MPU6050

class C_DIR_INPUT_MPU6050: public C_DIRECTION_INPUT{
private:
    MPU6050 accelgyro;
    int16_t s16Ox, s16Oy, s16Oz; // offsets / starting pos
    int16_t s16Ax, s16Ay, s16Az;
    int16_t s16Gx, s16Gy, s16Gz;
    uint32_t u32LastTime;
public:
    C_DIR_INPUT_MPU6050(){};
    ~C_DIR_INPUT_MPU6050(){};
    void vInputInit();
    void vInputLoop();
    E_DIRECTIONS eGetDirection(bool* pboSend);
}


#endif
