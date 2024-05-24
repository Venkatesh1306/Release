/* Basic bit manipulation macros
 * No one should ever have to rewrite these

 * Set bit y (0-indexed) of x to '1' by generating a a mask with a '1' in the proper bit location and ORing x with the mask.

#define SET(x,y) x |= (1 << y)

 * Set bit y (0-indexed) of x to '0' by generating a mask with a '0' in the y position and 1's elsewhere then ANDing the mask with x.

#define CLEAR(x,y) x &= ~(1<< y)

 * Return '1' if the bit value at position y within x is '1' and '0' if it's 0 by ANDing x with a bit mask where the bit in y's position is '1' and '0' elsewhere and comparing it to all 0's.  Returns '1' in least significant bit position if the value of the bit is '1', '0' if it was '0'.

#define READ(x,y) ((0u == (x & (1<<y)))?0u:1u)

 * Toggle bit y (0-index) of x to the inverse: '0' becomes '1', '1' becomes '0' by XORing x with a bitmask where the bit in position y is '1' and all others are '0'.

#define TOGGLE(x,y) (x ^= (1<<y))

READ COIL STATUS : Function Code - 02
=================

Reads the ON/OFF status of discrete outputs (0X references, coils) in the slave

 * QUERY FRAME:


| Transaction Identifier | Protocol Identifier | Length | Unit Identifier | Function Code | Starting Address |  	No of points	 |
|------------------------|---------------------|--------|-----------------|---------------|------------------|-----------------------|
|       2 bytes          |      2 bytes        |2 bytes |      1 byte     |     1 byte    |     2 bytes      |       2 bytes         |


 * RESPONSE FRAME :


| Transaction Identifier | Protocol Identifier | Length | Unit Identifier | Function Code |    Byte Count	 |      	DATA		 |
|------------------------|---------------------|--------|-----------------|---------------|------------------|-----------------------|
|       2 bytes          |      2 bytes        |2 bytes |      1 byte     |     1 byte    |		1byte		 |	variable (n bytes)	 |

 * DataRegister = {0xffff, 0x0f0f, 0x0ff0, 0xF00F, 0xf000, 0x00f0, 0x0fff, 0xff00, 0x3A2B, 0x3c7e, 0x0302, 0xFFFF, 0x1123, 0x1321, 0x3A2B, 0x3c7e, 0x0065, 0x2217, 0x1123, 0x1321, 0x3A2B, 0x3c7e, 0x0065, 0x2217, 0x1123, 0x1321, 0x3A2B, 0x3c7e, 0x0065, 0x2217, 0x1123, 0x1321, 0x3A2B, 0x3c7e};

 * Input Frame  :{0x00, 0x01, 0x00, 0x02, 0x00, 0x06, 0x03, 0x02, 0x00, 0x01, 0x00, 0x09}
 * Output Frame :{0x00, 0x01, 0x00, 0x02, 0x00, 0x05, 0x03, 0x02, 0x02, 0xff, 0x01}


 */

#include "modbusTcp.h"

/* Declaration of macro function */
#define SET(x, y) x |= (1 << y)
#define READ(x, y) ((0u == (x & (1 << y))) ? 0u : 1u)

uint16_t readInputStatus(uint8_t *p_modbusTxBuf, uint16_t *p_dataMemory, mbPacketParse_t *p_parseModbusTcpData) {

    /* According to CppCheck, it is advised to declare the p_dataMemory as a pointer to constant
     *  However, in this case, we are not declaring it as constant because it doesn't allow flexibility in modifying the data through the pointer when necessary.
     */

    /* local variable declaration */
    uint16_t NoOfBits = 0, Regbit = 0, reg = 0, RegbitTx = 0, regTx = 0, byte_index = 0, bit_count = 0, wordOffset = 0;
    uint16_t Txtempbuf1[MaxSizeTxtempbuf] = {0};
    uint16_t byte_count = 0, coil_bit = 0;
    uint8_t limit = 0;

    /* Assigning values for transmitting buffer*/
    p_modbusTxBuf[0] = p_parseModbusTcpData->transactionID.v[1];
    p_modbusTxBuf[1] = p_parseModbusTcpData->transactionID.v[0];

    p_modbusTxBuf[2] = p_parseModbusTcpData->protocolID.v[1];
    p_modbusTxBuf[3] = p_parseModbusTcpData->protocolID.v[0];

    p_modbusTxBuf[4] = 0X0;

    p_modbusTxBuf[6] = p_parseModbusTcpData->unitID;
    p_modbusTxBuf[7] = p_parseModbusTcpData->functionCode;

    byte_count = (p_parseModbusTcpData->numberofRegister.Val / 0x8) + 1;
    p_modbusTxBuf[8] = byte_count;

    p_modbusTxBuf[5] = 0x03 + byte_count;

    NoOfBits = p_parseModbusTcpData->numberofRegister.Val;

    /*Ignored the CppCheck warning for variables reg, Regbit,RegbitTx,wordOffset and coil_bit  as they are assigned values but never used
     * Regbit : Represents the bit position within a register,used in lines 97,102.
     * reg: Indicates the register index, used in lines 98,102
     * RegbitTx: Tracks the bit position for transmission,used in lines 99,103
     * wordOffset: Represents the offset for word alignment used in lines 109,110,111
     * coil_bit: Stores the value of the bit being read used in line 102,103.
     */

    for (bit_count = 0; bit_count < NoOfBits; bit_count++) /* byte count */ {
        Regbit = (p_parseModbusTcpData->startAddress.Val + bit_count - 1) % 16; /* 20 - 1 % 16 = 4th bit */
        reg = (p_parseModbusTcpData->startAddress.Val + bit_count - 1) / 16; /* 20 - 1 /16 = 1st  reg */
        RegbitTx = (bit_count) % 16; /* 20 - 1 % 16 = 4th bit -- bit increment */
        regTx = (bit_count) / 16; /* 20 - 1 /16 = 1st  reg -- register increment */

        coil_bit = READ(p_dataMemory[reg], Regbit);
        Txtempbuf1[regTx] |= coil_bit << RegbitTx;
    }

    for (byte_index = 0; byte_index < (regTx + 1); byte_index++) {
        wordOffset = byte_index * 2;
        p_modbusTxBuf[9 + wordOffset] = (Txtempbuf1[byte_index] % 0x100);
        p_modbusTxBuf[10 + wordOffset] = (Txtempbuf1[byte_index] / 0x100);
    }

    limit = p_modbusTxBuf[5] + 0x6;
    return limit;
}
