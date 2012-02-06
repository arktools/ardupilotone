 
add_definitions(    -D'CPU_FREQ=(16000000L)'
                    -D__linux__=1
                    -D__AVR__=1
                    -D__AVR_ATmega1280__=1
                    -D_PROGMEM
                    -D__STDC_VERSION__=199901L
                    -std=gnu99
                    -D'WIZ_AUTOGEN'
                    -D'ARCH=(ARCH_DEFAULT)'
                    -mmcu=atmega1280
                    -MMD -MP
                    )

include_directories("${CMAKE_SOURCE_DIR}/bertos")
include_directories("${CMAKE_SOURCE_DIR}/bertos/cpu/avr")

set_property(SOURCE ${CMAKE_SOURCE_DIR}/bertos/cpu/avr/hw/switch_ctx_avr.S
                    PROPERTY LANGUAGE CXX)
