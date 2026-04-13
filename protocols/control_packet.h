#include "cstdint"

struct ControlPacket
{
    uint16_t packet_id;
    uint16_t throttle;
    int16_t yaw;
    int16_t pitch;
    int16_t roll;
    uint8_t buttons;
};