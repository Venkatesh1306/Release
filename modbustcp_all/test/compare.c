#include "testhead.h"
// function for testing the output with the expected output
uint16_t Test_ing(const uint8_t ModbusTxBuf[], const uint8_t Test_tx[])
{
    Test_Res = 1;
    test_c = 0;

    // Data enter check for FC 0x06
    if (ModbusRxBuf[7] == 0x06)
    {
        add = (ModbusRxBuf[8] << 8) | ModbusRxBuf[9];
        test_c = (Dataregister[add] != ((ModbusRxBuf[10] << 8) | ModbusRxBuf[11])) ? 1 : 0;
    }

    // Data enter check for FC  0x10
    if (ModbusRxBuf[7] == 0x10)
    {
        add = (ModbusRxBuf[8] << 8) | ModbusRxBuf[9];
        numRegisters = (ModbusRxBuf[10] << 8) | ModbusRxBuf[11];

        for (increment = 0; increment < numRegisters; increment++)
        {
            receivedData = (ModbusRxBuf[13 + increment * 2] << 8) | ModbusRxBuf[14 + increment * 2];
            test_c = (Dataregister[add + increment] != receivedData) ? 1 : 0;
        }
    }

    // Data enter check for FC  0x05
    if (ModbusRxBuf[7] == 0x05)
    {

        int reg = (ModbusRxBuf[9] - 1) / 16;
        int bit = (ModbusRxBuf[9] - 1) % 16;
        //printf("\n before -- %04x - %04x", Dataregister[reg], COIL1[reg]);
        if (ModbusRxBuf[10] == 0xff)
        {
            SET(COIL1[reg], bit);
        }
        else
        {
            CLR(COIL1[reg], bit);
        }
        //printf("\n change -- %04x - %04x", Dataregister[reg], COIL1[reg]);
        test_c = (Dataregister[reg] != COIL1[reg]) ? 1 : 0;
        printf("%d",test_c);
    }

    if (ModbusRxBuf[7] == 0x0f)
    {
        unsigned int bit_count, reg, regbit, a, b, d;
        uint16_t c[25];

        for (int i = 0; i < ModbusRxBuf[12]; i++)
        {
            c[i] = (ModbusRxBuf[(i * 2) + 14] << 8) | ModbusRxBuf[(i * 2) + 13];
        }

        for (bit_count = ModbusRxBuf[11] - 1; bit_count >= 0; bit_count--)
        {
            regbit = ((ModbusRxBuf[9] + bit_count) - 1) % 16;
            reg = ((ModbusRxBuf[9] + bit_count) - 1) / 16;
            //printf("\n before -- %04x - %04x", Dataregister[reg], COIL1[reg]);
            a = bit_count % 16;
            b = bit_count / 16;

            d = GET_BIT(c[b], a);

            if (d == 0x1)
            {
                SET(COIL1[reg], regbit);
            }
            else
            {
                CLR(COIL1[reg], regbit);
            }
            if (bit_count == 0)
            {
                break;
            }
        }
        reg = ((ModbusRxBuf[9] + bit_count) - 1) / 16;
        for (int i = reg; i <= reg + (ModbusRxBuf[12] / 2); i++)
        {
            //printf("\n change -- %04x--%04x  ", Dataregister[i], COIL1[i]);
            if ((Dataregister[i] != COIL1[i]))
            {
                test_c = 1;
                break;
            }
        }
    }

    numRegisters = (ModbusTxBuf[7] < 0x80) ? (0x06 + ModbusTxBuf[5]) : 0x09;
    // send packet check for all function code
    for (increment = 0; increment < numRegisters; increment++)
    {
        // Test_Res = (ModbusTxBuf[increment] != Test_tx[increment]) ? 0 : 1;
        if ((ModbusTxBuf[increment] != Test_tx[increment]))
        {
            Test_Res = 0;
            break; // Exit the loop or block
        }
    }

    return Test_Res;
}
