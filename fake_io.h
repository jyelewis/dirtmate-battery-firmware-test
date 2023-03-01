//
// Created by Jye Lewis on 26/2/2023.
//

#ifndef DIRTMATE_BATTERY_FIRMWARE_TEST_FAKE_IO_H
#define DIRTMATE_BATTERY_FIRMWARE_TEST_FAKE_IO_H

typedef enum {
    HIGH,
    LOW,
    FLOATING
} PIN_STATE;

typedef struct {
    double internal_battery_voltage;

    // boolean state representations of power negotiation with each device
    // 0: no device / input power
    // 1: puck connected
    // 2: aux connected
    // 3: external battery connected & requesting power
    double top_state_bool_low;
    double top_state_bool_high;

    double bottom_state_bool_low;
    double bottom_state_bool_high;

    double port1_state_bool_low;
    double port1_state_bool_high;

    double port2_state_bool_low;
    double port2_state_bool_high;
} SystemInputState;

typedef struct {
    // all power connectors = charge in when low, battery output when high
    PIN_STATE top_output_enable;
    PIN_STATE bottom_output_enable;
    PIN_STATE port1_output_enable;
    PIN_STATE port2_output_enable;
} SystemOutputState;

void print_pin_state(char* label, PIN_STATE pin_state);

#endif //DIRTMATE_BATTERY_FIRMWARE_TEST_FAKE_IO_H
