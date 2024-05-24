/*MODBUS TCP
 *Header file : ModbusTcp.h
 *
 *Description:
 * The ModbusTcp.h header file provides declarations for the communication
 * protocol ModbusTcp used for data exchange between client and server applications.
 *
 * Included Functions :
 * 1) uint16_t modbusTcpFrame(const uint8_t *p_modbusRxBuf, uint16_t *p_dataMemory, uint8_t *p_modbusTxBuf, uint16_t *modBusframeLength);
 *      Receives the Query frame from client and provides the response frame and its length according to the request.
 *
 * 2) int16_t modbusTcpParse(mbPacketParse_t *p_parseModbusTcpData, uint8_t *p_modbusRxBuf);
 *      This function breaks down the received query frame and provides the parsed data for further processing.
 *
 * 3) void modbusError(mbPacketParse_t *p_parseModbusTcpData, uint8_t *p_modbusTxBuf, unsigned char exceptioncode);
 *      The server sends an exception frame to the client to report an exception response with the nature of the error.
 *
 * 4) uint16_t readHoldingRegisters(uint8_t *p_modbusTxBuf, uint16_t *p_dataMemory, mbPacketParse_t *p_parseModbusTcpData);
 *      This function is executed when the query frame has the function code of 0x03 and without any exceptions. It process
 *  the parsed data of the query and forms the response frame accordingly.
 *
 * 5) uint16_t presetSingleRegister(uint8_t *p_modbusTxBuf, uint16_t *p_dataMemory, mbPacketParse_t *p_parseModbusTcpData);
 *      This function is executed when the query frame has the function code of 0x06 and without any exceptions. It process
 *  the parsed data of the query and forms the response frame accordingly.
 *
   6) uint16_t presetMultipleRegisters(uint8_t *p_modbusTxBuf, uint16_t *p_dataMemory, mbPacketParse_t *p_parseModbusTcpData);
 *      This function is executed when the query frame has the function code of 0x10 and without any exceptions. It process
 *  the parsed data of the query and forms the response frame accordingly.
 *
 * Depedencies :
 *      modhead.h
 *
 * Usage :
 *      Example : # include "ModbusTcp.h"
 */

#include "..\modbusTcptypedef.h"
#include <stdio.h>

#ifndef MODBUSTCP_H
#define MODBUSTCP_H

/* Function Code Definitions */
#define ReadCoilStatus 01
#define ReadInputStatus 02
#define ReadHoldingRegister 03
#define ReadInputRegisters 04
#define ForceSingleCoil 05
#define PresetSingleRegister 06
#define ForceMultipleCoils 15
#define PresetMultipleRegisters 16

/* Definitions for size which the array and variables not be exceed*/
#define Checksize 1u
#define DataRegistersize 0x7du
#define DataRegistersizeCheck (DataRegistersize - Checksize)
#define CoilDatasize 0x100u
#define MaxSizeTcpTx 100u
#define MaxSizeTxtempbuf 30u
#define MaxSizeCoilData 25u
#define MaxSizeCoilDataCheck (MaxSizeCoilData - Checksize)
#define IllegalDataCheck 65000u

/*Error Code Definitions */
#define Illegal_Function_Code 0x01u
#define Illegal_Data_Address 0x02u
#define Illegal_Data_Value 0x03u

/* Declaration of Structure Variables */
typedef struct {
    uint16_t_VAL transactionID;
    uint16_t_VAL protocolID;
    uint16_t length;
    uint8_t unitID;
    uint8_t functionCode;
    uint16_t_VAL startAddress;
    uint16_t_VAL numberofRegister;
    uint16_t byteCount;
    uint16_t_VAL preset_Data;
    uint16_t coilData[MaxSizeCoilData];
    uint16_t_VAL forceData[MaxSizeCoilData];
    uint16_t_VAL data[DataRegistersize];

} mbPacketParse_t;

/* declaration of functions */
uint16_t modbusTcpFrame(const uint8_t *p_modbusRxBuf, uint16_t *p_dataMemory, uint8_t *p_modbusTxBuf, uint8_t *modBusframeLength); /* Frame function */
uint16_t modbusTcpParse(mbPacketParse_t *p_parseModbusTcpData, const uint8_t *p_modbusRxBuf); /* Parse Function */
uint16_t readCoilStatus(uint8_t *p_modbusTxBuf, const uint16_t *p_dataMemory, mbPacketParse_t *p_parseModbusTcpData); /* Function Code - 0x01 */
uint16_t readInputStatus(uint8_t *p_modbusTxBuf, uint16_t *p_dataMemory, mbPacketParse_t *p_parseModbusTcpData); /* Function Code - 0x02 */
uint16_t readHoldingRegisters(uint8_t *p_modbusTxBuf, uint16_t *p_dataMemory, mbPacketParse_t *p_parseModbusTcpData); /* Function Code - 0x03 */
uint16_t readInputReg(uint8_t *p_modbusTxBuf, uint16_t *p_dataMemory, mbPacketParse_t *p_parseModbusTcpData); /* Function Code - 0x04 */
uint16_t forceSingleCoil(uint8_t *p_modbusTxBuf, uint16_t *p_dataMemory, mbPacketParse_t *p_parseModbusTcpData); /* Function Code - 0x05 */
uint16_t presetSingleRegister(uint8_t *p_modbusTxBuf, uint16_t *p_dataMemory, mbPacketParse_t *p_parseModbusTcpData); /* Function Code - 0x06 */
uint16_t forceMultipleCoils(uint8_t *p_modbusTxBuf, uint16_t *p_dataMemory, mbPacketParse_t *p_parseModbusTcpData); /* Function Code - 0x0f */
uint16_t presetMultipleRegisters(uint8_t *p_modbusTxBuf, uint16_t *p_dataMemory, mbPacketParse_t *p_parseModbusTcpData); /* Function Code - 0x10 */
void modbusError(mbPacketParse_t *p_parseModbusTcpData, uint8_t *p_modbusTxBuf, uint8_t exceptioncode); /* Error Function */

#endif