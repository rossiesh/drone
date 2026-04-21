#pragma once

#include "esp_err.h"
#include "cstdint"

struct ImuData
{
    int16_t a_x;
    int16_t a_y;
    int16_t a_z;
    int16_t temp;
    int16_t g_x;
    int16_t g_y;
    int16_t g_z;
};

esp_err_t mpu6500_init(void);
esp_err_t mpu6500_read_data(ImuData &imu_data);
esp_err_t mpu6500_calibrate_gyro(void);