#include "testhead.h"

void printfunction()
{

    switch (ModbusRxBuf[7])
    {
    case 0x03:
        printf(ANSI_COLOR_BLUE "\nReadHolding");
        break;
    case 0x06:
        printf(ANSI_COLOR_BLUE "\nPresetSingle");
        break;
    case 0x10:
        printf(ANSI_COLOR_BLUE "\nPresetMultiple");
        break;
    }
    printf(ANSI_COLOR_RESET "\nQuery Packet:%d", incrs + 1);

    if (ModbusTxBuf[7] > 0x80)
    {
        switch (ModbusTxBuf[8])
        {
        case 1:
            printf(ANSI_COLOR_ORANGE " - Function Error ");
            break;
        case 2:
            printf(ANSI_COLOR_ORANGE " - Address Error ");
            break;
        case 3:
            printf(ANSI_COLOR_ORANGE " - Data Error ");
            break;
        }
    }

#ifdef result

    printf(ANSI_COLOR_RESET "\n");
    printf("Number of packets to send: %d\n", ModbusTxLength);

    for (int i = 0; i < ModbusRxBuftest[incrs][0]; i++)
        printf("%02X ", ModbusRxBuf[i]);
    printf("\n");

    printf("Expected Response:\n");
    for (int i = 0; i < Test_TXtest[incrs][0]; i++)
        printf("%02X ", Test_tx[i]);
    printf("\n");

    printf("Actual Response:\n");
    int responseLength = (ModbusTxBuf[7] == 0x06 || ModbusTxBuf[7] == 0x10 || ModbusTxBuf[7] == 0x05 || ModbusTxBuf[7] == 0x0f) ? 0x0C : ((ModbusTxBuf[7] < 0x80) ? 0x09 + ModbusTxBuf[8] : 0x09);
    for (int i = 0; i < responseLength; i++)
        printf("%02X ", ModbusTxBuf[i]);
    printf("\n");

#endif

    printf(Test_Res == 1 ? ANSI_COLOR_GREEN " Test Passed" : ANSI_COLOR_RED " Test failed\n");

    if (ModbusRxBuf[7] == 0x6 || ModbusRxBuf[7] == 0x10 || ModbusTxBuf[7] == 0x05 || ModbusRxBuf[7] == 0x0f)

        printf(testcheck == 1 ? ANSI_COLOR_RED " - Data not Entered" : ANSI_COLOR_GREEN " - Data Entered");

    printf("\n");
    printf(ANSI_COLOR_RESET); // Reset color to default
    printf("\n");
    printf("***********************************************************************************************************");
    printf("\n");
}
