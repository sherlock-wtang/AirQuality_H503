/*
 *@filename: AirQuality.c
 *@description:
 *@note:
 *
 */

/*-------------------------------INCLUDE FILES------------------------*/
#include "AppMain.h"

/*-------------------------------DEFINITION---------------------------*/
#define MAX_PAST_DATA (5)

/*-------------------------------GLOBAL VARIABLES---------------------*/

/*-------------------------------LOCAL VARIABLES----------------------*/

static FLOAT s_fTemperatureData[MAX_PAST_DATA][2];
static BYTE s_byRawData_DHT20[6] = {0};
static BYTE s_byCurrentDataSeq = 0;

/*-------------------------------GLOBAl PROTOTYPE---------------------*/
void Temperature_RoutineService(void);

/*-------------------------------LOCAL PROTOTYPE---------------------*/

/*-------------------------------FUNCTION CONTENTS-------------------*/

/*--------------------------------
@Function:
@Description:
@Return Value:
@Note:
-------------------------------*/
void Temperature_RoutineService(void)
{
    DHT_FetchData_Routine(s_byRawData_DHT20);

    /*Humidity*/
    s_fTemperatureData[s_byCurrentDataSeq][0] = ((float)((s_byRawData_DHT20[1] << 12) | (s_byRawData_DHT20[2] << 4) | (s_byRawData_DHT20[3] >> 4)) * 100) / 1048576;

    /*Temperature*/
    s_fTemperatureData[s_byCurrentDataSeq][1] = (((float)(((s_byRawData_DHT20[3] & 0b00001111) << 16) | (s_byRawData_DHT20[4] << 8) | (s_byRawData_DHT20[5])) * 200) / 1048576) - 50;

    s_byCurrentDataSeq++;
    if (s_byCurrentDataSeq == MAX_PAST_DATA)
    {
        s_byCurrentDataSeq = 0;
    }
    return;
}

/*--------------------------------
@Function:
@Description:
@Return Value:
@Note:
-------------------------------*/
void Temperature_USART_Tx(UART_HandleTypeDef huart, BYTE *pbyTxData)
{
}
/*-------------------------------EOF---------------------------------*/
