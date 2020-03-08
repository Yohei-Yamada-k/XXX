/*
 * FailSafeFunc.h
 *
 *  Created on: 2020/03/07
 *      Author:
 */

#ifndef FAILSAFEFUNC_H_
#define FAILSAFEFUNC_H_

#include <cstdint>
#include <iostream>
#include "CanMsgType.h"
#include "StubAPIFunc.h"

typedef enum{
	AD_SYS1,
	AD_SYS2,
	AD_TC,
	AD_VMC,
    MCU_TYPE_NUM
} MCUType;

typedef enum{
	CAN_RECV_INVALID = -1,
	CAN_RECV_AD_TC,
	CAN_RECV_AD_VMS,
	CAN_RECV_MCUTYPE_NUM
} CanRecv_MCUType;

typedef enum{
	FAIL_STATE_INVALID = -1,
	CAN_RECV_STATE,
	CAN_CLOCK_STATE,
	ETHER_RECV_STATE,
	ETHER_CLOCK_STATE,
	FAIL_STATE_TYPE_NUM
} FailStateType;

typedef struct{
	MCUType MCU_Type;
	CanRecv_MCUType CanRecv_Type;
}MCUType_Convert;

typedef struct{
        uint8_t size;
        CAN_MESSAGE_TYPE* array;
}ID_Table;

void FailSafeCheck();
void f_CANFailInfo_set(MCUType Micon);
void f_CANRecv_set(CanRecv_MCUType Micon_Info,  const ID_Table* const Message_Table, bool* const Error_Result[]);

#endif /* FAILSAFEFUNC_H_ */
