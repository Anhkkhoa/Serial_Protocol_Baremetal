//I2C Driver Header File
#pragma once

void I2CPeripheral(void);
void I2CStart(void);
void I2CStop(void);
void I2CWriteChipAddr(uint8_t txdata); //Sending Register and Address before dasta byte
void I2CWriteRegAddr(uint8_t txdata); //Sending Register and Address before dasta byte
uint8_t I2CRead(uint8_t ack);
void I2CWriteRegister(uint8_t reg, uint8_t value, uint8_t address);
uint8_t I2CReadRegister(uint8_t reg, uint8_t address) ;