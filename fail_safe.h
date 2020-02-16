#pragma once
#include <stdio.h>
#include "StubFunc.h"

#define ARRAY_LENGTH(array) (sizeof(array) / sizeof(array[0]))

/*****************************************************************
* テーブル                                                       *
*****************************************************************/
typedef enum{
    AA,
    BB,
    CC,
    /* Aurix */
    SYS1,
    SYS2,
    TC,
    VMS,
    /* R-Car */
    RC,
    RP,
    DM1,
    DM2,
    DM3,
    DM4,
    PP1,
    PP2,
    /* Other */
    XX,
    YY,
    MICON_TYPE_NUM
} MiconType;

typedef enum{
    /* 故障診断種別 */
    CAN_SEND,
    CAN_REV,
    CAN_CLOCK,
    EARHER_REV,
    EARHER_CLOCK,
    FAIL_TYPE_INFO_NUM,
} FAIL_TYPE_INFO;

typedef enum{
    /* Can Node CH */
    NODE1 = 11,
    NODE2 = 22, 
    NODE3 = 33, 
    NODE4 = 44, 
    NODE5 = 55, 
    NODE6 = 66, 
    NODE_CH_INFO_NUM,
} Node_Ch_Info;

typedef enum{
    /* Can Recv ID */
    CanID1 = 121,
    CanID2 = 122,
    CanID3 = 123,
    TC_ID_MAX,
    TC_ID_NUM = TC_ID_MAX - CanID1
} Can_Recv_ID_Table_TC;

typedef enum{
    /* Can Recv ID */
    CanID4 = 124,
    VMC_ID_MAX,
    VMC_ID_NUM = VMC_ID_MAX - CanID4
} Can_Recv_ID_Table_VMC;

typedef enum{
    /* R-Car */
    EARHER1, 
    EARHER_INFO_NUM,
} EARHER_INFO;

typedef struct ID_table{
        uint8_t size;
        uint8_t* const array;
}ID_Table;

/*=================================================================================================================*/
/* START OF GLOBAL VARIABLES */
/*=================================================================================================================*/
extern uint8_t g_FailState[FAIL_TYPE_INFO_NUM];
extern uint16_t power_On;

/*=================================================================================================================*/
/* START OF LOCAL DATA DECLARATIONS */
/*=================================================================================================================*/
static const uint8_t Flag_Off         = 0;
static const uint8_t Flag_On          = 1;
static const uint8_t Err_Off          = 0;
static const uint8_t Err_On           = 1;
static const uint8_t v_CanSendTh      = 3;
static const uint8_t v_CanRecvTh      = 3;
static const uint8_t v_CanClockTh     = 3;
static const uint8_t CAN_SEND_DATA    = 0x12;
static const uint8_t CAN_REV_DATA     = 0x13;
static const uint8_t CAN_CLOCK_DATA   = 0x14;
static const uint16_t Power_On_thr    = 1000;
static const uint8_t MiconType_Offset = 5;


/*=================================================================================================================*/
/* [START OF FUNCTIONS  DECLARATIONS] */
/*=================================================================================================================*/
void f_CANRecv_set(void);
void f_CANClock_set(ID_Table* const ID_Info, uint8_t Type_Aurix, const uint8_t* Can_Recv_Result);