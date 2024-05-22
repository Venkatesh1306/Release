#include <stdint.h>

#define INR_SIZE 36

int increment;
int Test_Res;
int test_c;
unsigned int incrs;
uint8_t ModbusRxBuftest[INR_SIZE][100];
uint8_t expected_TXA[INR_SIZE][100];
uint8_t ModbusRxBuf[100];
uint8_t ModbusTxBuf[25];
uint8_t expec_TX[25];
uint16_t COIL1[150];
uint16_t Dataregister[150];
uint16_t COIL[25];
uint8_t regis[25];
uint16_t ModbusTxLength;
uint16_t receivedData;
uint16_t add;
uint16_t numRegisters;