/*
*@filename: common.h
*@description: 
*@note:
*
*/

/*-------------------------------INCLUDE FILES------------------------*/
#include "Error.h"
#include "main.h"

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

/*-------------------------------EOF---------------------------------*/
