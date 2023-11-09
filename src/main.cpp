#include "pico/stdlib.h"
#include "stdio.h"
#include "pico_display.hpp"
#include "drivers/st7789/st7789.hpp"
#include "libraries/pico_graphics/pico_graphics.hpp"

#define T_DISPLAY_SPI spi0
#define T_DISPLAY_CS 5
#define T_DISPLAY_SCK 2
#define T_DISPLAY_MOSI 3
#define T_DISPLAY_DC 1
#define T_DISPLAY_PWM 4
#define T_DISPLAY_PWR 22

using namespace pimoroni;
SPIPins t_display_pins = {T_DISPLAY_SPI, T_DISPLAY_CS, T_DISPLAY_SCK, T_DISPLAY_MOSI, PIN_UNUSED, T_DISPLAY_DC, T_DISPLAY_PWM};
ST7789 st7789(
        PicoDisplay::WIDTH,
        PicoDisplay::HEIGHT,
        ROTATE_0,
        false,
        t_display_pins
        );

PicoGraphics_PenRGB332 graphics(st7789.width, st7789.height, nullptr);

bool state = true;

int main() {
    st7789.set_backlight(255);
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_init(T_DISPLAY_PWR);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    gpio_set_dir(T_DISPLAY_PWR, GPIO_OUT);
    gpio_put(T_DISPLAY_PWR, 1);
    stdio_init_all();
    Pen BG = graphics.create_pen(120, 40, 60);
    Pen YELLOW = graphics.create_pen(255, 255, 0);
    Pen TEAL = graphics.create_pen(0, 255, 255);
    Pen WHITE = graphics.create_pen(255, 255, 255);

    while (true) {
        graphics.set_pen(BG);
        graphics.clear();
        graphics.set_pen(TEAL);
        graphics.circle(Point(st7789.width / 2, st7789.height / 2), 20);
        st7789.update(&graphics);
        state = !state;
        gpio_put(PICO_DEFAULT_LED_PIN, state);
        sleep_ms(1000 / 60);
    }
}