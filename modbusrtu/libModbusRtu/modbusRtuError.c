/*
Function name : void modbusError(mbPacketParse_t *p_parseModbusRtuData, uint8_t *p_modbusTxBuf, unsigned char exceptioncode)
Return Type   : None
Parameters    :
     *      p_modbusTxBuf         -  response frame that is sent to client from the server after processing the query frame
     *      exceptioncode         -  error codes that are returned by a modbus slave device when it has detected a problem with a command that it received
     *      p_parseModbusRtuData  -  contains the parsed data of the received query frame
Description   :
 *      This function is called when the query message has detected a problem with a command . It receives the parsed data of the query message
  and the exception code specific to the problem as input. It frames the exception response message to be transmitted to the client. The length of the reponse
  frame is constant (9 bytes) for all exception codes.
Usage         :
 *      Example - modbusError(&p_parseModbusRtuData, p_modbusTxBuf, Illegal_Data_Address);
Required      :  exceptioncode,p_parseModbusRtuData

QUERY FRAME:

QUERY FRAME :

|Slave Address |  Function Code   |   Starting Address (Hi)   |   Starting Address (Lo)   |   Quantity of Registers (Hi)  |   Quantity of Registers (Lo)  |   CRC (Cyclic Redundancy Check)|
|--------------|------------------|---------------------------|---------------------------|-------------------------------|-------------------------------|--------------------------------|
|    1 byte    |     1 byte       |         1 byte            |          1 byte           |            1 byte             |            1 byte             |     2 bytes                    |

RESPONSE FRAME:

|Slave Address |  Function Code   | Exception Code      |   CRC (Cyclic Redundancy Check)|
|--------------|------------------|---------------------|--------------------------------| - 5 bytes
|    1 byte    |     1 byte       |   1 byte            |           2 bytes              |

FUNCTION CODE ERROR:(0X01)
 * INPUT FRAME  = {0x10, 0x09, 0x00, 0x06, 0x00, 0x03, 0x7E, 0x8A};
 * The function code specifief in the query is not recognized or supported by the server (i.e the function code (0x09) is invalid).
 * RESPONSE FRAME = {0x10, 0x89, 0x1, 0xD6, 0X55};

ADDRESS ERROR:(0X02)
 * INPUT FRAME  = {0x10, 0x03, 0x00, 0x64, 0x00, 0x1E, 0x87, 0x5C}
 * The  Starting Address size should not exceed DataRegistersize.
 * RESPONSE FRAME = {0x10, 0x83, 0x2, 0x90, 0xF4}

 DATA ERROR:(0X03) -- for Function code - 0x06 and 0x10:
 * INPUT FRAME  = {0x11, 0x06, 0x00, 0x01, 0xFD, 0xE8, 0x9A, 0x44};
 * The data value should not exceed the maximum allowed value of 65000(0xFDE8) for the Modbus Data Registers. Here the Data to be entered is invalid.
 * RESPONSE FRAME = {0x11, 0x86, 0x3, 0x3, 0xA4}
 */

#include "modbusRtu.h"

void modbusError(mbPacketParse_t *p_parseModbusRtuData, uint8_t *p_modbusTxBuf, unsigned char exceptioncode)
{
  /* Assigning values for modbustx buffer */
  p_modbusTxBuf[0] = p_parseModbusRtuData->slave_addr.Val;
  p_modbusTxBuf[1] = p_parseModbusRtuData->functionCode;
  p_modbusTxBuf[2] = exceptioncode;
  p_parseModbusRtuData->crc.Val = generateCRC(&p_modbusTxBuf[0], 3);
  p_modbusTxBuf[3] = p_parseModbusRtuData->crc.bytes.LB;
  p_modbusTxBuf[4] = p_parseModbusRtuData->crc.bytes.HB;
}
