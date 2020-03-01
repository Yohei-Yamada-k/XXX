#include "FailState .h"

#define DEBUG_REQUIREMENTS

static uint8_t g_FailState[FAIL_TYPE_INFO_NUM] = {0};

uint8_t g_FailState_get(FAIL_TYPE_INFO Type)
{
    return g_FailState[Type];
}

void g_FailState_set(uint8_t StateData, FAIL_TYPE_INFO Type)
{
    g_FailState[Type] = StateData;
}