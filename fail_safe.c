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

uint8_t g_FailState[FAIL_TYPE_INFO_NUM] = {0};
uint16_t power_On = 60001; // TBD

/*
*  Create Can Recive Info Data
*  @return None
*/
void f_CANRecv_set(void){

/*=================================================================================================================*/
/* [START OF DATA DECLARATIONS] */
/*=================================================================================================================*/

    static uint8_t v_CanRecv_fail_flag = 0;
    uint8_t i = 0;
    uint8_t Type_Aurix = MICON_TYPE_NUM; // TBD
    uint8_t TmporaryFlag = Flag_Off;

    /* [INITIALIZE : ID Table ] Struct Elements(Array) */
    /* TC */
    uint8_t Can_Recv_ID_TC_Array[TC_ID_NUM] = {
        CanID1,
        CanID2,
        CanID3
    };
    /* [INITIALIZE : ID Table ] Struct Elements(Array) */
    /* VMC */
    uint8_t Can_Recv_ID_VMC_Array[VMC_ID_NUM] = { CanID4 };

    /* [INITIALIZE : ID Table ] Struct */
    /* ID Table Struct */
    ID_Table Can_Recv_ID_Array[] ={
        { TC_ID_NUM, Can_Recv_ID_TC_Array },
        { VMC_ID_NUM, Can_Recv_ID_VMC_Array }
    };

    /* [INITIALIZE : Get API Result ] PtrArray Elements */
    /* [TBD : SR_REQUIREMENTS] : API ACK (PtrArray Elements) */
    uint8_t API_Result_TC[TC_ID_NUM]    = {0};
    uint8_t API_Result_VMC[VMC_ID_NUM]  = {0};

    /* [INITIALIZE : Get API Result ] PtrArray */
    /* [TBD : SR_REQUIREMENTS] : API ACK PtrArray */
    uint8_t* const API_Result[2] = { API_Result_TC, API_Result_VMC };

    /* [INITIALIZE : ID Err Counter] PtrArray Elements */
    /* Err Counter (PtrArray Elements) */
    static uint8_t Cnt_TC[TC_ID_NUM]    = {0};
    static uint8_t Cnt_VMC[VMC_ID_NUM]  = {0};

    /* [INITIALIZE : ID Err Counter] PtrArray */
    /* Err Counter PtrArray */
    uint8_t* const Can_Recv_Err_Cnt[2] = {Cnt_TC, Cnt_VMC};

    /* [INITIALIZE : ID Err Flag] PtrArray Elements */
    //* [TBD : SR_REQUIREMENTS] Err Flag (PtrArray Elements) */
    uint8_t Fail_Flag_TC[TC_ID_NUM]    = {0};
    uint8_t Fail_Flag_VMC[VMC_ID_NUM]  = {0};

    /* [INITIALIZE : ID Err Flag] PtrArray */
    /* [TBD : SR_REQUIREMENTS] : Fail Flag PtrArray */
    uint8_t* const Can_Recv_Fail_Falg[2] = {Fail_Flag_TC, Fail_Flag_VMC};

/*=================================================================================================================*/
/* [START OF PROCEDURE IMPLEMENTATIONS] */
/*=================================================================================================================*/

    /* [PROCESS] Get Micon Type */
    /* STUB GetFunction Micon Type */
    Type_Aurix = Stub_CallFunc_GetMiconType() - MiconType_Offset;

    /* Micon Type Overflow Check */
    if(Type_Aurix < 0 || Type_Aurix >= ARRAY_LENGTH(Can_Recv_ID_Array)){

        return;
    }
    else
    {
        // Do Nothing
    }

    for(; i < Can_Recv_ID_Array[Type_Aurix].size; i++){

        /* [ Get API ] */
        API_Result[Type_Aurix][i] = Stub_CallAPI_CanRecv(Can_Recv_ID_Array[Type_Aurix].array[i]);

        /* [ PROHIBITION ] */
        if(!(v_CanRecv_fail_flag == Flag_Off)){

        }
        else if(v_CanRecv_fail_flag == Flag_Off && (power_On < Power_On_thr)){
            if(!(Can_Recv_Err_Cnt[Type_Aurix][i] == Err_Off)){

                //Can_Recv_Err_Cnt[Type_Aurix][i] = Err_Off; // TBD
            }
            else
            {
                // Do Nothing
            }
        }
        else
        {
            /* [ FAIL JUDGMENT ] */
            if(!(API_Result[Type_Aurix][i] == Err_Off)){

                // Err Count Up!
                Can_Recv_Err_Cnt[Type_Aurix][i]++;

                if(Can_Recv_Err_Cnt[Type_Aurix][i] >= v_CanRecvTh){
                    
                    /* [TBD : SR_REQUIREMENTS] : Set Fail Flag */ 
                    Can_Recv_Fail_Falg[Type_Aurix][i] = Flag_On;

                    TmporaryFlag = Can_Recv_Fail_Falg[Type_Aurix][i];

                    /* [TBD : SR_REQUIREMENTS] : Set Fail State Condition */
                    if(Can_Recv_Fail_Falg[Type_Aurix][i]){

                        /* Create Fail State */
                        g_FailState[CAN_REV] = CAN_REV_DATA;
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
                if(!(Can_Recv_Err_Cnt[Type_Aurix][i] == Err_Off)){
                    Can_Recv_Err_Cnt[Type_Aurix][i] = Err_Off;

                }
                else
                {
                    // Do Nothing

                }

            }
        }
    }

    if(!(TmporaryFlag == Flag_Off) && v_CanRecv_fail_flag == Flag_Off){
        v_CanRecv_fail_flag = Flag_On;
    }

    /* Call CANClock Function */
    f_CANClock_set(&Can_Recv_ID_Array[Type_Aurix], Type_Aurix, API_Result[Type_Aurix]);
}

/*
*  Create Can Clock Info Data
*  @ param Can Recv ID Table
*  @ param MiconType
*  @ param Index
*  @ return None
*/
void f_CANClock_set(ID_Table* const ID_Info, uint8_t Type_Aurix, const uint8_t* Can_Recv_Result){

/*=================================================================================================================*/
/* [START OF DATA DECLARATIONS] */
/*=================================================================================================================*/

    static uint8_t v_CanClock_fail_flag = 0;
    int i;
    uint8_t TmporaryFlag = Flag_Off;

    /* [INITIALIZE : Get API Result ] PtrArray Elements */
    /* [TBD : SR_REQUIREMENTS] : Clock API ACK (PtrArray Elements) */
    uint8_t Clock_API_Result_TC[TC_ID_NUM]    = {0};
    uint8_t Clock_API_Result_VMC[VMC_ID_NUM]  = {0};

    /* [INITIALIZE : Get API Result ] PtrArray */
    /* [TBD : SR_REQUIREMENTS] : Clock API ACK PtrArray */
    uint8_t* const Clock_API_Result[2] = { Clock_API_Result_TC, Clock_API_Result_VMC };

    /* [INITIALIZE : ID Err Counter] PtrArray Elements */
    /* Clock Err Counter (PtrArray Elements) */
    static uint8_t Clock_Err_Cnt_TC[TC_ID_NUM]    = {0};
    static uint8_t Clock_Err_Cnt_VMC[VMC_ID_NUM]  = {0};

    /* [INITIALIZE : ID Err Counter] PtrArray */
    /* Clock Err Counter PtrArray */
    uint8_t* const Can_Clock_Err_Cnt[2] = {Clock_Err_Cnt_TC, Clock_Err_Cnt_VMC};

    /* [INITIALIZE : ID Err Flag] PtrArray Elements */
    //* [TBD : SR_REQUIREMENTS] Clock Err Flag (PtrArray Elements) */
    uint8_t Clock_Fail_Flag_TC[TC_ID_NUM]    = {0};
    uint8_t Clock_Fail_Flag_VMC[VMC_ID_NUM]  = {0};

    /* [INITIALIZE : ID Err Flag] PtrArray */
    /* [TBD : SR_REQUIREMENTS] : Clock Fail Flag PtrArray */
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
                            g_FailState[CAN_CLOCK] = CAN_CLOCK_DATA;
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
