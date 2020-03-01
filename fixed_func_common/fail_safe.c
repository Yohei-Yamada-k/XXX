#include "fail_safe.h"

#define DEBUG_REQUIREMENTS
//#define DEBUG_DESIGN 

#define DEBUG_COMMON
#define DEBUG_PROHIBITION
#define DEBUG_ERR
#define DEBUG_ERRTH
#define DEBUG_ERRTH_LESS
#define DEBUG_FIRST_FAIL
#define DEBUG_NORMAL
#define DEBUG_NORMAL_CNT_LESS

/*====================================================*/
/* Remark                                             */
/* @ 2020/03/01                                       */
/* f_CANRecv_setとf_CANClock_setのラッパー関数を追加  */
/* void f_CANFailInfo_set(MiconType Micon)            */
/*====================================================*/

//uint8_t g_FailState[FAIL_TYPE_INFO_NUM] = {0};
uint16_t power_On = 60001; // TBD

/*
*  Failure Info Notification Function
*  @return None
*/
void f_FailSafeCheck()
{
    MiconType Micon;

    Initialized(&Micon);
    f_CANFailInfo_set(Micon);
}

/*
*  Get MiconType Function
*  @param MiconType
*  @return None
*/
void Initialized(MiconType* const Micon)
{
    static uint8_t Initialized = 1;

    if(Initialized)
    {
        *Micon = Stub_CallFunc_GetMiconType();
        Initialized = 0;

    }
    else
    {
        // Do Nothing
    }

}

/*
*  Failure Info Notification Function(Can Not Received)
*  @return None
*/
void f_CANFailInfo_set(MiconType Micon)
{
    /* CanID_Array_MiconTYpe_TC */
    uint8_t Can_Recv_ID_TC_Array[TC_ID_NUM] = {
        CanID1,
        CanID2,
        CanID3
    };

    /* CanID_Array_MiconTYpe_VMC */
    uint8_t Can_Recv_ID_VMC_Array[VMC_ID_NUM] = {
        CanID4
    };

    /* CanID_Array Struct */
    ID_Table Can_Recv_ID_Array[2] = {
        { TC_ID_NUM, Can_Recv_ID_TC_Array },
        { VMC_ID_NUM, Can_Recv_ID_VMC_Array }
    };

    /* Err_Result Ptr Array Elements */
    uint8_t Err_Result_TC[TC_ID_NUM]    = {0};
    uint8_t Err_Result_VMC[VMC_ID_NUM]  = {0};

    /* Err_Result Ptr Array */
    uint8_t* Err_Result[2] = { Err_Result_TC, Err_Result_VMC };

    f_CANRecv_set(Micon, Can_Recv_ID_Array, Err_Result);
}

/*
*  Failure Info Notification Function(Can Not Received)
*  @return None
*/
void f_CANRecv_set(MiconType Micon,  const ID_Table* const CanID, uint8_t* const API_Array[])
{

/*=================================================================================================================*/
/* [START OF DATA DECLARATIONS] */
/*=================================================================================================================*/

    /* API_Result Ptr Array Elements */
    uint8_t API_Result_TC[TC_ID_NUM]    = {0};
    uint8_t API_Result_VMC[VMC_ID_NUM]  = {0};

    /* API_Result Ptr Array */
    uint8_t* const API_Result[2] = {API_Result_TC, API_Result_VMC};

    /* [ID Err Counter] Ptr Array Elements */
    static uint8_t Cnt_TC[TC_ID_NUM]    = {0};
    static uint8_t Cnt_VMC[VMC_ID_NUM]  = {0};

    /* [ID Err Counter] Ptr Array */
    uint8_t* const Can_Recv_Err_Cnt[2] = {Cnt_TC, Cnt_VMC};

    /* [ID Err Flag] Ptr Array Elements */
    static uint8_t Fail_Flag_TC[TC_ID_NUM]    = {0};
    static uint8_t Fail_Flag_VMC[VMC_ID_NUM]  = {0};

    /* [ID Err Flag] Ptr Array */
    uint8_t* const Can_Recv_Fail_Falg[2] = {Fail_Flag_TC, Fail_Flag_VMC};

    PtrTest(Micon, CanID, API_Array, API_Result, Can_Recv_Err_Cnt, Can_Recv_Fail_Falg);

}

