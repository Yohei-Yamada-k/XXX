#pragma once
#include "fail_safe.h"

/*******************************
* テーブル                     *
*******************************/


/*******************************
* Global Value                 *
*******************************/
extern uint8_t g_Call_CanSend;
extern uint8_t g_Call_CanRecv;
extern uint8_t g_Call_GetMiconType;

/*******************************
* 定数                         *
*******************************/
static const uint8_t API_Normal = 0;
static const uint8_t API_Err    = 1;

/*================================
* プロトタイプ宣言               *
*===============================*/
uint8_t Stub_CallAPI_CanSend(uint32_t CanID);
uint8_t Stub_CallAPI_CanRecv(uint8_t CanID);
uint8_t Stub_CallAPI_CanClock(uint8_t CanID);
uint8_t Stub_CallFunc_GetMiconType();
void Func_Test();
