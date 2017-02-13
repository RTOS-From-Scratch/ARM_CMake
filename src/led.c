#include "tm4c123gh6pm.h"

#define LED_RED 0x2
#define NOP __asm__ __volatile__("NOP\n\tNOP")

void LedRed_init()
{
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGC2_GPIOF;
    __asm__ __volatile__("NOP\n\tNOP");
    GPIO_PORTF_DEN_R |= LED_RED;
    GPIO_PORTF_AMSEL_R &= ~LED_RED;
    GPIO_PORTF_AFSEL_R &= ~LED_RED;
    GPIO_PORTF_PCTL_R &= ~(0xf0 << 4);
    GPIO_PORTF_DIR_R |= LED_RED;
}

void LedRed_HIGH()
{
    GPIO_PORTF_DATA_R |= LED_RED;
}

void LedRed_LOW()
{
    GPIO_PORTF_DATA_R &= ~LED_RED;
}