void PtrTest(MiconType Micon, const ID_Table* const CanID, uint8_t* const Err_Array[], uint8_t* const API_Result_Array[], uint8_t* const Err_Cnt_Array[], uint8_t* const Fail_Flag_Array[])
{
    uint8_t i = 0;
    uint8_t TmporaryFlag = Flag_Off;

    /* Micon Type Overflow Check */
    if(Micon < 0 || Micon >= 2){

        return;
    }
    else
    {
        // Do Nothing
    }

    for(; i < CanID[Micon].size; i++)
    {
        /* [GET API] */
        API_Result_Array[Micon][i] = Stub_CallAPI_CanRecv(CanID[Micon].array[i]);

        /* [SR_REQUIREMENTS] : GET API JUDGMENT */
        Err_Array[Micon][i] = (API_Result_Array[Micon][i] == 0) ? 0 : 1;

        /* [PROHIBITION FAIL] */
        if(!(Fail_Flag_Array[Micon][i] == Flag_Off))
        {

        }
        /* [PROHIBITION POWER] */
        else if(power_On < Power_On_thr)
        {
            if(!(Err_Cnt_Array[Micon][i] == Err_Off))
            {
                Err_Cnt_Array[Micon][i] = 0;
            }
            else
            {
                // Do Nothing
            }
        }
        else
        {
            /* [ERR JUDGMENT] */
            if(!(Err_Array[Micon][i] == Err_Off))
            {
                // Err Count Up!
                Err_Cnt_Array[Micon][i]++;

                /* [FAIL JUDGMENT] */
                if(Err_Cnt_Array[Micon][i] >= v_CanRecvTh)
                {
                    /* [SR_REQUIREMENTS] : Set Fail Flag */ 
                    Fail_Flag_Array[Micon][i] = Flag_On;
                    TmporaryFlag = Flag_On; // TBD

                    /* [SET FAIL STATE CONDITION] */
                    if(Fail_Flag_Array[Micon][i])
                    {
                        /* Create Fail State */
                        g_FailState_set(CAN_REV_DATA, CAN_REV);
                    }
                    else
                    {
                        // Do Nathig
                    }
                }
                else
                {
                    // Do Nothing

                }
            }
            else
            {
                /* [NORMAL PROSESS] */
                if(!(Err_Cnt_Array[Micon][i] == Err_Off)){
                    Err_Cnt_Array[Micon][i] = Err_Off;
                }
                else
                {
                    // Do Nothing

                }
            }
        }
    }

    if(!(TmporaryFlag == Flag_Off) && Fail_Flag_Array[Micon][i] == Flag_Off)
    {
        Fail_Flag_Array[Micon][i] = Flag_On;
    }
}


