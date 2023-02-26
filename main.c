#include <stdio.h>
#include <memory.h>
#include "fake_io.h"
#include "update_system_state.h"

void run_test(char* test_name, SystemInputState input_state, SystemOutputState expected_output_state) {
    SystemOutputState actual_output_state = {
        .MOS_1 = FLOATING
    };
    update_system_state(&input_state, &actual_output_state);
    if (memcmp(&actual_output_state, &expected_output_state, sizeof(SystemOutputState)) == 0) {
        // test passed
        printf("Test: %s PASSED\n", test_name);
        return;
    }

    // test failed :(
    printf("Test: %s FAILED\n", test_name);
    if (expected_output_state.MOS_1 != actual_output_state.MOS_1) {
        print_pin_state("\tExpected MOS_1 to be", expected_output_state.MOS_1);
        print_pin_state("\tBut it was", actual_output_state.MOS_1);
    }
}

int main() {
    run_test(
            "Dummy test",
            (SystemInputState){
                .BOTTOM_VOLTAGE = 0.1,
                .TOP_VOLTAGE = 0.3,
                .PORT_IN_VOLTAGE = 0.5,
                .PORT_OUT_VOLTAGE = 0.7
        },
    (SystemOutputState){
                .MOS_1 = HIGH
        }
    );

    return 0;
}
