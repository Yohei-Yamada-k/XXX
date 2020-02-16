#include "fail_safe.h"
#include "StubFunc.h"
#define DEBUG_COMMON

int main()
{   
     printf("Can_Recv_ID_NUM=%d\n",TC_ID_NUM);
    Func_Test();

#ifdef DEBUG_COMMON
    int i;
    for(i=0; i < FAIL_TYPE_INFO_NUM; i++){
        printf("[FAIL STATE] : g_FailState[0x%x]\n", g_FailState[i]);
    }
#endif
    return 0;
}