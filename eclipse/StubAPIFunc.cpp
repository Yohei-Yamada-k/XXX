/*
 * StubAPIFunc.cpp
 *
 *  Created on: 2020/03/08
 *      Author:
 */

#include "StubAPIFunc.h"

uint8_t g_GetCANRecv = 0;

uint8_t Stub_GetCANRecv(CAN_MESSAGE_TYPE Msg){

    return g_GetCANRecv ? 1 : 0;
}

uint8_t Stub_GetCANRecv_StartFail(CAN_MESSAGE_TYPE Msg)
{

	/* VMC */
	if(Msg == CAN_RECEV5)
	{
		return 1;
	}
    return 0;
}
