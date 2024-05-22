// including the required header files
#include "..\modhead.h"
#include "..\libModbus\ModbusTcp.h"
#include <stdio.h>
// #include <stdint.h>

// define the values
#define test_ing
#define result
#define INR_SIZE 18
#define GET_BIT(x, pos) ((x >> pos) & 1)
#define SET(PIN, N) (PIN |= (1 << N))
#define CLR(PIN, N) (PIN &= ~(1 << N))

// ANSI escape codes for text color - for testing features
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_ORANGE "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_RESET "\x1b[0m"

 int increment;
 int Test_Res;
 int testcheck;
 unsigned int incrs;
 uint16_t ModbusTxLength;
 uint8_t ModbusRxBuftest[INR_SIZE][100];
 uint8_t Test_TXtest[INR_SIZE][100];
 uint8_t ModbusRxBuf[100];
 uint8_t ModbusTxBuf[25];
 uint8_t Test_tx[25];
 uint16_t COIL1[25];
 uint16_t COIL[25];
 uint8_t regis[25];
 uint16_t Dataregister[150];
 uint16_t receivedData;
 uint16_t add;
 uint16_t numRegisters;

// declaration of the function
// uint16_t processexpecteddata(uint8_t *ModbusRxBuf, uint8_t *Test_tx, uint16_t Dataregister[]);
uint16_t Test_ing(const uint8_t ModbusTxBuf[], const uint8_t Test_tx[]);
uint16_t modbusTcpFrame(const uint8_t *p_modbusRxBuf, uint16_t *p_dataMemory, uint8_t *p_modbusTxBuf, uint16_t *modBusframeLength);
void printfunction();