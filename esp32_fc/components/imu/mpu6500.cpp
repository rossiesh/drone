#include "mpu6500.h"
#include "driver/spi_master.h"
#include "esp_err.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define PIN_NUM_CLK 7
#define PIN_NUM_MISO 8
#define PIN_NUM_MOSI 9
#define PIN_NUM_CS 44

struct GyroOffset
{
  int16_t g_x_offset;
  int16_t g_y_offset;
  int16_t g_z_offset;
};

static spi_device_handle_t imu_handle;
static const char *TAG = "mpu6500";
static GyroOffset gyro_offset = {0};

static const uint8_t BURST_READ_START_REGISTER = 0x3B;
static const uint8_t WHO_AM_I_REGISTER = 0x75;
static const uint8_t SIGNAL_PATH_RESET_REGISTER = 0x68;
static const uint8_t PWR_MGMT_1_REGISTER = 0x6B;
static const uint8_t PWR_MGMT_2_REGISTER = 0x6C;

static const uint8_t PWR_MGMT_1_DEVICE_RESET=0x80;
static const uint8_t SIGNAL_PATH_RESET_ALL=0x07;
static const uint8_t PWR_MGMT_1_CLKSEL=0x01;
static const uint8_t PWR_MGMT_2_ENABLE_ALL_AXES=0x00;
static const uint8_t BURST_READ_TRANSFER_LENGTH = 15;
static const uint8_t READ_WRITE_TRANSFER_LENGTH = 2;
static const uint8_t EXPECTED_WHO_AM_I = 0x70;

static esp_err_t read_register(uint8_t reg, uint8_t &value)
{
  uint8_t tx_buffer[READ_WRITE_TRANSFER_LENGTH] = {static_cast<uint8_t>(reg | 0x80), 0x00};
  uint8_t rx_buffer[READ_WRITE_TRANSFER_LENGTH] = {0};
  spi_transaction_t transaction = {};
  transaction.length = READ_WRITE_TRANSFER_LENGTH * 8;
  transaction.tx_buffer = tx_buffer;
  transaction.rx_buffer = rx_buffer;
  ESP_ERROR_CHECK(spi_device_polling_transmit(imu_handle, &transaction));
  value = rx_buffer[1];
  return ESP_OK;
}

static esp_err_t write_register(uint8_t reg, uint8_t value)
{
  uint8_t tx_buffer[READ_WRITE_TRANSFER_LENGTH] = {reg, value};
  spi_transaction_t transaction = {};
  transaction.length = READ_WRITE_TRANSFER_LENGTH * 8;
  transaction.tx_buffer = tx_buffer;
  ESP_ERROR_CHECK(spi_device_polling_transmit(imu_handle, &transaction));
  return ESP_OK;
}

static esp_err_t read_raw_sample(ImuData &imu_data)
{
  uint8_t tx_buffer[BURST_READ_TRANSFER_LENGTH] = {0};
  uint8_t rx_buffer[BURST_READ_TRANSFER_LENGTH] = {0};
  tx_buffer[0] = BURST_READ_START_REGISTER | 0x80;
  spi_transaction_t transaction = {0};
  transaction.length = BURST_READ_TRANSFER_LENGTH * 8;
  transaction.tx_buffer = tx_buffer;
  transaction.rx_buffer = rx_buffer;
  ESP_ERROR_CHECK(spi_device_polling_transmit(imu_handle, &transaction));
  imu_data.a_x = (rx_buffer[1] << 8) | rx_buffer[2];
  imu_data.a_y = (rx_buffer[3] << 8) | rx_buffer[4];
  imu_data.a_z = (rx_buffer[5] << 8) | rx_buffer[6];
  imu_data.temp = (rx_buffer[7] << 8) | rx_buffer[8];
  imu_data.g_x = (rx_buffer[9] << 8) | rx_buffer[10];
  imu_data.g_y = (rx_buffer[11] << 8) | rx_buffer[12];
  imu_data.g_z = (rx_buffer[13] << 8) | rx_buffer[14];
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

  uint8_t who_am_i = 0x00;
  ESP_ERROR_CHECK(read_register(WHO_AM_I_REGISTER, who_am_i));
  if (who_am_i != EXPECTED_WHO_AM_I)
  {
    return ESP_ERR_INVALID_RESPONSE;
  }

  ESP_ERROR_CHECK(write_register(PWR_MGMT_1_REGISTER, PWR_MGMT_1_DEVICE_RESET));
  vTaskDelay(pdMS_TO_TICKS(100));
  ESP_ERROR_CHECK(write_register(SIGNAL_PATH_RESET_REGISTER, SIGNAL_PATH_RESET_ALL));
  vTaskDelay(pdMS_TO_TICKS(100));
  ESP_ERROR_CHECK(write_register(PWR_MGMT_1_REGISTER, PWR_MGMT_1_CLKSEL));
  vTaskDelay(pdMS_TO_TICKS(100));
  ESP_ERROR_CHECK(write_register(PWR_MGMT_2_REGISTER, PWR_MGMT_2_ENABLE_ALL_AXES));
  return ESP_OK;
}

esp_err_t mpu6500_calibrate_gyro(void)
{
  int32_t g_x_sum = 0;
  int32_t g_y_sum = 0;
  int32_t g_z_sum = 0;
  ImuData imu_data = {0};

  for (int i = 0; i < 200; i++)
  {
    ESP_ERROR_CHECK(read_raw_sample(imu_data));
    g_x_sum += imu_data.g_x;
    g_y_sum += imu_data.g_y;
    g_z_sum += imu_data.g_z;
    vTaskDelay(pdMS_TO_TICKS(20));
  }

  gyro_offset.g_x_offset = g_x_sum / 200;
  gyro_offset.g_y_offset = g_y_sum / 200;
  gyro_offset.g_z_offset = g_z_sum / 200;
  return ESP_OK;
}

esp_err_t mpu6500_read_data(ImuData &imu_data)
{
  ESP_ERROR_CHECK(read_raw_sample(imu_data));
  imu_data.g_x = imu_data.g_x - gyro_offset.g_x_offset;
  imu_data.g_y = imu_data.g_y - gyro_offset.g_y_offset;
  imu_data.g_z = imu_data.g_z - gyro_offset.g_z_offset;
  return ESP_OK;
}
