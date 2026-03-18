#include <stdio.h>
#include "wifi.h"
#include "espnow.h"

extern "C" void app_main(void)
{
    ESP_ERROR_CHECK(wifi_init());
    ESP_ERROR_CHECK(espnow_init());
}
