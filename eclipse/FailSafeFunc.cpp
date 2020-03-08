/*
 * FailSafeFunc.cpp
 *
 *  Created on: 2020/03/07
 *      Author:
 */

#include "FailSafeFunc.h"
using namespace std;

#define DEBUG_PRINT

#define CAN_MESSAGE_AD_TC_NUM 3
#define CAN_MESSAGE_AD_VMC_NUM 2

static uint8_t g_FailState[FAIL_STATE_TYPE_NUM] = {0};
static const uint8_t m_CanRecvTh = 3;
static const uint8_t Can_Rec_State = 0x11;
static const uint16_t Power_On_thr = 1000;
uint16_t power_On = 1001;

void FailSafeCheck()
{
	MCUType Micon = AD_TC;
	f_CANFailInfo_set(Micon);
}

void f_CANFailInfo_set(MCUType Micon)
{
	MCUType_Convert Can_Racv_Info[MCU_TYPE_NUM] = {
			{AD_SYS1, CAN_RECV_INVALID},
			{AD_SYS2, CAN_RECV_INVALID},
			{AD_TC, CAN_RECV_AD_TC},
			{AD_VMC, CAN_RECV_AD_VMS},
	};

    /* CanMessageType AD_TC */
	CAN_MESSAGE_TYPE Can_Recv_AD_TC_Array[CAN_MESSAGE_AD_TC_NUM] = {
    		CAN_RECEV1,
			CAN_RECEV2,
			CAN_RECEV6
    };

    /* CanMessageType AD_VMC */
	CAN_MESSAGE_TYPE Can_Recv_AD_VMC_Array[CAN_MESSAGE_AD_VMC_NUM] = {
    		CAN_RECEV5,
			CAN_RECEV8
    };

    /* CanMessageType Array */
    ID_Table Can_Recv_Table[CAN_RECV_MCUTYPE_NUM] = {
        { CAN_MESSAGE_AD_TC_NUM, Can_Recv_AD_TC_Array },
        { CAN_MESSAGE_AD_VMC_NUM, Can_Recv_AD_VMC_Array }
    };

    /* Error_Result  */
    bool f_CANRecv_Err_AD_TC[CAN_MESSAGE_AD_TC_NUM] = {0};
    bool f_CANRecv_Err_AD_VMC[CAN_MESSAGE_AD_VMC_NUM] = {0};
    bool* f_CANRecv_Err[2] = { f_CANRecv_Err_AD_TC, f_CANRecv_Err_AD_VMC };

    f_CANRecv_set(Can_Racv_Info[Micon].CanRecv_Type, Can_Recv_Table, f_CANRecv_Err);
}

void f_CANRecv_set(CanRecv_MCUType Micon,  const ID_Table* const Message_Table, bool* const Error_Result[])
{

    uint8_t i = 0;

    /* Declarations */
    /* v_CANRecv_Mon */
    uint8_t v_CANRecv_Mon_AD_TC[CAN_MESSAGE_AD_TC_NUM] = {0};
    uint8_t v_CANRecv_Mon_AD_VMC[CAN_MESSAGE_AD_VMC_NUM] = {0};
    uint8_t* v_CANRecv_Mon[CAN_RECV_MCUTYPE_NUM] = {v_CANRecv_Mon_AD_TC, v_CANRecv_Mon_AD_VMC};

    /* Declarations */
    /* l_CANRecvErrCnt */
    static uint8_t l_CANRecvErrCnt_AD_TC[CAN_MESSAGE_AD_TC_NUM] = {0};
    static uint8_t l_CANRecvErrCnt_AD_VMC[CAN_MESSAGE_AD_VMC_NUM] = {0};
    uint8_t* l_CANRecvErrCnt[CAN_RECV_MCUTYPE_NUM] = {l_CANRecvErrCnt_AD_TC, l_CANRecvErrCnt_AD_VMC};

    /* Declarations */
    /* CANRecv_Fail */
    static bool CANRecv_Fail_AD_TC[CAN_MESSAGE_AD_TC_NUM] = {0};
    static bool CANRecv_Fail_AD_VMC[CAN_MESSAGE_AD_VMC_NUM] = {0};
    bool* CANRecv_Fail[CAN_RECV_MCUTYPE_NUM] = {CANRecv_Fail_AD_TC, CANRecv_Fail_AD_VMC};

    for(i=0 ; i < Message_Table[Micon].size; i++)
    {
    	/* Get API */
    	v_CANRecv_Mon[Micon][i] = Stub_GetCANRecv(Message_Table[Micon].array[i]);

    	cout << "[GET_API] v_CANRecv_Mon = " << (int)v_CANRecv_Mon[Micon][i] << endl;
    	/* API Judgment*/
    	Error_Result[Micon][i] = !(v_CANRecv_Mon[Micon][i] == 0) ? 1 : 0;
    	cout << "[API_JUDGMENT] Error_Result = " << Error_Result[Micon][i] << endl;

        /* Prohibition Fail */
        if(!(CANRecv_Fail[Micon][i] == 0))
        {
        	// Do Nothing
        	cout << "[PROHIBITION] CANRecv_Fail = " << (int)CANRecv_Fail[Micon][i] << endl;
        	return;
        }
        /* Prohibition Power_On_thr */
        else if(power_On < Power_On_thr)
        {
        	l_CANRecvErrCnt[Micon][i] = 0;
        	return;
        }
        else
        {
        	/* Error Judgment */
        	l_CANRecvErrCnt[Micon][i] = !(Error_Result[Micon][i] == 0) ? l_CANRecvErrCnt[Micon][i] + 1 : 0;
        	cout << "[ERR_JUDGMENT] l_CANRecvErrCnt = " << (int)l_CANRecvErrCnt[Micon][i] << endl;
        	/* Fail Judgment */
        	if(l_CANRecvErrCnt[Micon][i] >= m_CanRecvTh)
        	{
        		CANRecv_Fail[Micon][i] = 1;
        		cout << "[FAIL_JUDGMENT] CANRecv_Fail = " << CANRecv_Fail[Micon][i] << endl;
        	}
        	else
        	{
        		// Do Nothing
        	}
        }
    }

    for(i=0 ; i < Message_Table[Micon].size; i++)
    {
    	g_FailState[CAN_RECV_STATE] = !(CANRecv_Fail[Micon][i]== 0) ? Can_Rec_State : 0;
    	cout << "[G_FAILSTATE] g_FailState= " << (int)g_FailState[CAN_RECV_STATE] << endl;
    }
}
