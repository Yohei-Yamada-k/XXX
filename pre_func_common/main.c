#include "fail_safe.h"
#include "StubFunc.h"
#define DEBUG_COMMON

int main()
{   
    Func_Test();
    uint8_t temp[FAIL_TYPE_INFO_NUM] = {0};
    for(int i=0; i< FAIL_TYPE_INFO_NUM; i++)
    {
        temp[i] = !(g_FailState_get(i)==0) ? 1 : 0;
        printf("temp = %d\n",temp[i]);
    }
    return 0;
}