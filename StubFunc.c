#include "fail_safe.h"
#include "StubFunc.h"

#define DEBUG_COMMON
#define DEBUG_PROHIBITION
#define DEBUG_ERR
#define DEBUG_ERRTH
#define DEBUG_ERRTH_LESS
#define DEBUG_FIRST_FAIL
#define DEBUG_NORMAL
#define DEBUG_NORMAL_CNT_LESS

uint8_t g_Call_CanSend      = 0;
uint8_t g_Call_CanRecv      = 0;
uint8_t g_Call_CanClock     = 0;
uint8_t g_Call_GetMiconType = 0;

uint8_t Stub_CallAPI_CanSend(uint32_t CanID){
    return g_Call_CanSend ? API_Err : API_Normal;
}

uint8_t Stub_CallAPI_CanRecv(uint8_t CanID){

    switch(g_Call_GetMiconType){
    case 5:
        return (CanID == CanID1) ? API_Err : API_Normal;
    case 6:
        return (CanID == CanID4) ? API_Normal : API_Normal;
    defalt:
        return API_Normal;
        break;
    }
}

uint8_t Stub_CallAPI_CanClock(uint8_t CanID){
    return g_Call_CanClock ? 1 : 0;
}

uint8_t Stub_CallFunc_GetMiconType(){

    MiconType Result_Array[MICON_TYPE_NUM] = {
        AA, BB, CC, SYS1, SYS2, TC, VMS, RC, RP, DM1, DM2, DM3, DM4, PP1, PP2, XX, YY
    };
    
    
    return Result_Array[g_Call_GetMiconType];
}


void Func_Test(){
    int i;

    g_Call_GetMiconType = 5;
    g_Call_CanClock = 1;
    for(i=0; i<5; i++){
        f_CANRecv_set();
    }

}
