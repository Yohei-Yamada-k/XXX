#include "fail_safe.h"

int main()
{   

    int number = 6;
    
    static uint8_t CanIDTC[4] = {0};
    static uint8_t CanClockTC[4]  = {0};
    static uint8_t CanIDVMC[2] = {0};
    static uint8_t CanClockVMC[2]  = {0};
    
    struct {
        uint8_t *CanID;
        uint8_t *CanClock;
    }CanMsg[] = {
        CanIDTC,
        CanClockTC
    };
    
    CanMsg[0].CanID[0] =4;
    
    
    
    void _test(int* temp){
        printf("[_test] = %d\n",*temp);
        static int test_CLOCK[*temp];
    
    };

    _test(&number);

    // CAN未受信情報を設定
    void CANRevcInfo_set(Micon_Info){
        
        // CAN未送信を設定
        f_CANRevc_set(Micon_Info);
    }
    
    // CAN未送信を設定
    void f_CANRevc_set(Micon_Info){
        static CANRevcFailFlag;
        static CANRevcErrCnt[];
        static CANClockErrCnt[];
        
        for(){
            // CAN未の処理
            //       :
            
            // CANClockを設定
            f_CANClock_set(Micon_Info);
        }
    }
    
    void f_CANClock_set(Micon_Info, uint8* CANClockErrCnt){
        static CANRevcFailFlag;
    }

    return 0;
}