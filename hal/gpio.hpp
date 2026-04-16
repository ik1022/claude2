#pragma once
// MCU-agnostic GPIO HAL interface.
// Implementations live in hal/<mcu>/gpio.cpp.

#include <cstdint>

namespace hal
{
    namespace gpio
    {

        enum class Port : uint8_t
        {
            PA = 0,
            PB,
            PC,
            PD,
            PE,
            PF
        };
        enum class Pin : uint8_t
        {
            P0 = 0,
            P1,
            P2,
            P3,
            P4,
            P5,
            P6,
            P7,
            P8,
            P9,
            P10,
            P11,
            P12,
            P13,
            P14,
            P15
        };
        enum class Mode : uint8_t
        {
            Input,
            OutputPushPull,
            OutputOpenDrain,
            Analog,
            AltFunc
        };
        enum class Pull : uint8_t
        {
            None,
            Up,
            Down
        };

        // Enable the GPIO port clock (call before configure).
        void enable_clock(Port port);

        // Configure a single pin.
        void configure(Port port, Pin pin, Mode mode, Pull pull = Pull::None);

        // Output control (only valid for output modes).
        void set(Port port, Pin pin);
        void clear(Port port, Pin pin);
        void toggle(Port port, Pin pin);

        // Read input level.
        bool read(Port port, Pin pin);

    } // namespace gpio
} // namespace hal
