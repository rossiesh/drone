#include <stdio.h>
#include "wifi.h"

extern "C" void app_main(void)
{
    ESP_ERROR_CHECK(wifi_init());
}
