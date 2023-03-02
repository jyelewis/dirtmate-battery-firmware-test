#include <stdio.h>
#include <memory.h>
#include "fake_io.h"
#include "update_system_state.h"

void run_test(char *test_name, SystemInputState input_state, SystemOutputState expected_output_state) {
    SystemOutputState actual_output_state = {
            .top_output_enable = FLOATING,
            .bottom_output_enable = FLOATING,
            .port1_output_enable = FLOATING,
            .port2_output_enable = FLOATING,
    };
    update_system_state(&input_state, &actual_output_state);
    if (memcmp(&actual_output_state, &expected_output_state, sizeof(SystemOutputState)) == 0) {
        // test passed
        printf("Test: %s PASSED\n", test_name);
        return;
    }

    // test failed :(
    printf("\tTest: %s FAILED\n", test_name);
    if (expected_output_state.top_output_enable != actual_output_state.top_output_enable) {
        print_pin_state("\tExpected top_output_enable to be", expected_output_state.top_output_enable);
        print_pin_state("\tBut it was", actual_output_state.top_output_enable);
    }

    printf("\tTest: %s FAILED\n", test_name);
    if (expected_output_state.bottom_output_enable != actual_output_state.bottom_output_enable) {
        print_pin_state("\tExpected bottom_output_enable to be", expected_output_state.bottom_output_enable);
        print_pin_state("\tBut it was", actual_output_state.bottom_output_enable);
    }

    printf("\tTest: %s FAILED\n", test_name);
    if (expected_output_state.port1_output_enable != actual_output_state.port1_output_enable) {
        print_pin_state("\tExpected port1_output_enable to be", expected_output_state.port1_output_enable);
        print_pin_state("\tBut it was", actual_output_state.port1_output_enable);
    }

    printf("\tTest: %s FAILED\n", test_name);
    if (expected_output_state.port2_output_enable != actual_output_state.port2_output_enable) {
        print_pin_state("\tExpected port2_output_enable to be", expected_output_state.port2_output_enable);
        print_pin_state("\tBut it was", actual_output_state.port2_output_enable);
    }
}

