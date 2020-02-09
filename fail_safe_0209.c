#include "fail_safe.h"
char g_FailState[FAIL_TYPE_INFO_NUM] = {0};

/*******************************
* 静的変数 FailFlag[]を外に出した*
* [0]で仮実装                  *
* FailFlag[]のTmpFlaを追加     *
* ・ループの関数化             *
* ・データ生成に必要な情報     *
*   - 故障種別                 *
*******************************/

/*
* 故障診断情報(Cam未送信)を生成する
* @param Micon_Info マイコンタイプ
* @return 無し
*/
void f_CanSend_set(MICON_INFO Micon_Info){
    // マイコン毎の故障情報フラグの静的変数
    static char v_CanSendFail[MICON_INFO_NUM] = {0};
    
    // マイコン毎の処理関数を配列に格納
    void (*Pfunc[1])(MICON_INFO Micon_Info, char* const FailFlag) = {
        //Cmd_CanSend_set_SYS1,
        //Cmd_CanSend_set_TC,
        //Cmd_CanSend_set_VMC,
        Cmd_CanSend_set_SYS2
    };

    // 当該のマイコン処理関数をコール
    Pfunc[0](Micon_Info, v_CanSendFail);
}

/*
void Cmd_CanSend_set_SYS1(MICON_INFO Micon_Info, char* const FailFlag){
    int v_NodeTable[] = {
        NODE1,
    };
    char v_CanSendErr[ARRAY_LENGTH(v_NodeTable)];
    static int v_CanSendErrCnt_SYS1[ARRAY_LENGTH(v_NodeTable)] ={0};
    
    Cmd_CanSend_set_Internal(
        ARRAY_LENGTH(v_NodeTable),
        v_CanSendErr,
        v_CanSendErrCnt_SYS1,
        Micon_Info, FailFlag
   );
}
*/

/*
* Can未送信(SYS2)を生成する
* @param Micon_Info マイコンタイプ
* @param FailFlag 故障フラグ
* @return 無し
*/
void Cmd_CanSend_set_SYS2(MICON_INFO Micon_Info, char* const FailFlag){
    const int v_NodeCHTable[] = {
        NODE2,
        NODE3
    };
    int v_APIResult[ARRAY_LENGTH(v_NodeCHTable)] = {0};
    
    static int v_CanSendErrCnt[ARRAY_LENGTH(v_NodeCHTable)] = {0};
    Cmd_CanSend_set_Internal(
        v_NodeCHTable,
        v_APIResult,
        v_CanSendErrCnt,
        Micon_Info,
        FailFlag
    );
}

/*
void Cmd_TC(){
    int v_num = 1;
    printf("Cmd_TC=%d",v_num);
}

void Cmd_VMS(){
    int v_num = 1;
    printf("Cmd_VMS=%d",v_num);
}
*/

char f_GetCanSend_API(int CanID){
    printf("[GET_API] : CanID=%d\n", CanID);
    if(!(CanID == 0)){
        return 1;
    }
    else
    {
        return 0;
    }
}

void Cmd_CanSend_set_Internal(
    const int* v_NodeCHTable,
    int* const v_APIResult,
    int* const v_ErrCnt,
    const MICON_INFO v_MiconInfo,
    char* const FailFlag
){
    int i;
    char TmporaryFlag = 0;

    printf("[INTERNAL] index=%d: \n",ARRAY_LENGTH(v_NodeCHTable));
    
    for(i=0; i < ARRAY_LENGTH(v_NodeCHTable); i++){
        /* <入力部> */
        printf("[ENTRY]:index=%d, ErrCnt=%d, Micon=%d, Flag=%d\n",i, v_ErrCnt[i], v_MiconInfo, FailFlag[v_MiconInfo]);
        v_APIResult[i] = f_GetCanSend_API(v_NodeCHTable[i]);

        /* <禁止判定部> */
        if(!(FailFlag[v_MiconInfo] == 0)){
            /* 異常 */
            // Do Nathing
            printf("[OUT FAIL]\n");
        }
        else
        {
            /* <故障診断判定部> */
            // APIから取得した結果が異常を検出
            if(!(v_APIResult[i] == 0)){
                // エラーカウントアップ
                v_ErrCnt[i]++;
                // 故障情報判定
                if(v_ErrCnt[i] > v_CanSendTh){
                    TmporaryFlag = 1;
                    printf("[Fail]:index=%d, ErrCnt=%d, Micon=%d, Flag=%d \n",i, v_ErrCnt[i], v_MiconInfo, FailFlag[v_MiconInfo]);
                }
                else
                {
                    // Do Nathing
                    printf("[Fail_COU_TUP]\n");
                }
            }
            // APIから取得した結果が正常
            else
            {
                
                // エラーカウントをクリア
                if(!(v_ErrCnt[i] == 0)){
                    v_ErrCnt[i] = 0;
                }
                else
                {
                    // Do Nathing
                }
            }
        }
    }
    if(!(TmporaryFlag == 0)){
        FailFlag[v_MiconInfo] = 1;
        printf("[TMPORARY_FLAG_SET]=%d\n", FailFlag[v_MiconInfo]);
    }
}   