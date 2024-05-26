/*
 *@filename: AirQuality.c
 *@description:
 *@note:
 *
 */

/*-------------------------------INCLUDE FILES------------------------*/
#include "common.h"
#include "__DriverMain.h"
#include "task.h"

/*-------------------------------DEFINITION---------------------------*/
#define MAX_PAST_DATA (5)

/*-------------------------------GLOBAL VARIABLES---------------------*/
TaskHandle_t* taskH_AirQualityRoutineTask;

/*-------------------------------LOCAL VARIABLES----------------------*/

static WORD s_wAirQualityData_STD[MAX_PAST_DATA][6];

static BYTE s_byRawData_STD[ROUTINE_DATA_QUANTITY - 9] = {0};
// static BYTE s_byRawData_PM_ALL[MAX_PAST_DATA][PM_ALL_DATA_QUANTITY - 9] = {0};
// static BYTE s_byRawData_PM_TSI[MAX_PAST_DATA][PM_ALL_DATA_QUANTITY - 9] = {0};

static BYTE s_byCurrentDataSeq = 0;

/*-------------------------------GLOBAl PROTOTYPE---------------------*/
void AirQuality_USART_Tx(UART_HandleTypeDef huart, BYTE *pbyTxData);
void AirQuality_RoutineTask_Startup(void);
void AirQuality_RoutineTask(void);
void AirQuality_RoutineTask_Body(void);

/*-------------------------------LOCAL PROTOTYPE---------------------*/

/*-------------------------------FUNCTION CONTENTS-------------------*/
/*******************************
 @name   : AirQuality_RoutineTask_Body
 @brief  : AirQuality Fetch Data Routine
 @param  :
 @return :
 @note   : When RTOS is not used, Call this function directly
*******************************/
void AirQuality_RoutineTask_Body(void)
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

/*******************************
 @name   :
 @brief  :
 @param  :
 @return :
 @note   :
*******************************/
void AirQuality_RoutineTask(void)
{
    while (1)
    {
        AirQuality_RoutineTask_Body();
        vTaskDelay(pdMS_TO_TICKS(50));
    }
}

/*******************************
 @name   :
 @brief  :
 @param  :
 @return :
 @note   :
*******************************/
void AirQuality_RoutineTask_Startup(void)
{
    xTaskCreate((void *)AirQuality_RoutineTask, "AQ_R", STANDARD_TASK_STACK, NULL, osPriorityLow, taskH_AirQualityRoutineTask);
    return;
}

/*******************************
 @name   :
 @brief  :
 @param  :
 @return :
 @note   :
*******************************/
void AirQuality_USART_Tx(UART_HandleTypeDef huart, BYTE *pbyTxData)
{

}
/*-------------------------------EOF---------------------------------*/
