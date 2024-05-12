/*
 *@filename: AppMain.c
 *@description:
 *@note:
 *
 */

/*-------------------------------INCLUDE FILES------------------------*/
#include "__DriverMain.h"
#include "AppMain.h"
/*-------------------------------DEFINITION---------------------------*/

/*-------------------------------GLOBAL VARIABLES---------------------*/

/*-------------------------------LOCAL VARIABLES----------------------*/

/*-------------------------------GLOBAl PROTOTYPE---------------------*/

/*-------------------------------LOCAL PROTOTYPE---------------------*/

/*-------------------------------FUNCTION CONTENTS-------------------*/

void AppMain(void)
{
    DHT_Startup();

    while (1)
    {
         AirQuality_RoutineService();
         Temperature_RoutineService();
    }
}

/*-------------------------------EOF---------------------------------*/
