//
// Created by Jye Lewis on 26/2/2023.
//

#include "update_system_state.h"
#include "fake_io.h"

void update_system_state(SystemInputState* input_state, SystemOutputState* output_state) {
    if (input_state->BOTTOM_VOLTAGE > input_state->TOP_VOLTAGE) {
        output_state->MOS_1 = LOW;
    } else {
        output_state->MOS_1 = HIGH;
    }
}