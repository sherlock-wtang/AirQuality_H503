/**
*@filename: AirQuality.h
*@note:
*
**/

#ifndef __AIRQUALITY_H__
#define __AIRQUALITY_H__

/*-------------------------------INCLUDE FILES------------------------*/

/*-------------------------------DEFINITION---------------------------*/

/*-------------------------------GLOBAL VARIABLES---------------------*/

/*-------------------------------GLOBAl PROTOTYPE---------------------*/
extern void AirQuality_USART_Tx(UART_HandleTypeDef huart, BYTE *pbyTxData);
extern void AirQuality_RoutineTask_Startup(void);
extern void AirQuality_RoutineTask(void);
extern void AirQuality_RoutineTask_Body(void);

#endif /*__AIRQUALITY_H__*/
/*-------------------------------EOF---------------------------------*/