/*
*  Create Can Clock Info Data
*  @ param Can Recv ID Table
*  @ param MiconType
*  @ param Index
*  @ return None
*/
void f_CANClock_set(const ID_Table* const ID_Info, uint8_t Type_Aurix, const uint8_t* Can_Recv_Result){

/*=================================================================================================================*/
/* [START OF DATA DECLARATIONS] */
/*=================================================================================================================*/

    static uint8_t v_CanClock_fail_flag = 0;
    int i;
    uint8_t TmporaryFlag = Flag_Off;

    /* [Get API Result] Ptr Array Elements */
    uint8_t Clock_API_Result_TC[TC_ID_NUM]    = {0};
    uint8_t Clock_API_Result_VMC[VMC_ID_NUM]  = {0};

    /* [Get API Result] Ptr Array */
    uint8_t* const Clock_API_Result[2] = { Clock_API_Result_TC, Clock_API_Result_VMC };

    /* [ID Err Counter] PtrArray Elements */
    static uint8_t Clock_Err_Cnt_TC[TC_ID_NUM]    = {0};
    static uint8_t Clock_Err_Cnt_VMC[VMC_ID_NUM]  = {0};

    /* [ID Err Counter] PtrArray */
    uint8_t* const Can_Clock_Err_Cnt[2] = {Clock_Err_Cnt_TC, Clock_Err_Cnt_VMC};

    /* [ID Err Flag] PtrArray Elements */
    static uint8_t Clock_Fail_Flag_TC[TC_ID_NUM]    = {0};
    static uint8_t Clock_Fail_Flag_VMC[VMC_ID_NUM]  = {0};

    /* [ID Err Flag] PtrArray */
    uint8_t* const Can_Clock_Fail_Falg[2] = {Clock_Fail_Flag_TC, Clock_Fail_Flag_VMC};

/*=================================================================================================================*/
/* [START OF PROCEDURE IMPLEMENTATIONS] */
/*=================================================================================================================*/

    for(i=0; i < ID_Info->size; i++){

#ifdef DEBUG_COMMON
            printf("[ENTRY] : Type_Aurix=%d, index=%d, Can_Recv_Result=%d\n", Type_Aurix, i, Can_Recv_Result[i]);
#endif
        if(Can_Recv_Result[i] == Err_On){
            // Do Nothing
#ifdef DEBUG_COMMON
            printf("[FAIL_OUT] : Type_Aurix=%d, index=%d, Can_Recv_Result=%d\n", Type_Aurix, i, Can_Recv_Result[i]);
#endif
        }
        else
        {
            /* <<< Get API >>> */
            Clock_API_Result[Type_Aurix][i] = Stub_CallAPI_CanClock(ID_Info->array[i]);
#ifdef DEBUG_COMMON
        printf("[GET] : Micon=%d, index=%d, Clock_API_Result=%d\n", Type_Aurix, i, Clock_API_Result[Type_Aurix][i]); 
#endif
            /* <<< PROHIBITION >>> */
            if(!(v_CanClock_fail_flag == Flag_Off)){
                
            }
            else
            {
                /* [ FAIL JUDGMENT ] */
                if(!(Clock_API_Result[Type_Aurix][i] == Err_Off)){

                    // Err Count Up
                    Can_Clock_Err_Cnt[Type_Aurix][i]++;
#ifdef DEBUG_ERR
            printf("[ERR_CNT_UP] : Micon=%d, index=%d, ErCnt=%d\n", Type_Aurix, i, Can_Clock_Err_Cnt[Type_Aurix][i]);
#endif
                    if(Can_Clock_Err_Cnt[Type_Aurix][i] >= v_CanClockTh){
                        Can_Clock_Fail_Falg[Type_Aurix][i] = Flag_On;
                        TmporaryFlag = Can_Clock_Fail_Falg[Type_Aurix][i];

                        if(Can_Clock_Fail_Falg[Type_Aurix][i]){
                            /* Create Fail State */
                            g_FailState_set(CAN_CLOCK_DATA, CAN_CLOCK);
                        }
                        else
                        {
                            // Do Nothing
                        }
                    }
                    else
                    {
                        // Do Nothing
                    }
                }
                else
                {
                    if(Can_Clock_Err_Cnt[Type_Aurix][i] == Err_Off){
                        Can_Clock_Err_Cnt[Type_Aurix][i] = Err_Off;
                    }
                    else
                    {
                        // Do Nothing
                    }
                }
            }
        }
    }

    if(!(TmporaryFlag == Flag_Off) && v_CanClock_fail_flag == Flag_Off){
        v_CanClock_fail_flag = Flag_On;
    }

}
