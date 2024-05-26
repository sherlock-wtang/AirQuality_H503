/**
*@filename: common.h
*@description: 
*@note:
*
**/

#ifndef __COMMON_H__
#define __COMMON_H__

/*-------------------------------INCLUDE FILES------------------------*/
#include "Error.h"
#include "compile_define.h"
#include "main.h"
#include "FreeRTOS.h"
#include "cmsis_os2.h"

/*-------------------------------DEFINITION---------------------------*/
#define BYTE uint8_t
#define WORD uint16_t
#define DWORD uint32_t
#define QWORD uint64_t

#define SBYTE int8_t
#define SWORD int16_t
#define SDWORD int32_t
#define SQWORD int64_t

#define FLOAT float
#define DOUBLE double

#define BOOL  uint8_t
#define TRUE    (1)
#define FALSE   (0)

#define NOT_UNDER_CONSTRCUTION (FALSE)

#define MAX_FREQUENCY_MHZ   (250)
#define MAX_FREQUENCY_HZ    (MAX_FREQUENCY_MHZ*1000000)
#define COM_PTQS_BAUDRATE    (9600)


/*-------------------------------GLOBAL VARIABLES---------------------*/

/*-------------------------------GLOBAl PROTOTYPE---------------------*/

#endif /*__COMMON_H__*/
/*-------------------------------EOF---------------------------------*/
