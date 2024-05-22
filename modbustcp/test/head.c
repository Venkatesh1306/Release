#include <stdint.h>

#define INR_SIZE 14

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
uint16_t Dataregister[100];
uint16_t receivedData;
uint16_t add;
uint16_t numRegisters;