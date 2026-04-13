#pragma once

#include "esp_err.h"
#include "cstdint"

struct ImuRawData
{
    int16_t g_x;
    int16_t g_y;
    int16_t g_z;
    int16_t a_x;
    int16_t a_y;
    int16_t a_z;
    int8_t temp;
};

esp_err_t mpu6500_init(void);
esp_err_t mpu6500_read_raw_data(ImuRawData &data);