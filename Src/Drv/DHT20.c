/*
 *@filename: DTH20.c
 *@description:
 *@note:
 *
 */

/*-------------------------------INCLUDE FILES------------------------*/
#include "__DriverMain.h"

/*-------------------------------DEFINITION---------------------------*/
#define DTH_I2C_CHANNEL (&hi2c1)
#define DTH_I2C_TIMEOUT (1000)

#define TRIGGER_CMD_SIZE (3)
/*-------------------------------GLOBAL VARIABLES---------------------*/

/*-------------------------------LOCAL VARIABLES----------------------*/
static const BYTE sc_byDHT_ADDR = (0x38 << 1); /*Preshift for HAL Driver*/
static const BYTE sc_byCMD_Status = 0x71;
static const BYTE sc_byCMD_Trigger[3] = {0xAC, 0x33, 0x00};

/*-------------------------------GLOBAl PROTOTYPE---------------------*/
void DHT_Startup(void);
void DHT_FetchData_Routine(BYTE *pbyData);

/*-------------------------------LOCAL PROTOTYPE---------------------*/

/*-------------------------------FUNCTION CONTENTS-------------------*/
void DHT_FetchData_Routine(BYTE *pbyData)
{
    BYTE byConvStat = 0;
    BYTE byRxData_Buf[6] = {0};

    HAL_I2C_Master_Transmit(DTH_I2C_CHANNEL, sc_byDHT_ADDR, sc_byCMD_Trigger, TRIGGER_CMD_SIZE, DTH_I2C_TIMEOUT);
    HAL_Delay(100);
    HAL_I2C_Master_Transmit(DTH_I2C_CHANNEL, sc_byDHT_ADDR, &sc_byCMD_Status, 1, DTH_I2C_TIMEOUT);
    HAL_I2C_Master_Receive(DTH_I2C_CHANNEL, sc_byDHT_ADDR, &byConvStat, 1, DTH_I2C_TIMEOUT);

    if ((byConvStat & 0x80) != 0x80)
    {
        HAL_Delay(50);
        /*Conv Not Completed Yet*/
    }
    HAL_I2C_Master_Receive(DTH_I2C_CHANNEL, sc_byDHT_ADDR, pbyData, 6, DTH_I2C_TIMEOUT);
    return;
}

void DHT_Startup(void)
{
    BYTE byStartupRx_Buf = 0;
    HAL_I2C_Master_Transmit(DTH_I2C_CHANNEL, sc_byDHT_ADDR, &sc_byCMD_Status, 1, DTH_I2C_TIMEOUT);
    HAL_I2C_Master_Receive(DTH_I2C_CHANNEL, sc_byDHT_ADDR, &byStartupRx_Buf, 1, DTH_I2C_TIMEOUT);

    if (byStartupRx_Buf == 0x18)
    {
        asm("nop");
    }
    else
    {
        asm("nop");
    }

    return;
}

/*-------------------------------EOF---------------------------------*/
