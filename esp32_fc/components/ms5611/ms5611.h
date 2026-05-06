#pragma once

#include "esp_err.h"
#include <cstdint>

struct BarometerData{
    int32_t pressure;
    int32_t temp;
};

esp_err_t ms5611_init(void);
esp_err_t ms5611_read_data(BarometerData &data);