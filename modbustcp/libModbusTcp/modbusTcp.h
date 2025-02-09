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

#include "..\modbusTcptydef.h"

#ifndef MODBUSTCP_H
#define MODBUSTCP_H

/* Function Code Definitions */
#define ReadHoldingRegister 03
#define PresetSingleRegister 06
#define PresetMultipleRegisters 16

/* Definitions for size which the array and variables not be exceed*/
#define DataRegistersize 0x7d
#define DataRegistersizeCheck (DataRegistersize - 1)
#define MaxSizeTcpTx 100
#define IllegalDataCheck 65000

/*Error Code Definitions */
#define Illegal_Function_Code 0x01u
#define Illegal_Data_Address 0x02u
#define Illegal_Data_Value 0x03u

/* Declaration of Structure Variables */
typedef struct
{
  uint16_t_VAL transactionID;
  uint16_t_VAL protocolID;
  uint16_t length;
  uint8_t unitID;
  uint8_t functionCode;
  uint16_t_VAL startAddress;
  uint16_t_VAL numberofRegister;
  uint16_t byteCount;
  uint16_t_VAL preset_Data;
  uint16_t_VAL data[DataRegistersize];

} mbPacketParse_t;

/* declaration of functions */
uint16_t modbusTcpFrame(const uint8_t *p_modbusRxBuf, uint16_t *p_dataMemory, uint8_t *p_modbusTxBuf, uint16_t *modBusframeLength); /* Frame function */
uint16_t modbusTcpParse(mbPacketParse_t *p_parseModbusTcpData, const uint8_t *p_modbusRxBuf);                                       /* Parse Function */
uint16_t readHoldingRegisters(uint8_t *p_modbusTxBuf, uint16_t *p_dataMemory, mbPacketParse_t *p_parseModbusTcpData);               /* Function Code - 0x03 */
uint16_t presetSingleRegister(uint8_t *p_modbusTxBuf, uint16_t *p_dataMemory, mbPacketParse_t *p_parseModbusTcpData);               /* Function Code - 0x06 */
uint16_t presetMultipleRegisters(uint8_t *p_modbusTxBuf, uint16_t *p_dataMemory, mbPacketParse_t *p_parseModbusTcpData);            /* Function Code - 0x10 */
void modbusError(mbPacketParse_t *p_parseModbusTcpData, uint8_t *p_modbusTxBuf, unsigned char exceptioncode);                       /* Error Function */

#endif