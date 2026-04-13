#include <stdio.h>
#include "control_packet.h"
#include "wifi.h"
#include "espnow.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

void setup_gpio_pin(gpio_num_t gpio_num)
{
    gpio_config_t io_conf = {
        .pin_bit_mask = 1ULL << gpio_num,
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    ESP_ERROR_CHECK(gpio_config(&io_conf));
}

extern "C" void app_main(void)
{
    static const char *TAG = "button_num";

    ESP_ERROR_CHECK(wifi_init());
    ESP_ERROR_CHECK(espnow_init());

    gpio_num_t button_1 = GPIO_NUM_4;
    gpio_num_t button_2 = GPIO_NUM_43;
    gpio_num_t button_3 = GPIO_NUM_6;
    gpio_num_t button_4 = GPIO_NUM_5;

    setup_gpio_pin(button_1);
    setup_gpio_pin(button_2);
    setup_gpio_pin(button_3);
    setup_gpio_pin(button_4);

    uint8_t test_data[] = "ping";
    // ESP_ERROR_CHECK(espnow_send_data(test_data, sizeof(test_data)));
    while (true)
    {
        if (gpio_get_level(button_1) == 0)
        {
            ESP_ERROR_CHECK(espnow_send_data(test_data, sizeof(test_data)));
            /* ControlPacket control_data={
                .packet_id=1,
                .throttle=200,
                .yaw=0,
                .pitch=0,
                .roll=0,
            };  */
            ESP_LOGI(TAG, "%d", 1);
               }
        if (gpio_get_level(button_2) == 0)
        {
            ESP_LOGI(TAG, "%d", 2);
        }
        if (gpio_get_level(button_3) == 0)
        {
            ESP_LOGI(TAG, "%d", 3);
        }
        if (gpio_get_level(button_4) == 0)
        {
            ESP_LOGI(TAG, "%d", 4);
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}