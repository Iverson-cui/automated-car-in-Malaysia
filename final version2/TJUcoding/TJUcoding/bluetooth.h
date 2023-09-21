#ifndef __BLUETOOTH_H__
#define __BLUETOOTH_H__

#include <reg52.h>
#include <driver.h>

void Bluetooth_Init(void);
extern int RETURN_FLAG;
extern int PATTERN;
extern char Flag_BluetoothCar;

void BluetoothControlCar(void);
void receive(unsigned char m);
#endif