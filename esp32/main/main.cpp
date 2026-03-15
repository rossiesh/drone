#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "wifi.h"

/* static constexpr gpio_num_t L1 = GPIO_NUM_9;
static constexpr gpio_num_t L2 = GPIO_NUM_8;
static constexpr gpio_num_t L3 = GPIO_NUM_7;

static void init_out(gpio_num_t pin)
{
    gpio_config_t io_conf = {};

    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = (1ULL << pin);
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;

    gpio_config(&io_conf);
    gpio_set_level(pin, 0);
} */

extern "C" void app_main(void)
{
    wifi_start_softap();
    /* init_out(L1);
    init_out(L2);
    init_out(L3);
    int count = 1;
    int delay = 300;

    while (count != 100)
    {
        gpio_set_level(L1, 1);
        vTaskDelay(pdMS_TO_TICKS(delay));
        gpio_set_level(L1, 0);
        vTaskDelay(pdMS_TO_TICKS(delay));

        gpio_set_level(L2, 1);
        vTaskDelay(pdMS_TO_TICKS(delay));
        gpio_set_level(L2, 0);
        vTaskDelay(pdMS_TO_TICKS(delay));

        gpio_set_level(L3, 1);
        vTaskDelay(pdMS_TO_TICKS(delay));
        gpio_set_level(L3, 0);
        vTaskDelay(pdMS_TO_TICKS(delay));

        printf("%d\n", count);
        count++;
    } */
}