/*QUERY FRAME:

| Transaction Identifier | Protocol Identifier | Length | Unit Identifier | Function Code | Starting Address | Quantity of Registers | Byte Count | Data (2 bytes per register) |
|------------------------|---------------------|--------|-----------------|---------------|------------------|-----------------------|------------|-----------------------------|
|       2 bytes          |      2 bytes        |2 bytes |      1 byte     |     1 byte    |     2 bytes      |       2 bytes         |   1 byte   |         n bytes            |


RESPONSE FRAME:

| Transaction Identifier | Protocol Identifier | Length | Unit Identifier | Function Code | Starting Address | Quantity of Registers |
|------------------------|---------------------|--------|-----------------|---------------|------------------|-----------------------|
|       2 bytes          |      2 bytes        |2 bytes |      1 byte     |     1 byte    |     2 bytes      |       2 bytes         |

 * Function Code - 16 (10 HEX)
 * DataRegister[25]={0x0000, 0x0001, 0x0002, 0x0003, 0x0004, 0x0005, 0x0006, 0x0007, 0x0008, 0x0009, 0x0009, 0x0008, 0x0007, 0x0007, 0x0006, 0x0005, 0x0004, 0x0003, 0x0002, 0x0001, 0x0025, 0x0035, 0x0036, 0x9957, 0x7890};
 * INPUT FRAME = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x10, 0x10, 0x00, 0x01, 0x00, 0x02, 0x04, 0x00, 0x0A, 0x01, 0x02}
 *
 * After Processing the Query the DataRegister changes if no error is detected i.e to preset two registers starting at 01 to 0x0000A, 0x0102
 * RESPONSE FRAME = {0x0, 0x1, 0x2, 0x3, 0x0, 0x12, 0x10, 0x10, 0x0, 0x1, 0x0, 0x2} - 12 bytes.
 * DATAREGISTER = {0x0000, 0x000A, 0x0102, 0x0003, 0x0004, 0x0005, 0x0006, 0x0007, 0x0008, 0x0009, 0x0009, 0x0008, 0x0007, 0x0007, 0x0006, 0x0005, 0x0004, 0x0003, 0x0002, 0x0001, 0x0025, 0x0035, 0x0036, 0x9957, 0x7890 }

 * If error detected
 * RESPONSE FRAME = {0x0, 0x1, 0x2, 0x3, 0x0, 0x9, 0x10, 0x90, 0x3} - last byte refers to exception code
 * DATAREGISTER UNMODIFIED.

 */

#include "modbusTcp.h"

uint16_t presetMultipleRegisters(uint8_t *p_modbusTxBuf, uint16_t *p_dataMemory, mbPacketParse_t *p_parseModbusTcpData)
{
  /*Local variable declaration */
  uint16_t length = 0;
  uint16_t limit = 0;

  /* Assigning values for transmitting buffer*/
  p_modbusTxBuf[0] = p_parseModbusTcpData->transactionID.v[1];
  p_modbusTxBuf[1] = p_parseModbusTcpData->transactionID.v[0];

  p_modbusTxBuf[2] = p_parseModbusTcpData->protocolID.v[1];
  p_modbusTxBuf[3] = p_parseModbusTcpData->protocolID.v[0];

  p_modbusTxBuf[4] = 0X0;

  p_modbusTxBuf[6] = p_parseModbusTcpData->unitID;

  p_modbusTxBuf[7] = p_parseModbusTcpData->functionCode;

  for (limit = 0; limit < p_parseModbusTcpData->numberofRegister.v[0]; limit++)
  {
    if (p_parseModbusTcpData->data[limit].Val >= (int)(IllegalDataCheck)) /* checks for illegal data value */
    {

      p_parseModbusTcpData->functionCode = p_parseModbusTcpData->functionCode + 0x80;
      modbusError(p_parseModbusTcpData, p_modbusTxBuf, Illegal_Data_Value);
      limit = p_parseModbusTcpData->numberofRegister.v[0] + 1;
      length = 0X09;
    }
    else
    {
      p_dataMemory[p_parseModbusTcpData->startAddress.Val + limit] = p_parseModbusTcpData->data[limit].v[0] +
                                                                     (p_parseModbusTcpData->data[limit].v[1] * 0x100); /* Writes the data to register */ 
    }
  }
  if (0x10 == p_parseModbusTcpData->functionCode)
  {
    /* Assigning values for transmitting buffer*/
    p_modbusTxBuf[8] = p_parseModbusTcpData->startAddress.v[1];
    p_modbusTxBuf[9] = p_parseModbusTcpData->startAddress.v[0];
    p_modbusTxBuf[10] = p_parseModbusTcpData->numberofRegister.v[1];
    p_modbusTxBuf[11] = p_parseModbusTcpData->numberofRegister.v[0];
    p_modbusTxBuf[5] = 0x06;
    length = 0x12;
  }

  return length;
}