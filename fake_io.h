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
    // TODO: check the board and complete me
    double BOTTOM_VOLTAGE;
    double TOP_VOLTAGE;
    double PORT_OUT_VOLTAGE;
    double PORT_IN_VOLTAGE;
} SystemInputState;

typedef struct {
    // TODO: check the board and complete me
    PIN_STATE MOS_1;
} SystemOutputState;

void print_pin_state(char* label, PIN_STATE pin_state);

#endif //DIRTMATE_BATTERY_FIRMWARE_TEST_FAKE_IO_H
