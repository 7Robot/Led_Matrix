# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.1)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.1.1)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
cmake_minimum_required(VERSION 3.13)


#set (CMAKE_BUILD_TYPE "Release")
set (CMAKE_BUILD_TYPE "Debug")

set(PICO_BOARD pico_w CACHE STRING "Board type")

#set (LIB_PICO_STDIO_UART "0")
set (PICO_STDIO_UART "OFF")
set(PICO_CYW43_SUPPORTED 1)

include(pico_sdk_import.cmake)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

project(PKit_Plateau_RP2040 C CXX ASM)


pico_sdk_init()

add_custom_target(invalidate_files ALL
                COMMAND ${CMAKE_COMMAND} -E touch "..\\user.c")


add_executable(PKit_Plateau_RP2040
main.c

ADC.c

BT/BT.c
BT/BT_Stdio.c

Hex_Decodeur.c
Interpreteur.c

Leds_RGB.c
Leds_RGB_Anim.c

Test_Funcs.c
user.c

Flash/Flash.c
Flash/Log_File.c
Flash/Setup_File.c

)


target_include_directories(PKit_Plateau_RP2040 PRIVATE ${CMAKE_CURRENT_LIST_DIR} )
target_include_directories(PKit_Plateau_RP2040 PRIVATE ${CMAKE_CURRENT_LIST_DIR}/BT )


# ajout du programme PIO pour ws2812 ?
pico_generate_pio_header(PKit_Plateau_RP2040 ${CMAKE_CURRENT_LIST_DIR}/ws2812.pio)

pico_enable_stdio_usb(PKit_Plateau_RP2040 1)
#pico_enable_stdio_uart(test 1)
#pico_add_extra_outputs(PKit_RP2040)
target_link_libraries(PKit_Plateau_RP2040 pico_stdlib)
#target_link_libraries(PKit_Plateau_RP2040 hardware_spi)
target_link_libraries(PKit_Plateau_RP2040 hardware_adc)
target_link_libraries(PKit_Plateau_RP2040 hardware_pwm)
target_link_libraries(PKit_Plateau_RP2040 hardware_pio)



# target_link_libraries(PKit_Plateau_RP2040 pico_cyw43_arch_none)
target_link_libraries(PKit_Plateau_RP2040 
    pico_btstack_classic
    pico_btstack_cyw43
    pico_cyw43_arch_lwip_poll)

pico_add_extra_outputs(PKit_Plateau_RP2040)
