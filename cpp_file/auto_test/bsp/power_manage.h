#ifndef _POWER_MANAGE_H_
#define _POWER_MANAGE_H_

#define GPIO_B    4
#define GPIO_ACC  2
#define GPIO_IG   3

#define GPIO_USB_POWER 5
#define GPIO_PROGRAM_5G 25

void power_manage_init();

void normal_power_mode();
void low_power_mode();
void power_gpio_set(int a,int b,int c,int d);
#endif