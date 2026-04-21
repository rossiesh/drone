#include <stdio.h>
#include "wifi.h"
#include "espnow.h"
#include "esp_log.h"
#include "mpu6500.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *TAG = "mpu6500";

extern "C" void app_main(void)
{
    ESP_ERROR_CHECK(wifi_init());
    ESP_ERROR_CHECK(espnow_init());
    ESP_ERROR_CHECK(mpu6500_init());
    ESP_ERROR_CHECK(mpu6500_calibrate_gyro());
    ImuData imu_data = {0};
    while (true)
    {
        ESP_ERROR_CHECK(mpu6500_read_data(imu_data));
        ESP_LOGI(TAG, "a_x:%6d a_y=%6d a_z=%6d temp=%6d g_x=%6d g_y=%6d g_z=%6d", imu_data.a_x, imu_data.a_y, imu_data.a_z, imu_data.temp, imu_data.g_x, imu_data.g_y, imu_data.g_z);
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}
