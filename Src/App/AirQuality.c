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

static WORD s_wAirQualityData_STD[MAX_PAST_DATA][6];

static BYTE s_byRawData_STD[ROUTINE_DATA_QUANTITY - 9] = {0};
// static BYTE s_byRawData_PM_ALL[MAX_PAST_DATA][PM_ALL_DATA_QUANTITY - 9] = {0};
// static BYTE s_byRawData_PM_TSI[MAX_PAST_DATA][PM_ALL_DATA_QUANTITY - 9] = {0};

static BYTE s_byCurrentDataSeq = 0;

/*-------------------------------GLOBAl PROTOTYPE---------------------*/
void AirQuality_USART_Tx(UART_HandleTypeDef huart, BYTE *pbyTxData);
void AirQuality_RoutineService(void);

/*-------------------------------LOCAL PROTOTYPE---------------------*/

/*-------------------------------FUNCTION CONTENTS-------------------*/

/*--------------------------------
@Function:
@Description:
@Return Value:
@Note:
-------------------------------*/
void AirQuality_RoutineService(void)
{
    PTQS_FetchData_Routine(s_byRawData_STD);
    /*PM2.5 ug/m3*/
    s_wAirQualityData_STD[s_byCurrentDataSeq][0] = ((s_byRawData_STD[0] << 8) | s_byRawData_STD[1]);
    /*TVOC ppm*/
    s_wAirQualityData_STD[s_byCurrentDataSeq][1] = ((s_byRawData_STD[2] << 8) | s_byRawData_STD[3]) / 100;
    /*HCHO mg/m3*/
    s_wAirQualityData_STD[s_byCurrentDataSeq][2] = ((s_byRawData_STD[5] << 8) | s_byRawData_STD[6]) / 100;
    /*CO2 ppm*/
    s_wAirQualityData_STD[s_byCurrentDataSeq][3] = ((s_byRawData_STD[8] << 8) | s_byRawData_STD[9]);
    /*Temperature*/
    s_wAirQualityData_STD[s_byCurrentDataSeq][4] = ((s_byRawData_STD[10] << 8) | s_byRawData_STD[11]) / 10;
    /*Humidity*/
    s_wAirQualityData_STD[s_byCurrentDataSeq][5] = ((s_byRawData_STD[12] << 8) | s_byRawData_STD[13]) / 10;

    s_byCurrentDataSeq++;
    if (s_byCurrentDataSeq == MAX_PAST_DATA)
    {
        s_byCurrentDataSeq = 0;
    }
}

/*--------------------------------
@Function:
@Description:
@Return Value:
@Note:
-------------------------------*/
void AirQuality_USART_Tx(UART_HandleTypeDef huart, BYTE *pbyTxData)
{

}
/*-------------------------------EOF---------------------------------*/