int main() {
    run_test(
            "Nothing connected",
            (SystemInputState) {
                    .internal_battery_voltage = 1.0,

                    .top_state_bool_low = 0.0,
                    .top_state_bool_high = 0.0,

                    .bottom_state_bool_low = 0.0,
                    .bottom_state_bool_high = 0.0,

                    .port1_state_bool_low = 0.0,
                    .port1_state_bool_high = 0.0,

                    .port2_state_bool_low = 0.0,
                    .port2_state_bool_high = 0.0,
            },
            (SystemOutputState) {
                    .top_output_enable = LOW,
                    .bottom_output_enable = LOW,
                    .port1_output_enable = LOW,
                    .port2_output_enable = LOW,
            }
    );

    run_test(
            "Puck connected via top port, no input sources, battery is full",
            (SystemInputState) {
                    .internal_battery_voltage = 1.0,

                    .top_state_bool_low = 1.0,
                    .top_state_bool_high = 0.0,

                    .bottom_state_bool_low = 0.0,
                    .bottom_state_bool_high = 0.0,

                    .port1_state_bool_low = 0.0,
                    .port1_state_bool_high = 0.0,

                    .port2_state_bool_low = 0.0,
                    .port2_state_bool_high = 0.0,
            },
            (SystemOutputState) {
                    .top_output_enable = HIGH,
                    .bottom_output_enable = LOW,
                    .port1_output_enable = LOW,
                    .port2_output_enable = LOW,
            }
    );

    run_test(
            "Puck connected via port 1, no input sources, battery is full",
            (SystemInputState) {
                    .internal_battery_voltage = 1.0,

                    .top_state_bool_low = 0.0,
                    .top_state_bool_high = 0.0,

                    .bottom_state_bool_low = 0.0,
                    .bottom_state_bool_high = 0.0,

                    .port1_state_bool_low = 1.0,
                    .port1_state_bool_high = 0.0,

                    .port2_state_bool_low = 0.0,
                    .port2_state_bool_high = 0.0,
            },
            (SystemOutputState) {
                    .top_output_enable = LOW,
                    .bottom_output_enable = LOW,
                    .port1_output_enable = HIGH,
                    .port2_output_enable = LOW,
            }
    );

    run_test(
            "Puck connected via port 2, no input sources, battery is full",
            (SystemInputState) {
                    .internal_battery_voltage = 1.0,

                    .top_state_bool_low = 0.0,
                    .top_state_bool_high = 0.0,

                    .bottom_state_bool_low = 0.0,
                    .bottom_state_bool_high = 0.0,

                    .port1_state_bool_low = 0.0,
                    .port1_state_bool_high = 0.0,

                    .port2_state_bool_low = 1.0,
                    .port2_state_bool_high = 0.0,
            },
            (SystemOutputState) {
                    .top_output_enable = LOW,
                    .bottom_output_enable = LOW,
                    .port1_output_enable = LOW,
                    .port2_output_enable = HIGH,
            }
    );

    run_test(
            "Puck connected via top pins, no input sources, battery is 50%",
            (SystemInputState) {
                    .internal_battery_voltage = 0.5,

                    .top_state_bool_low = 1.0,
                    .top_state_bool_high = 0.0,

                    .bottom_state_bool_low = 0.0,
                    .bottom_state_bool_high = 0.0,

                    .port1_state_bool_low = 0.0,
                    .port1_state_bool_high = 0.0,

                    .port2_state_bool_low = 0.0,
                    .port2_state_bool_high = 0.0,
            },
            (SystemOutputState) {
                    .top_output_enable = HIGH,
                    .bottom_output_enable = LOW,
                    .port1_output_enable = LOW,
                    .port2_output_enable = LOW,
            }
    );

    run_test(
            "Puck Not Connected, Battery Connected via Bottom Pins, battery is full",
            (SystemInputState) {
                    .internal_battery_voltage = 1.0,

                    .top_state_bool_low = 0.0,
                    .top_state_bool_high = 0.0,

                    .bottom_state_bool_low = 1.0,
                    .bottom_state_bool_high = 1.0,

                    .port1_state_bool_low = 0.0,
                    .port1_state_bool_high = 0.0,

                    .port2_state_bool_low = 0.0,
                    .port2_state_bool_high = 0.0,
            },
            (SystemOutputState) {
                    .top_output_enable = LOW,
                    .bottom_output_enable = HIGH,
                    .port1_output_enable = LOW,
                    .port2_output_enable = LOW,
            }
    );

    run_test(
            "Puck Not Connected, Battery Connected via Bottom Pins, battery is at 60%",
            (SystemInputState) {
                    .internal_battery_voltage = 0.6,

                    .top_state_bool_low = 0.0,
                    .top_state_bool_high = 0.0,

                    .bottom_state_bool_low = 1.0,
                    .bottom_state_bool_high = 1.0,

                    .port1_state_bool_low = 0.0,
                    .port1_state_bool_high = 0.0,

                    .port2_state_bool_low = 0.0,
                    .port2_state_bool_high = 0.0,
            },
            (SystemOutputState) {
                    .top_output_enable = LOW,
                    .bottom_output_enable = LOW,
                    .port1_output_enable = LOW,
                    .port2_output_enable = LOW,
            }
    );

    run_test(
            "Puck Connected, Battery Connected via Bottom Pins, battery is at 40%",
            (SystemInputState) {
                    .internal_battery_voltage = 0.4,

                    .top_state_bool_low = 1.0,
                    .top_state_bool_high = 0.0,

                    .bottom_state_bool_low = 1.0,
                    .bottom_state_bool_high = 1.0,

                    .port1_state_bool_low = 0.0,
                    .port1_state_bool_high = 0.0,

                    .port2_state_bool_low = 0.0,
                    .port2_state_bool_high = 0.0,
            },
            (SystemOutputState) {
                    .top_output_enable = HIGH,
                    .bottom_output_enable = LOW,
                    .port1_output_enable = LOW,
                    .port2_output_enable = LOW,
            }
    );

    run_test(
            "Puck Connected, Aux Device in Port 1, battery is full",
            (SystemInputState) {
                    .internal_battery_voltage = 1.0,

                    .top_state_bool_low = 1.0,
                    .top_state_bool_high = 0.0,

                    .bottom_state_bool_low = 0.0,
                    .bottom_state_bool_high = 0.0,

                    .port1_state_bool_low = 0.0,
                    .port1_state_bool_high = 1.0,

                    .port2_state_bool_low = 0.0,
                    .port2_state_bool_high = 0.0,
            },
            (SystemOutputState) {
                    .top_output_enable = HIGH,
                    .bottom_output_enable = LOW,
                    .port1_output_enable = HIGH,
                    .port2_output_enable = LOW,
            }
    );

    run_test(
            "Puck Connected, Aux Device in Port 1, battery is 40%",
            (SystemInputState) {
                    .internal_battery_voltage = 0.4,

                    .top_state_bool_low = 1.0,
                    .top_state_bool_high = 0.0,

                    .bottom_state_bool_low = 0.0,
                    .bottom_state_bool_high = 0.0,

                    .port1_state_bool_low = 0.0,
                    .port1_state_bool_high = 1.0,

                    .port2_state_bool_low = 0.0,
                    .port2_state_bool_high = 0.0,
            },
            (SystemOutputState) {
                    .top_output_enable = HIGH,
                    .bottom_output_enable = LOW,
                    .port1_output_enable = LOW,
                    .port2_output_enable = LOW,
            }
    );

    run_test(
            "Puck connected on top, second battery bottom pins, ext obj port 1, second puck port 2, battery is full",
            (SystemInputState) {
                    .internal_battery_voltage = 1.0,

                    .top_state_bool_low = 1.0,
                    .top_state_bool_high = 0.0,

                    .bottom_state_bool_low = 1.0,
                    .bottom_state_bool_high = 1.0,

                    .port1_state_bool_low = 0.0,
                    .port1_state_bool_high = 1.0,

                    .port2_state_bool_low = 1.0,
                    .port2_state_bool_high = 0.0,
            },
            (SystemOutputState) {
                    .top_output_enable = HIGH,
                    .bottom_output_enable = HIGH,
                    .port1_output_enable = HIGH,
                    .port2_output_enable = HIGH,
            }
    );

    run_test(
            "Puck connected on top, second battery bottom pins, ext obj port 1, second puck port 2, battery is 70%",
            (SystemInputState) {
                    .internal_battery_voltage = 0.7,

                    .top_state_bool_low = 1.0,
                    .top_state_bool_high = 0.0,

                    .bottom_state_bool_low = 1.0,
                    .bottom_state_bool_high = 1.0,

                    .port1_state_bool_low = 0.0,
                    .port1_state_bool_high = 1.0,

                    .port2_state_bool_low = 1.0,
                    .port2_state_bool_high = 0.0,
            },
            (SystemOutputState) {
                    .top_output_enable = HIGH,
                    .bottom_output_enable = LOW,
                    .port1_output_enable = HIGH,
                    .port2_output_enable = HIGH,
            }
    );

    run_test(
            "Puck connected on top, second battery bottom pins, ext obj port 1, second puck port 2, battery is 40%",
            (SystemInputState) {
                    .internal_battery_voltage = 0.4,

                    .top_state_bool_low = 1.0,
                    .top_state_bool_high = 0.0,

                    .bottom_state_bool_low = 1.0,
                    .bottom_state_bool_high = 1.0,

                    .port1_state_bool_low = 0.0,
                    .port1_state_bool_high = 1.0,

                    .port2_state_bool_low = 1.0,
                    .port2_state_bool_high = 0.0,
            },
            (SystemOutputState) {
                    .top_output_enable = HIGH,
                    .bottom_output_enable = LOW,
                    .port1_output_enable = LOW,
                    .port2_output_enable = HIGH,
            }
    );

    run_test(
            "Puck connected on top, second battery bottom pins, ext obj port 1, second puck port 2, battery is 10%",
            (SystemInputState) {
                    .internal_battery_voltage = 0.1,

                    .top_state_bool_low = 1.0,
                    .top_state_bool_high = 0.0,

                    .bottom_state_bool_low = 1.0,
                    .bottom_state_bool_high = 1.0,

                    .port1_state_bool_low = 0.0,
                    .port1_state_bool_high = 1.0,

                    .port2_state_bool_low = 1.0,
                    .port2_state_bool_high = 0.0,
            },
            (SystemOutputState) {
                    .top_output_enable = LOW,
                    .bottom_output_enable = LOW,
                    .port1_output_enable = LOW,
                    .port2_output_enable = LOW,
            }
    );

    run_test(
            "Battery connected on top, second battery bottom pins, ext obj port 1, puck port 2, battery is full",
            (SystemInputState) {
                    .internal_battery_voltage = 1.0,

                    .top_state_bool_low = 1.0,
                    .top_state_bool_high = 1.0,

                    .bottom_state_bool_low = 1.0,
                    .bottom_state_bool_high = 1.0,

                    .port1_state_bool_low = 0.0,
                    .port1_state_bool_high = 1.0,

                    .port2_state_bool_low = 1.0,
                    .port2_state_bool_high = 0.0,
            },
            (SystemOutputState) {
                    .top_output_enable = HIGH,
                    .bottom_output_enable = LOW,
                    .port1_output_enable = HIGH,
                    .port2_output_enable = HIGH,
            }
    );

    run_test(
            "Full Battery connected on top, second battery bottom pins, ext obj port 1, puck port 2, battery is 70%",
            (SystemInputState) {
                    .internal_battery_voltage = 0.7,

                    .top_state_bool_low = 0.0,
                    .top_state_bool_high = 0.0,

                    .bottom_state_bool_low = 1.0,
                    .bottom_state_bool_high = 1.0,

                    .port1_state_bool_low = 0.0,
                    .port1_state_bool_high = 1.0,

                    .port2_state_bool_low = 1.0,
                    .port2_state_bool_high = 0.0,
            },
            (SystemOutputState) {
                    .top_output_enable = LOW,
                    .bottom_output_enable = LOW,
                    .port1_output_enable = HIGH,
                    .port2_output_enable = HIGH,
            }
    );

    run_test(
            "Battery connected on top, second battery bottom pins, ext obj port 1, puck port 2, battery is 40%",
            (SystemInputState) {
                    .internal_battery_voltage = 0.4,

                    .top_state_bool_low = 1.0,
                    .top_state_bool_high = 1.0,

                    .bottom_state_bool_low = 1.0,
                    .bottom_state_bool_high = 1.0,

                    .port1_state_bool_low = 0.0,
                    .port1_state_bool_high = 1.0,

                    .port2_state_bool_low = 1.0,
                    .port2_state_bool_high = 0.0,
            },
            (SystemOutputState) {
                    .top_output_enable = LOW,
                    .bottom_output_enable = LOW,
                    .port1_output_enable = LOW,
                    .port2_output_enable = HIGH,
            }
    );

    run_test(
            "Battery connected on top, second battery bottom pins, ext obj port 1, puck port 2, battery is 10%",
            (SystemInputState) {
                    .internal_battery_voltage = 0.1,

                    .top_state_bool_low = 1.0,
                    .top_state_bool_high = 1.0,

                    .bottom_state_bool_low = 1.0,
                    .bottom_state_bool_high = 1.0,

                    .port1_state_bool_low = 0.0,
                    .port1_state_bool_high = 1.0,

                    .port2_state_bool_low = 1.0,
                    .port2_state_bool_high = 0.0,
            },
            (SystemOutputState) {
                    .top_output_enable = LOW,
                    .bottom_output_enable = LOW,
                    .port1_output_enable = LOW,
                    .port2_output_enable = LOW,
            }
    );

    return 0;
}
