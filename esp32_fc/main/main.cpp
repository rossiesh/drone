#include <stdio.h>
#include "wifi.h"
#include "espnow.h"
#include "mpu6500.h"

extern "C" void app_main(void)
{
    ESP_ERROR_CHECK(wifi_init());
    ESP_ERROR_CHECK(espnow_init());
    ESP_ERROR_CHECK(mpu6500_init());
}
