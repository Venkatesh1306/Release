/*MODBUS RTU

 * Header file: ModbusRtu.h
 *
 * Description:
 * The ModbusRtu.h header file provides declarations for the Modbus RTU communication protocol, facilitating data exchange between master and slave applications.
 *
 * Included Functions:
 * 1) uint16_t modbusRtuFrame(const uint8_t *p_modbusRxBuf, uint16_t *p_dataMemory, uint8_t *p_modbusTxBuf, uint16_t *modBusframeLength):
 *    This function receives query frames from the master, processes them, and generates response frames along with their respective lengths.
 *
 * 2) int16_t modbusRtuParse(mbPacketParse_t *p_parseModbusRtuData, uint8_t *p_modbusRxBuf):
 *    Upon receiving query frames, this function parses the data for further processing.
 *
 * 3) void modbusError(mbPacketParse_t *p_parseModbusRtuData, uint8_t *p_modbusTxBuf, unsigned char exceptioncode):
 *    In case of errors, this function sends exception frames to the master device, detailing the nature of the error.
 *
 * 4) uint16_t readHoldingRegisters(uint8_t *p_modbusTxBuf, uint16_t *p_dataMemory, mbPacketParse_t *p_parseModbusRtuData):
 *    When query frames with a function code of 0x03 are received without any exceptions, this function processes the data and constructs response frames accordingly.
 *
 * 5) uint16_t presetSingleRegister(uint8_t *p_modbusTxBuf, uint16_t *p_dataMemory, mbPacketParse_t *p_parseModbusRtuData):
 *    When query frames with a function code of 0x06 are received without any exceptions, this function processes the data and constructs response frames accordingly.
 *
 * 6) uint16_t presetMultipleRegisters(uint8_t *p_modbusTxBuf, uint16_t *p_dataMemory, mbPacketParse_t *p_parseModbusRtuData):
 *    Upon receiving query frames with a function code of 0x10 without any exceptions, this function processes the data and generates response frames accordingly.
 *
 * Dependencies:
 *        modhead.h
 *
 * Usage:
 *      Example: #include "ModbusRtu.h"
 */

#include "../modbusRtutypedef.h"

#ifndef MODBUSRTU_H
#define MODBUSRTU_H

/* Function Code Declaration */
#define ReadHoldingRegister 03
#define PresetSingleRegister 06
#define PresetMultipleRegisters 16

/* Size of address declaration */
#define DataRegistersize 0x7d
#define DataRegistersizeCheck (DataRegistersize - 1)
#define IllegalDataCheck 65000
#define MaxSizeRtuTx 100

/* Error Code Declaration */
#define Illegal_Function_Code 0x01u
#define Illegal_Data_Address 0x02u
#define Illegal_Data_Value 0x03u

/* Structure variable Declaration */
typedef struct
{
    uint16_t_VAL slave_addr;
    uint8_t functionCode;
    uint16_t_VAL startAddress;
    uint16_t_VAL numberofRegister;
    uint16_t_VAL num_reg;
    uint16_t byteCount;
    uint16_t_VAL forceData;
    uint16_t_VAL preset_Data;
    uint16_t_VAL data[DataRegistersize];
    uint16_t_VAL crc;
} mbPacketParse_t;

/* Function Declaration */
uint16_t modbusRtuFrame(const uint8_t *p_modbusRxBuf, uint16_t *p_dataMemory, uint8_t *p_modbusTxBuf, uint16_t *modBusframeLength); /* Frame function */
uint16_t modbusRtuParse(mbPacketParse_t *p_parseModbusRtuData, const uint8_t *p_modbusRxBuf);                                       /* Parse Function */
uint16_t readHoldingRegisters(uint8_t *p_modbusTxBuf, uint16_t *p_dataMemory, mbPacketParse_t *p_parseModbusRtuData);               /* Function Code - 0x03 */
uint16_t presetSingleRegisters(uint8_t *p_modbusTxBuf, uint16_t *p_dataMemory, mbPacketParse_t *p_parseModbusRtuData);              /* Function Code - 0x06 */
uint16_t presetMultipleRegisters(uint8_t *p_modbusTxBuf, uint16_t *p_dataMemory, mbPacketParse_t *p_parseModbusRtuData);            /* Function Code - 0x10 */
void modbusError(mbPacketParse_t *p_parseModbusRtuData, uint8_t *p_modbusTxBuf, uint8_t exceptioncode);                             /* Error Function */

uint8_t getLOWbyte(uint16_t input);
uint8_t getHIGHbyte(uint16_t input);
uint16_t combineBytes(uint8_t high, uint8_t low);
uint16_t CRC16(uint16_t crc, uint16_t data);
uint16_t checkCRC(const uint8_t *data, uint8_t Rcv_byte_cnt);
uint16_t generateCRC(const uint8_t *data, uint8_t length);

#endif