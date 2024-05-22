#include "ModbusRtu.h"

/*
 * Function name : uint8_t getLOWbyte(uint16_t input)
 * Return Type   : Returns the low byte from the input.
 * Parameters    : uint16_t input - ModbusRtuRx frame with the generated crc
 * Description   :The result of the bitwise AND operation is returned as an 8-bit unsigned integer (uint8_t), which contains the low byte of the original 16-bit input.
 * Usage         :
 *      Example -   getLOWbyte(Rcv_Data_CRC);
 * Required      :  Rcv_Data_CRC that is the generated crc
 */

uint8_t getLOWbyte(uint16_t input)
{

    return input & 255;
}

/* Function name : uint8_t getHIGHbyte(uint16_t input)
 * Return Type   : Returns the High byte from the input.
 * Parameters    : uint16_t input - ModbusRx frame with the generated crc
 * Description   :The result of the bitwise AND operation is returned as an 8-bit unsigned integer (uint8_t), which contains the high byte of the original 16-bit input.
 * Usage         :
 *      Example -   getLOWbyte(Rcv_Data_CRC);
 * Required      :  Rcv_Data_CRC that is the generated crc
 */
/* Get HIGH byte of int */
uint8_t getHIGHbyte(uint16_t input)
{

    return (input >> 8) & 255;
}

/*
 * Function name : uint16_t combineBytes(uint8_t high, uint8_t low)
 * Return Type   : returns the combined high and low bytes of a 16-bit value into a single 16-bit unsigned integer.
 * Parameters    : uint8_t high, uint8_t low
 * Description   : The function combineBytes takes two 8-bit unsigned integers high and low, representing the high and low bytes of a 16-bit value respectively, and combines them into a single 16-bit unsigned integer.
 * Usage         : uint16_t combineBytes(uint8_t highbyte, uint8_t lowbyte)
 *      Example -
 * Required      :  two 8-bit values
 */
/* Combine HIGH and LOW bytes */
uint16_t combineBytes(uint8_t high, uint8_t low)
{

    return (int)(high << 8) + low;
}

/*
 * Function name : uint16_t generateCRC(uint8_t * data, uint8_t length)
 * Return Type   : Returns the final CRC value calculated over the entire data buffer.
 * Parameters    : uint16_t input - ModbusRtuRx frame
 *                 uint16_t length - ModbusRtuRx frame length without crc
 * Description   : This function is responsible for generating a CRC value for a given data buffer using the CRC16 function
 * Usage         :
 *      Example -   generateCRC(data, Rcv_byte_cnt1);
 * Required      :  ModbusRxframe ,its length
 */

uint16_t generateCRC(const uint8_t *data, uint8_t length)
{
    uint16_t crc = 0xFFFF; /* load a bit register with FFFF - CRC register */
    uint16_t j;
    for (j = 0; j < length; j++)
    {

        crc = CRC16(crc, data[j]);
    }
    return crc;
}

/*
 * Function name : uint16_t CRC16(uint16_t crc, uint16_t data)
 * Return Type   : Returns the final CRC value calculated over the entire data buffer.
 * Parameters    : uint16_t input - ModbusRtuRx frame
 *                 uint16_t length - ModbusRtuRx frame length without crc
 * Description   : This function is responsible for generating a CRC value for a given data buffer using the CRC16 function
 * Usage         :
 *      Example -   generateCRC(data, Rcv_byte_cnt1);
 * Required      :  ModbusRxframe ,its length
 */

/* CRC algorithm */
uint16_t CRC16(uint16_t crc, uint16_t data)
{
    const uint16_t Poly16 = 0xA001;
    uint16_t LSB, i;
    crc = ((crc ^ data) | 0xFF00) & (crc | 0x00FF); /* EXOR the first b-bit byte of the message with the low-order byte of the 16 bit */
    for (i = 0; i < 8; i++)
    {                         /* CRC register, put the result in the CRC regsiter */
        LSB = (crc & 0x0001); /* check LSB is 1 */
        crc = crc / 2;        /*  right shift the CRC, Zero filling the MSB */

        if (LSB)
            crc = crc ^ Poly16; /*  if LSB of CRC is 1 --> EXOR with polynomial value 0xA001 */
    }
    return (crc);
}

/* Function name : uint16_t checkCRC(uint8_t * data, uint8_t Rcv_byte_cnt)
 * Return Type   : Returns either 0 or 1
 * Parameters    :
 *      data        - The Query message from the ModbusRTU
 *     Rcv_byte_cnt - length of the query frame
 *
 * Description   :
 *      The receiving device recalculates a CRC of the query message, and compares the calculated
 * value to the actual value it received in the CRC field. If the two values are not equal, an error results.
 * Usage         :
 *      Example - checkEqual = checkCRC(&p_modbusRxBuf[0], preMultiLength);
 * Required      :  modbusTcpRxBuf,byte count of received query frame
 *
 */

uint16_t checkCRC(const uint8_t *data, uint8_t Rcv_byte_cnt)
{
    uint8_t Rcv_byte_cnt1 = 0;
    uint16_t Rcv_Data_CRC = 0;
    uint16_t low_byte = 0;
    uint16_t highbyte = 0;
    Rcv_byte_cnt1 = Rcv_byte_cnt - 2;
    Rcv_Data_CRC = generateCRC(data, Rcv_byte_cnt1);
    low_byte = getLOWbyte(Rcv_Data_CRC);
    highbyte = getHIGHbyte(Rcv_Data_CRC);

    if (low_byte == data[Rcv_byte_cnt - 2] &&
        highbyte == data[Rcv_byte_cnt - 1])
    {
        return 0x01;
    }
    else
    {
        return 0x00;
    }
}
