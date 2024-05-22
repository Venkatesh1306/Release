#include "testhead.h"

void printfunction()
{
   
    switch (ModbusRxBuf[1])
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
    if (mbTxBuf[1] > 0x80)
    {
        switch (mbTxBuf[2])
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
    for (int i = 0; i < textTxts[incrs][0]; i++)
        printf("%02X ", testTxBuf[i]);
    printf("\n");

    printf("Actual Response:\n");
    int responseLength = (mbTxBuf[1] == 0x06 || mbTxBuf[1] == 0x10 || mbTxBuf[1] == 0x05 || mbTxBuf[1] == 0x0f) ? 0x08 : ((mbTxBuf[1] < 0x80) ? 0x05 + mbTxBuf[2] : 0x05);
    for (int i = 0; i < responseLength; i++)
        printf("%02X ", mbTxBuf[i]);
    printf("\n");

#endif

    printf(Test_Res == 1 ? ANSI_COLOR_GREEN "Test Passed" : ANSI_COLOR_RED "Test failed\n");

    if (ModbusRxBuf[1] == 0x6 || ModbusRxBuf[1] == 0x10 || mbTxBuf[1] == 0x05 || ModbusRxBuf[1] == 0x0f)

        printf(test_c == 1 ? ANSI_COLOR_RED " - Data not Entered" : ANSI_COLOR_GREEN " - Data Entered");

    printf("\n");
    printf(ANSI_COLOR_RESET); // Reset color to default
}
