#define F_CPU 3333333UL

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>

/*
  ATmega4809 Curiosity Nano:
  - The user LED is commonly on PORTF pin 5.
  If your LED doesn't blink, change LED_PORT and LED_PIN below.
*/
#define LED_PORT PORTF
#define LED_PIN  5

static void led_init(void)
{
    LED_PORT.DIRSET = (1 << LED_PIN);   // output
}

static void led_toggle(void)
{
    LED_PORT.OUTTGL = (1 << LED_PIN);   // toggle
}

static uint16_t compute_cycle_value(uint16_t value)
{
    uint16_t result = value;

    for (uint8_t i = 1; i <= 6; i++) {
        result += (uint16_t)((result ^ (uint16_t)(i * 7u)) + (i << 2));
        result ^= (uint16_t)((result >> 3) | (result << 5));
    }

    return result;
}

static uint16_t perform_debug_operations(void)
{
    volatile uint16_t accumulator = 0;
    uint16_t values[10];

    for (uint8_t i = 0; i < sizeof(values) / sizeof(values[0]); i++) {
        values[i] = (uint16_t)((i + 1) * 13 + ((i & 1) ? 0x5A : 0xA5));
    }

    for (uint8_t i = 0; i < sizeof(values) / sizeof(values[0]); i++) {
        uint16_t v = values[i];
        uint16_t computed = compute_cycle_value(v);

        if ((v & 3) == 0) {
            accumulator += computed;
        } else {
            accumulator -= (uint16_t)(computed >> 1);
        }

        accumulator ^= (uint16_t)(v << (i % 5));
    }

    if (accumulator < 5000) {
        accumulator += 0x1234;
    } else {
        accumulator ^= 0x55AA;
    }

    return accumulator;
}

int main(void)
{
    uint16_t debug_value;

    led_init();

    while (1) {
        led_toggle();
        debug_value = perform_debug_operations();

        if (debug_value & 1u) {
            _delay_ms(250);
        } else {
            _delay_ms(400);
        }
    }
}