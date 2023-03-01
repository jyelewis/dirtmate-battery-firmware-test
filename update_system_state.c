//
// Created by Jye Lewis on 26/2/2023.
//

#include <printf.h>
#include "update_system_state.h"
#include "fake_io.h"

typedef enum {
    // 0: no device / input power
    PORT_STATE_NO_DEVICE = 0,
    // 1: puck connected
    PORT_STATE_PUCK = 1,
    // 2: aux connected
    PORT_STATE_AUX = 2,
    // 3: external battery connected & requesting power
    PORT_STATE_EXTERNAL_BATTERY_REQUESTING_POWER = 3
} CONNECTED_DEVICE_STATE;

CONNECTED_DEVICE_STATE read_connected_device_state(float high_bit, float low_bit) {
    CONNECTED_DEVICE_STATE state = 0;
    if (high_bit > 0.8) {
        state += 2;
    }
    if (low_bit > 0.8) {
        state += 1;
    }

    return state;
}

void update_system_state(SystemInputState* input_state, SystemOutputState* output_state) {
    // TODO: implement me
    CONNECTED_DEVICE_STATE top_port_state = read_connected_device_state(input_state->top_state_bool_high, input_state->top_state_bool_low);
    if (top_port_state == PORT_STATE_PUCK) {
        // puck is connected to top port
        output_state->top_output_enable = HIGH;
        output_state->bottom_output_enable = LOW;
        output_state->port1_output_enable = LOW;
        output_state->port2_output_enable = LOW;
    } else {
        // nothing connected
        output_state->top_output_enable = LOW;
        output_state->bottom_output_enable = LOW;
        output_state->port1_output_enable = LOW;
        output_state->port2_output_enable = LOW;
    }


}