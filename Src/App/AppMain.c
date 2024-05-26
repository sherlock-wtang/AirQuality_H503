/**
 *@filename: AppMain.c
 *@description:
 *@note:
 *
 **/

/*-------------------------------INCLUDE FILES------------------------*/
#include "__DriverMain.h"
#include "AppMain.h"
/*-------------------------------DEFINITION---------------------------*/

/*-------------------------------GLOBAL VARIABLES---------------------*/

/*-------------------------------LOCAL VARIABLES----------------------*/

/*-------------------------------GLOBAl PROTOTYPE---------------------*/
void AppMain(void);
void AppMain_RTOS_Startup(void);

/*-------------------------------LOCAL PROTOTYPE---------------------*/

/*-------------------------------FUNCTION CONTENTS-------------------*/
/*******************************
 @name   : AppMain
 @brief  :
 @param  :
 @return :
 @note   :
*******************************/
void AppMain(void)
{
    DHT_Startup();

    while (1)
    {
         AirQuality_RoutineTask_Body();
         Temperature_RoutineService();
    }
}

/*******************************
 @name   : 
 @brief  :
 @param  :
 @return :
 @note   :
*******************************/
void AppMain_RTOS_Startup(void)
{
    Temperature_RoutineTask_Startup();
    AirQuality_RoutineTask_Startup();
    return;
}
/*-------------------------------EOF---------------------------------*/
