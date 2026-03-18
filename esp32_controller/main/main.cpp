#include <stdio.h>
#include "wifi.h"
#include "espnow.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

extern "C" void app_main(void)
{
    ESP_ERROR_CHECK(wifi_init());
    ESP_ERROR_CHECK(espnow_init());

    gpio_config_t io_conf = {
        .pin_bit_mask = 1ULL << GPIO_NUM_7,
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    ESP_ERROR_CHECK(gpio_config(&io_conf));

    uint8_t test_data[] = "ping";

    while (true)
    {
        if (gpio_get_level(GPIO_NUM_7) == 0)
        {
            ESP_ERROR_CHECK(espnow_send_data(test_data, sizeof(test_data)));
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}