/*
 * StubAPIFunc.h
 *
 *  Created on: 2020/03/08
 *      Author:
 */

#ifndef STUBAPIFUNC_H_
#define STUBAPIFUNC_H_

#include <cstdint>
#include "FailSafeFunc.h"
#include "CanMsgType.h"

extern uint8_t g_GetCANRecv;

uint8_t Stub_GetCANRecv(CAN_MESSAGE_TYPE Msg);
uint8_t Stub_GetCANRecv_StartFail(CAN_MESSAGE_TYPE Msg);

#endif /* STUBAPIFUNC_H_ */
