// including the required header files
#include "..\modbusTcptypedef.h"
#include "..\libModbusTcp\modbusTcp.h"
#include <stdio.h>

// define the values
#define test_ing
#define result
#define INR_SIZE 36
#define GET_BIT(x, pos) ((x >> pos) & 1)
#define SET(PIN, N) (PIN |= (1 << N))
#define CLR(PIN, N) (PIN &= ~(1 << N))

// ANSI escape codes for text color - for testing features
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_ORANGE "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_RESET "\x1b[0m"

// Variables and Values
extern int increment;
extern int Test_Res;
extern int test_c;
extern unsigned int incrs;
extern uint8_t ModbusRxBuftest[INR_SIZE][100];
extern uint8_t expected_TXA[INR_SIZE][100];
extern uint8_t ModbusRxBuf[100];
extern uint8_t ModbusTxBuf[25];
extern uint8_t expec_TX[25];
extern uint16_t COIL1[150];
extern uint16_t Dataregister[150];
extern uint16_t COIL[25];
extern uint8_t regis[25];
extern uint16_t ModbusTxLength;
extern uint16_t receivedData;
extern uint16_t add;
extern uint16_t numRegisters;

// declaration of the function
// uint16_t processexpecteddata(uint8_t *ModbusRxBuf, uint8_t *expec_TX, uint16_t Dataregister[]);
uint16_t Test_ing(const uint8_t ModbusTxBuf[], const uint8_t expec_TX[]);
uint16_t modbusTcpFrame(const uint8_t *p_modbusRxBuf, uint16_t *p_dataMemory, uint8_t *p_modbusTxBuf, uint16_t *modBusframeLength);
void printfunction();