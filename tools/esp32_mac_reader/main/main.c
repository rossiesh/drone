#include "esp_err.h"
#include "esp_log.h"
#include "esp_mac.h"

void app_main(void)
{
    static const char *TAG = "mac_reader";
    uint8_t mac_address[6] = {0};
    ESP_ERROR_CHECK(esp_read_mac(mac_address, ESP_MAC_WIFI_STA));
    ESP_LOGI(
        TAG,
        "STA MAC: %02X:%02X:%02X:%02X:%02X:%02X",
        mac_address[0], mac_address[1], mac_address[2], mac_address[3], mac_address[4], mac_address[5]);
}
