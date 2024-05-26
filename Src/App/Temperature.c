/**
 *@filename: AirQuality.c
 *@description:
 *@note:
 *
 **/

/*-------------------------------INCLUDE FILES------------------------*/
#include "AppMain.h"
#include "__DriverMain.h"
#include "task.h"

/*-------------------------------DEFINITION---------------------------*/
#define MAX_PAST_DATA (5)

/*-------------------------------GLOBAL VARIABLES---------------------*/
TaskHandle_t* taskH_Temperature;
/*-------------------------------LOCAL VARIABLES----------------------*/

static FLOAT s_fTemperatureData[MAX_PAST_DATA][2];
static BYTE s_byRawData_DHT20[6] = {0};
static BYTE s_byCurrentDataSeq = 0;

/*-------------------------------GLOBAl PROTOTYPE---------------------*/
void Temperature_RoutineService(void);
void Temperature_RoutineTask_Startup(void);
void Temperature_RoutineTask_Body(void);

/*-------------------------------LOCAL PROTOTYPE---------------------*/

/*-------------------------------FUNCTION CONTENTS-------------------*/

/*******************************
 @name   :
 @brief  :
 @param  :
 @return :
 @note   :
*******************************/
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

/*******************************
 @name   :
 @brief  :
 @param  :
 @return :
 @note   :
*******************************/
void Temperature_RoutineTask_Body(void)
{
    while(1)
    {
        Temperature_RoutineService();
        vTaskDelay(pdMS_TO_TICKS(45));
    }
}

/*******************************
 @name   :
 @brief  :
 @param  :
 @return :
 @note   :
*******************************/
void Temperature_RoutineTask_Startup(void)
{
    xTaskCreate((void *)Temperature_RoutineTask_Body, "Temperature", STANDARD_TASK_STACK, NULL, osPriorityLow, taskH_Temperature);
    return;
}

/*******************************
 @name   :
 @brief  :
 @param  :
 @return :
 @note   :
*******************************/
void Temperature_USART_Tx(UART_HandleTypeDef huart, BYTE *pbyTxData)
{
}
/*-------------------------------EOF---------------------------------*/
