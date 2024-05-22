/* Force Multiple Coil - Function Code - 0F
 *  The query message specifies the coil reference to be forced

 * QUERY FRAME:
| Transaction Identifier | Protocol Identifier | Length | Unit Identifier | Function Code | Coil Address | Number of Bits |  Force Data Value      |
|------------------------|---------------------|--------|-----------------|---------------|--------------|----------------|------------------------|
|       2 bytes          |      2 bytes        |2 bytes |      1 byte     |     1 byte    |    2 bytes   |     2 bytes    |  Variable(nbytes)      |

RESPONSE FRAME:
| Transaction Identifier | Protocol Identifier | Length | Unit Identifier | Function Code | Coil Address |     Force Data Value   |
|------------------------|---------------------|--------|-----------------|---------------|--------------|------------------------|
|       2 bytes          |      2 bytes        |2 bytes |      1 byte     |     1 byte    |    2 bytes   |         2 bytes        |
 *
 * INPUT FRAME    = {0x00, 0x01, 0x00, 0x02, 0x00, 0x0B, 0x03, 0x0F, 0x00, 0x01, 0x00, 0x15, 0x04, 0xcd, 0x01, 0x03, 0x02}
 * RESPONSE FRAME = {0x00, 0x01, 0x00, 0x02, 0x00, 0x06, 0x03, 0x0F, 0x00, 0x01, 0x00, 0x15}
 */

#include "modbusTcp.h"

/* Macro definitions */
#define SET(x, y) x |= (1 << y)
#define READ(x, y) ((0u == (x & (1 << y))) ? 0u : 1u)
#define CLEAR(x, y) x &= ~(1 << y)

uint16_t forceMultipleCoils(uint8_t *p_modbusTxBuf, uint16_t *p_dataMemory, mbPacketParse_t *p_parseModbusTcpData) {

    /* Declaration of local variables*/
    uint16_t NoOfBits = 0, bit_count = 0, Regbit = 0, regTx = 0, RegbitTx = 0, reg = 0;
    uint16_t coil_data = 0;

    /* Assigning values for transmitting buffer*/
    p_modbusTxBuf[0] = p_parseModbusTcpData->transactionID.v[1];
    p_modbusTxBuf[1] = p_parseModbusTcpData->transactionID.v[0];

    p_modbusTxBuf[2] = p_parseModbusTcpData->protocolID.v[1];
    p_modbusTxBuf[3] = p_parseModbusTcpData->protocolID.v[0];

    p_modbusTxBuf[4] = 0X0;
    p_modbusTxBuf[5] = 0x06;

    p_modbusTxBuf[6] = p_parseModbusTcpData->unitID;
    p_modbusTxBuf[7] = p_parseModbusTcpData->functionCode;

    p_modbusTxBuf[8] = p_parseModbusTcpData->startAddress.v[1];
    p_modbusTxBuf[9] = p_parseModbusTcpData->startAddress.v[0];

    p_modbusTxBuf[10] = p_parseModbusTcpData->numberofRegister.v[1];
    p_modbusTxBuf[11] = p_parseModbusTcpData->numberofRegister.v[0];

    NoOfBits = p_parseModbusTcpData->numberofRegister.Val; /*Quantity of coils*/

    for (bit_count = NoOfBits - 1; bit_count >= 0; bit_count--) /*byte count*/ {

        Regbit = (p_parseModbusTcpData->startAddress.Val + bit_count - 1) % 16; /* 20 - 1 % 16 = 4th bit */
        reg = (p_parseModbusTcpData->startAddress.Val + bit_count - 1) / 16; /* 20 - 1 /16 = 1st  reg */

        RegbitTx = (bit_count) % 16; /* 20 - 1 % 16 = 4th bit -- bit increment */
        regTx = (bit_count) / 16; /* 20 - 1 /16 = 1st  reg -- register increment */

        if (p_parseModbusTcpData->coilData[regTx] > IllegalDataCheck) /*checks for illegal data*/ {
            p_parseModbusTcpData->functionCode = p_parseModbusTcpData->functionCode + 0x80;
            modbusError(p_parseModbusTcpData, p_modbusTxBuf, Illegal_Data_Value);
            break;
        } else {
            coil_data = READ(p_parseModbusTcpData->coilData[regTx], RegbitTx);

            if (coil_data == 0x1) {
                SET(p_dataMemory[reg], Regbit);
            } else {
                CLEAR(p_dataMemory[reg], Regbit);
            }
            if (bit_count == 0) {
                break;
            }
        }
    }
    return 0x12;
}
