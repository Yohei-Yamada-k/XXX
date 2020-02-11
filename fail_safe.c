#include "fail_safe.h"

#define DEBUG_COMMON
#define DEBUG_PROHIBITION
#define DEBUG_ERR
#define DEBUG_ERRTH
#define DEBUG_ERRTH_LESS
#define DEBUG_FIRST_FAIL
#define DEBUG_NORMAL
#define DEBUG_NORMAL_CNT_LESS

uint8_t g_FailState[FAIL_TYPE_INFO_NUM] = {0};
uint8_t g_TEST_FI = {0};

void f_CanSend_set(MICON_INFO Micon_Info){
    static uint8_t v_fail_flag = 0;
    uint16_t power_On = 60001; 
    uint16_t power_On_th = 6000;
    uint8_t i;
    uint8_t TmporaryFlag = 0;

    /* Can Node CH Table (TC) */
    uint32_t Can_Node_TC[] = {
        /* TBD */
        NODE1,
        NODE2
    };
    /* Can Node CH Table (VMC) */
    uint32_t Can_Node_VMC[] = {
        /* TBD */
        NODE3,
        NODE4,
        NODE5
    };
    
    /* Table Struct */
    const struct {
        uint8_t size;
        uint32_t* array;
    }Node_CH[] ={
        { ARRAY_LENGTH(Can_Node_TC), Can_Node_TC },
        { ARRAY_LENGTH(Can_Node_VMC), Can_Node_VMC }
    };

    /* Fail Counter */
    static uint8_t Cnt_TC[ARRAY_LENGTH(Can_Node_TC)]    = {0};
    static uint8_t Cnt_VMC[ARRAY_LENGTH(Can_Node_VMC)]  = {0};

    /* API ACK */ 
    //uint8_t API_Result_TC[ARRAY_LENGTH(Can_Node_TC)]    = {0};
    //uint8_t API_Result_VMC[ARRAY_LENGTH(Can_Node_VMC)]  = {0};

    /* Fail Counter Array */
    uint8_t* const Can_Send_Cnt[] = {Cnt_TC, Cnt_VMC};
    /* API ACK Array */
    uint8_t API_Result = 0;

    for(i=0; i < Node_CH[Micon_Info].size; i++){

#ifdef DEBUG_COMMON
        printf("[COMMON_ENTRY] : Micon=%d, index=%d, Table=%d, cnt=%d\n", Micon_Info, i, Node_CH[Micon_Info].array[i], Can_Send_Cnt[Micon_Info][i]);
#endif

        /* <入力部> */
        API_Result = stub_f_GetCanSend(Node_CH[Micon_Info].array[i]);

#ifdef DEBUG_COMMON
        printf("[COMMON_GET] : Micon=%d, index=%d, API_Result=%d\n", Micon_Info, i, API_Result); 
#endif

        /* <禁止判定部> */
        if(!(v_fail_flag == 0) || (power_On < power_On_th)){
            // Do Nothing
#ifdef DEBUG_PROHIBITION
            printf("[PROHIBITION_FAIL] : Micon=%d, index=%d, v_fail_flag=%d\n", Micon_Info, i, v_fail_flag);
#endif
        }
        else
        {
            /* <故障診断判定部> */
            if(!(API_Result == 0)){
                // Err Count Up!
                Can_Send_Cnt[Micon_Info][i]++;
#ifdef DEBUG_ERR
            printf("[ERR_CNT_UP] : Micon=%d, index=%d, cnt=%d\n", Micon_Info, i, Can_Send_Cnt[Micon_Info][i]);
#endif
                if(Can_Send_Cnt[Micon_Info][i] > v_CanSendTh){
                    TmporaryFlag = 1;
                    /* <故障診断情報生成> */
                    g_FailState[CAN_SEND] |= CAN_SEND_DATA;
#ifdef DEBUG_ERRTH
            printf("[ERRTH_OVER] : Micon=%d, index=%d, Flag=%d\n", Micon_Info, i, TmporaryFlag);
#endif
                }
                else
                {
                    // Do Nothing
#ifdef DEBUG_ERRTH_LESS
            printf("[ERRTH_LESS] : Micon=%d, index=%d, cnt=%d, Flag=%d\n", Micon_Info, i, Can_Send_Cnt[Micon_Info][i], TmporaryFlag);
#endif
                }
            }
            else
            {
                if(!(Can_Send_Cnt[Micon_Info][i] == 0)){
                    Can_Send_Cnt[Micon_Info][i] = 0;
#ifdef DEBUG_NORMAL_CNT_LESS
            printf("[NORMAL_CNT_LESS] : Micon=%d, index=%d, cnt=%d \n", Micon_Info, i, Can_Send_Cnt[Micon_Info][i]);
#endif
                }
                else
                {
                    // Do Nothing
#ifdef DEBUG_NORMAL
            printf("[NORMAL] : Micon=%d, index=%d, cnt=%d \n", Micon_Info, i, Can_Send_Cnt[Micon_Info][i]);
#endif
                }
            }
        }
    }

    if(!(TmporaryFlag == 0) && !(v_fail_flag == 1)){
        v_fail_flag = 1;
#ifdef DEBUG_FIRST_FAIL
            printf("[FIAL_FLAG=1] : Micon=%d, index=%d, TmporaryFlag=%d, Flag=%d\n", Micon_Info, i, TmporaryFlag, v_fail_flag);
#endif
    }

}

uint8_t stub_f_GetCanSend(uint32_t CanID){
    uint8_t result = 0;
    
    switch(g_TEST_FI){
    case 0:
        result = 0;
        break;
    case 1:
        result = 1;
        break;
    defalt:
        break;
    }
    return result;
        
}

void test_func(){
    
    uint8_t i;
    for(i = 0;i < 3; i++){
        f_CanSend_set(SYS1);
    }
    
    g_TEST_FI = 1;
    for(i = 0;i < 3; i++){
        f_CanSend_set(SYS1);
    }
    
    g_TEST_FI = 0;
    for(i = 0;i < 2; i++){
        f_CanSend_set(SYS2);
    }

    g_TEST_FI = 1;
    for(i = 0;i < 12; i++){
        f_CanSend_set(SYS1);
    }
}
