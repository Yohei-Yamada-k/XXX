#include "fail_safe.h"

int main()
{   
    
    test_func();
    printf("[FAIL_FAIL] : failset=%d\n", g_FailState[CAN_SEND]);
    return 0;
}