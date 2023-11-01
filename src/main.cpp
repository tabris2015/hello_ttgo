#include "pico/stdlib.h"
#include "stdio.h"

int main() {
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    stdio_init_all();

    while (true) {
        printf("Hello! \n");
        gpio_put(PICO_DEFAULT_LED_PIN, true);
        sleep_ms(300);
        gpio_put(PICO_DEFAULT_LED_PIN, false);
        sleep_ms(300);
    }
}