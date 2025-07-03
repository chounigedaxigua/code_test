#ifndef _UART_H_
#define _UART_H_

#include <string>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <wiringPi.h>
#include <wiringSerial.h>


int uart_init(std::string dev);

// float get_current(char *current_char,int size);

void uartHandler(int uart_fd);

#endif