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
    NODE1, // SYS1
    //NODE2, // SYS2
    //NODE3, // SYS2
    //NODE4, // TC
    //NODE5, // VMC
    //NODE6, // VMC
    NODE_SYS1_INFO_NUM,
} NODE_SYS1_INFO;

typedef enum{
    /* Can Node ID */
    //NODE1, // SYS1
    NODE2, // SYS2
    NODE3, // SYS2
    //NODE4, // TC
    //NODE5, // VMC
    //NODE6, // VMC
    NODE_SYS2_INFO_NUM,
} NODE_SYS2_INFO;

typedef enum{
    /* R-Car */
    EARHER1, 
    EARHER_INFO_NUM,
} EARHER_INFO;

/*******************************
* Global Value                 *
*******************************/
extern char g_FailState[FAIL_TYPE_INFO_NUM];

/*******************************
* 定数                         *
*******************************/
static const unsigned char v_CanSendTh = 3;

/*******************************
* プロトタイプ宣言             *
*******************************/
void f_CanSend_set(MICON_INFO Micon_Info);
void Cmd_CanSend_set_SYS1(MICON_INFO Micon_Info, char* const FailFlag);
void Cmd_CanSend_set_SYS2(MICON_INFO Micon_Info, char* const FailFlag);
void Cmd_TC();
void Cmd_VMS();
// スタブ API：Can未送信IDの状態を取得
char f_GetCanSend_API(int CanID);
void Cmd_CanSend_set_Internal(const int* v_NodeCHTable, int* const v_APIResult, int* const v_ErrCnt, const MICON_INFO v_MiconInfo, char* const FailFlag);
#endif