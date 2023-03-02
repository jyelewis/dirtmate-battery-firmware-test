//
// Created by Jye Lewis on 26/2/2023.
//

#include <printf.h>
#include <stdbool.h>
#include "update_system_state.h"
#include "fake_io.h"

#define LOW_BATTERY_PERCENTAGE 0.2
#define HALF_BATTERY_PERCENTAGE 0.5
#define HIGH_BATTERY_PERCENTAGE 0.8
#define FULL_BATTERY_PERCENTAGE 1 

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
    CONNECTED_DEVICE_STATE bottom_port_state = read_connected_device_state(input_state->bottom_state_bool_high, input_state->bottom_state_bool_low);
    CONNECTED_DEVICE_STATE port1_state = read_connected_device_state(input_state->port1_state_bool_high, input_state->port1_state_bool_low);
    CONNECTED_DEVICE_STATE port2_state = read_connected_device_state(input_state->port2_state_bool_high, input_state->port2_state_bool_low);
    double battery_percentage = input_state -> internal_battery_voltage;

    output_state->top_output_enable = LOW;
    output_state->bottom_output_enable = LOW;
    output_state->port1_output_enable = LOW;
    output_state->port2_output_enable = LOW;

    int is_charging_external_battery = false;

//Top Pins - Battery, Puck or Off
    if (top_port_state == PORT_STATE_PUCK && battery_percentage >= LOW_BATTERY_PERCENTAGE) {
        output_state->top_output_enable = HIGH;
     }else if (top_port_state == PORT_STATE_EXTERNAL_BATTERY_REQUESTING_POWER && battery_percentage >= HIGH_BATTERY_PERCENTAGE && is_charging_external_battery == false){
        output_state->top_output_enable = HIGH;
        is_charging_external_battery = true;
        //maybe combine these two into one
    }
//Bottom Pins - Battery, Off, Managing Two Batteries
    if(bottom_port_state == PORT_STATE_EXTERNAL_BATTERY_REQUESTING_POWER && battery_percentage >= HIGH_BATTERY_PERCENTAGE && is_charging_external_battery == false) {
        output_state->bottom_output_enable = HIGH;
        is_charging_external_battery = true;
    } 

    // Port 1 - Puck or Auxiliary Power
    if (port1_state == PORT_STATE_PUCK && battery_percentage > LOW_BATTERY_PERCENTAGE) {
        output_state->port1_output_enable = HIGH;
    }else if (port1_state == PORT_STATE_AUX && battery_percentage >= HALF_BATTERY_PERCENTAGE) {
        output_state->port1_output_enable = HIGH;
    }
    // Port 2 - Puck or Auxiliary Power
    if(port2_state == PORT_STATE_AUX && battery_percentage >= HALF_BATTERY_PERCENTAGE) {
        output_state->port2_output_enable = HIGH;
        // Is it worth adding another statement turning both on at the same time?
    }else if (port2_state == PORT_STATE_PUCK && battery_percentage >= LOW_BATTERY_PERCENTAGE) {
        output_state->port2_output_enable = HIGH;
    } 

        if (battery_percentage <= LOW_BATTERY_PERCENTAGE ) {
        return;
        // Keeps all ports off
    } 
} 
    
  
    
    




