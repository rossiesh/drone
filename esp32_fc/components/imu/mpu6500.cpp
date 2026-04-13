#include "mpu6500.h"
#include "driver/spi_master.h"
#include "esp_err.h"
#include "esp_log.h"

#define PIN_NUM_CLK 7
#define PIN_NUM_MISO 8
#define PIN_NUM_MOSI 9
#define PIN_NUM_CS 44

static spi_device_handle_t imu_handle;
static const char *TAG = "mpu6500";

esp_err_t read_register(uint8_t reg, uint8_t &value)
{
  uint8_t tx_buffer[2] = {static_cast<uint8_t>(reg | 0x80), 0x00};
  uint8_t rx_buffer[2] = {0};

  spi_transaction_t transaction = {};
  transaction.length = 16;
  transaction.tx_buffer = tx_buffer;
  transaction.rx_buffer = rx_buffer;

  ESP_ERROR_CHECK(spi_device_polling_transmit(imu_handle, &transaction));

  value = rx_buffer[1];
  return ESP_OK;
}

esp_err_t mpu6500_init(void)
{
  spi_bus_config_t bus_config = {};
  bus_config.miso_io_num = PIN_NUM_MISO;
  bus_config.mosi_io_num = PIN_NUM_MOSI;
  bus_config.sclk_io_num = PIN_NUM_CLK;

  spi_device_interface_config_t device_config = {};
  device_config.clock_speed_hz = 1000000;
  device_config.mode = 0;
  device_config.spics_io_num = PIN_NUM_CS;
  device_config.queue_size = 1;

  ESP_ERROR_CHECK(spi_bus_initialize(SPI2_HOST, &bus_config, SPI_DMA_CH_AUTO));
  ESP_ERROR_CHECK(spi_bus_add_device(SPI2_HOST, &device_config, &imu_handle));

  uint8_t who_am_i = 0;
  ESP_ERROR_CHECK(read_register(0x75, who_am_i));
  ESP_LOGI(TAG, "0x%02X", who_am_i);
  return ESP_OK;
}
