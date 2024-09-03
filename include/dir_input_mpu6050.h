#ifndef DIR_INPUT_MPU6050
#define DIR_INPUT_MPU6050

#include "input_template.h"

class C_DIR_INPUT_MPU6050 : public C_DIRECTION_INPUT
{
private:
    bool boVertical;
    bool boHorizontal;
    float fAngleOffset;

    unsigned long previousTime = 0;
    unsigned long lasttimes = 0;
    unsigned long lasttimed = 0;
    float dt; // Time difference

    // Sensor data
    float accX, accY, accZ;
    float gyroX, gyroY, gyroZ;

    // Kalman filter variables
    float angleRoll = 0, anglePitch = 0; // Estimated angles
    float biasRoll = 0, biasPitch = 0;   // Estimated bias
    float P[2][2] = {{1, 0}, {0, 1}};    // Error covariance matrix
    const float Q_angle = 0.001;         // Process noise variance for the accelerometer
    const float Q_bias = 0.003;          // Process noise variance for the gyroscope bias
    const float R_measure = 0.03;        // Measurement noise variance for the accelerometer

    E_DIRECTIONS eLastDirection;
    bool boSend;

    void vReadMPU6050();
    void kalmanFilter(float &angle, float &bias, float gyroRate, float measuredAngle);

public:
    C_DIR_INPUT_MPU6050(){};
    ~C_DIR_INPUT_MPU6050(){};
    void vInputInit();
    void vInputLoop();
    E_DIRECTIONS eGetDirection(bool *pboSend);
};

#endif
