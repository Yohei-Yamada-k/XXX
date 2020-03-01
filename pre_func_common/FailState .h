#pragma once
#include "fail_safe.h"
#define DEBUG_REQUIREMENTS

typedef enum{
    /* 故障診断種別 */
    CAN_SEND,
    CAN_REV,
    CAN_CLOCK,
    EARHER_REV,
    EARHER_CLOCK,
    FAIL_TYPE_INFO_NUM,
} FAIL_TYPE_INFO;

uint8_t g_FailState_get(FAIL_TYPE_INFO Type);
void g_FailState_set(uint8_t StateData, FAIL_TYPE_INFO Type);