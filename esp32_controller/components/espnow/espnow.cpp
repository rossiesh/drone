#include "control_packet.h"
#include "telemetry_packet.h"
#include "espnow.h"
#include "esp_err.h"
#include "esp_log.h"
#include "esp_now.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <cstring>

static uint8_t mac_address_fc[ESP_NOW_ETH_ALEN] = {0x10, 0x20, 0xBA, 0x03, 0xBB, 0x80};
static const char *TAG = "espnow";

void espnow_send_cb(const esp_now_send_info_t *tx_info, esp_now_send_status_t status)
{
    uint8_t *mac = tx_info->des_addr;
    ESP_LOGI(
        TAG,
        "sent to %02X:%02X:%02X:%02X:%02X:%02X, %s",
        mac[0], mac[1], mac[2], mac[3], mac[4], mac[5],
        status == ESP_NOW_SEND_SUCCESS ? "success" : "fail");
}

void espnow_recv_cb(const esp_now_recv_info_t *recv_info, const uint8_t *data, int len)
{
    ESP_LOGI(TAG, "%s", "received");
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
    std::memcpy(peer.peer_addr, mac_address_fc, ESP_NOW_ETH_ALEN);
    ESP_ERROR_CHECK(esp_now_add_peer(&peer));
    esp_now_rate_config_t rate_config = {};
    rate_config.phymode = WIFI_PHY_MODE_LR;
    rate_config.rate = WIFI_PHY_RATE_LORA_250K;
    rate_config.ersu = false;
    rate_config.dcm = false;
    ESP_ERROR_CHECK(esp_now_set_peer_rate_config(mac_address_fc, &rate_config));
    return ESP_OK;
}

esp_err_t espnow_send_data(const uint8_t *data, size_t len)
{
    ESP_ERROR_CHECK(esp_now_send(mac_address_fc, data, len));
    return ESP_OK;
}
