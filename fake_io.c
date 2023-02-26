#include <printf.h>
#include "fake_io.h"

void print_pin_state(char* label, PIN_STATE pin_state) {
    switch (pin_state) {
        case HIGH:
            printf("%s HIGH\n", label);
            break;
        case LOW:
            printf("%s LOW\n", label);
            break;
        case FLOATING:
            printf("%s FLOATING\n", label);
            break;
    }
}
