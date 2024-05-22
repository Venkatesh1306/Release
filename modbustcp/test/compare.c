#include "testhead.h"
// function for testing the output with the expected output
uint16_t Test_ing(const uint8_t ModbusTxBuf[], const uint8_t Test_tx[])
{

    Test_Res = 1;

    numRegisters = (ModbusTxBuf[7] < 0x80) ? (0x09 + ModbusTxBuf[8]) : 0x09;
    // send packet check for all function code
    for (increment = 0; increment < numRegisters; increment++)
    {
        if ((ModbusTxBuf[increment] != Test_tx[increment]))
        {
            Test_Res = 0;
            break; // Exit the loop or block
        }
    }

   testcheck = 0;

    // Data enter check for FC 0x06
    if (ModbusRxBuf[7] == 0x06)
    {
        add = (ModbusRxBuf[8] << 8) | ModbusRxBuf[9];
       testcheck = (Dataregister[add] != ((ModbusRxBuf[10] << 8) | ModbusRxBuf[11])) ? 1 : 0;
    }

    // Data enter check for FC  0x10
    if (ModbusRxBuf[7] == 0x10)
    {
        add = (ModbusRxBuf[8] << 8) | ModbusRxBuf[9];
        numRegisters = (ModbusRxBuf[10] << 8) | ModbusRxBuf[11];

        for (increment = 0; increment < numRegisters; increment++)
        {
            receivedData = (ModbusRxBuf[13 + increment * 2] << 8) | ModbusRxBuf[14 + increment * 2];
           testcheck = (Dataregister[add + increment] != receivedData) ? 1 : 0;
        }
    }

    return Test_Res;
}
