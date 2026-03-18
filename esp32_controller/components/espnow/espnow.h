#pragma once

#include "esp_err.h"
#include <cstddef>
#include <cstdint>

esp_err_t espnow_init(void);

esp_err_t espnow_send_data(const uint8_t *data, size_t len);
