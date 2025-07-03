#include "power_manage.h"

#include <stdio.h>
#include <wiringPi.h>

void power_manage_init()
{
    wiringPiSetup();
    
    pinMode(GPIO_B,OUTPUT);
    pinMode(GPIO_ACC,OUTPUT);
    pinMode(GPIO_IG,OUTPUT);
    pinMode(GPIO_USB_POWER,OUTPUT);

    // digitalWrite(GPIO0,LOW); 
}
void normal_power_mode()
{
    digitalWrite(GPIO_B,LOW);
    digitalWrite(GPIO_ACC,LOW);
    digitalWrite(GPIO_IG,LOW);
    digitalWrite(GPIO_USB_POWER,LOW);
}
void low_power_mode()
{
    digitalWrite(GPIO_B,LOW);
    digitalWrite(GPIO_ACC,HIGH);
    digitalWrite(GPIO_IG,HIGH);
    digitalWrite(GPIO_USB_POWER,HIGH);
}
void power_gpio_set(int a,int b,int c,int d)
{

    digitalWrite(GPIO_B,!a);
    digitalWrite(GPIO_ACC,!b); 
    digitalWrite(GPIO_IG,!c); 
    digitalWrite(GPIO_USB_POWER,!d); 
}
