#include "espnow.h"
#include "esp_err.h"
#include "esp_log.h"
#include "esp_now.h"
#include <cstring>

static uint8_t mac_address_controller[ESP_NOW_ETH_ALEN] = {0x10, 0x20, 0xBA, 0x03, 0xBF, 0x28};
static const char *TAG = "espnow";
int count = 1;

void espnow_send_cb(const esp_now_send_info_t *tx_info, esp_now_send_status_t status)
{
    ESP_LOGI(TAG, "%s", "sent");
}

void espnow_recv_cb(const esp_now_recv_info_t *recv_info, const uint8_t *data, int len)
{
    uint8_t *mac = recv_info->src_addr;
    ESP_LOGI(
        TAG,
        "[%d]: received from %02X:%02X:%02X:%02X:%02X:%02X",
        count,
        mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    count++;
}

esp_err_t espnow_init(void)
{
    ESP_ERROR_CHECK(esp_now_init());
    ESP_ERROR_CHECK(esp_now_register_send_cb(espnow_send_cb));
    ESP_ERROR_CHECK(esp_now_register_recv_cb(espnow_recv_cb));
    esp_now_peer_info_t peer = {};
    peer.channel = 1;
    peer.encrypt = false;
    peer.ifidx = WIFI_IF_STA;
    std::memcpy(peer.peer_addr, mac_address_controller, ESP_NOW_ETH_ALEN);
    ESP_ERROR_CHECK(esp_now_add_peer(&peer));
    esp_now_rate_config_t rate_config = {};
    rate_config.phymode = WIFI_PHY_MODE_LR;
    rate_config.rate = WIFI_PHY_RATE_LORA_250K;
    rate_config.ersu = false;
    rate_config.dcm = false;
    ESP_ERROR_CHECK(esp_now_set_peer_rate_config(mac_address_controller, &rate_config));
    return ESP_OK;
}
