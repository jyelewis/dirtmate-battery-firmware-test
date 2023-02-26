cmake_minimum_required(VERSION 3.24)
project(dirtmate_battery_firmware_test C)

set(CMAKE_C_STANDARD 17)

add_executable(dirtmate_battery_firmware_test main.c fake_io.c fake_io.h update_system_state.c update_system_state.h)
