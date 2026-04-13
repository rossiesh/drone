#include "cstdint"

struct TelemetryPacket
{
    uint16_t received_packet_id;
    uint16_t consumed_mah;
    uint16_t battery_mv;
    uint8_t esc_temperature;
    int8_t rssi_at_fc;
};