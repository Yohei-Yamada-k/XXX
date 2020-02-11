#ifndef _FAIL_SAFE_H_
#define _FAIL_SAFE_H_

#include <stdio.h>

#define ARRAY_LENGTH(array) (sizeof(array) / sizeof(array[0]))

/*******************************
* テーブル                     *
*******************************/
typedef enum{
    /* Aurix */
    SYS1,
    SYS2,
    TC,
    VMS,
    MICON_INFO_NUM,
} MICON_INFO;

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
    /* Can Node ID */
    NODE1 = 11, // SYS1
    NODE2 = 22, // SYS2
    NODE3 = 33, // SYS2
    NODE4 = 44, // TC
    NODE5 = 55, // VMC
    NODE6 = 66, // VMC
    NODE_SYS1_INFO_NUM,
} NODE_SYS1_INFO;


typedef enum{
    /* R-Car */
    EARHER1, 
    EARHER_INFO_NUM,
} EARHER_INFO;


/*
typedef struct {
        int size;
        int* array;
}Msg_Table;
*/
/*******************************
* Global Value                 *
*******************************/
extern uint8_t g_FailState[FAIL_TYPE_INFO_NUM];
extern uint8_t g_TEST_FI;

/*******************************
* 定数                         *
*******************************/
static const uint8_t v_CanSendTh = 10;
static const uint8_t CAN_SEND_DATA = 0x03;

/*******************************
* プロトタイプ宣言             *
*******************************/
void f_CanSend_set(MICON_INFO Micon_Info);
uint8_t stub_f_GetCanSend(uint32_t CanID);
void test_func();
#endif