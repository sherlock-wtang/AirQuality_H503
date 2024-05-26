/**
 *@filename: PTQS1005.c
 *@description:
 *@note:
 *
 **/

/*-------------------------------INCLUDE FILES------------------------*/
#include "__DriverMain.h"

/*-------------------------------DEFINITION---------------------------*/
#define COM_MODE_USART (TRUE) /* TRUE = USART, FALSE = I2C */
#define UART_PORT (&huart1)
#define COM_TIMEOUT (100)

/*-------------------------------GLOBAL VARIABLES---------------------*/

/*-------------------------------LOCAL VARIABLES----------------------*/
/*CMD:
FIX1: 0x42
FIX2: 0x4D
MODE: 0xAB = STD MODE, 0xAC = PM_ALL, 0xAD = PM_TSI
*/
static const BYTE sc_byCMD_STD[8] = {0x42, 0x4D, 0xAB, 0x00, 0x00, 0x01, 0x3A};
// static BYTE s_byCMD_PM_ALL = {0x42,0x4D,0xAC,0x00,0x00,};
// static BYTE s_byCMD_PM_TSI = {0x42,0x4D,0xAD,0x00,0x00,};

/*-------------------------------GLOBAl PROTOTYPE---------------------*/
void PTQS_FetchData_Routine(BYTE *pbyData);

/*-------------------------------LOCAL PROTOTYPE---------------------*/

/*-------------------------------FUNCTION CONTENTS-------------------*/
void PTQS_FetchData_Routine(BYTE *pbyData)
{
    BYTE byRxData_Buf[24] = {0};
    WORD wCheckSum = 0;

#if (COM_MODE_USART)
    HAL_UART_Transmit(UART_PORT, &sc_byCMD_STD[0], 7, COM_TIMEOUT);
    HAL_UART_Receive(UART_PORT, &byRxData_Buf[0], ROUTINE_DATA_QUANTITY, COM_TIMEOUT);

    if ((byRxData_Buf[0] != 0x42) || (byRxData_Buf[1] != 0x4D)) /*Unknown Response or Noise*/
    {
        /*@TODO Error Management*/
        return;
    }

    /*HAL_UART_Receive already handled the data quantity expectation, thus further error managment is not needed*/
    WORD wReceivedSum = ((byRxData_Buf[22] << 8) | byRxData_Buf[23]);
    for (BYTE byIndex = 0; byIndex < 22; byIndex++)
    {
        wCheckSum += byRxData_Buf[byIndex];
    }
    if (wCheckSum != wReceivedSum)
    {
        /*@TODO Error Management*/
        return;
    }

    for (BYTE byIndex = 0; byIndex < 14; byIndex++)
    {
        pbyData[byIndex] = byRxData_Buf[byIndex + 4];
    }

#elif /*COM_MODE_I2C*/

#endif

    return;
}

/*-------------------------------EOF---------------------------------*/
