#ifndef TYPE_DEFINED
    #define TYPE_DEFINED
#include    "xTypes.H"

/*
    --------------------------------
    ----    その他の型          ----
    --------------------------------
*/
/*
    文字列型
*/
typedef PCHAR           PSTR;
typedef PCONST_CHAR     PCSTR;
/*
    真偽値
*/
typedef enum Boolean
{
    FALSE,
    TRUE
}BOOL;
/*
    ヌルポインタ
*/
#ifndef NULL
    #define  NULL  ( (PVOID)0 )
#endif
/*
    High Value of Pointer
*/
#ifndef FP_MARK
    #define FP_MARK ( (PVOID)(-1L) )
#endif

/*
    サイズ型
*/
typedef ULONG       SIZE;
typedef SIZE _FAR  *PSIZE;
/*
    ＯＮ／ＯＦＦスイッチ型
*/
typedef enum
{
    SW_UNTUCH   = -1,
    SW_OFF      = 0,
    SW_ON       ,
    SW_SET      
}SWITCHOVER;
/*
    ============================================================================
    ====                Ｉ／Ｏ関連の型定義                                  ====
    ============================================================================
*/
/*
    Ｉ／Ｏポートのタイプ型
*/
typedef enum
{
    IO_TYPE_NOUSE   = -1,               /*  未使用Ｉ／Ｏ            */
    IO_TYPE_PORT    =  0,               /*  Ｉ／Ｏポート形式        */
    IO_TYPE_MEMMAP  =  1                /*  メモリマップドＩ／Ｏ    */
}IO_ACCESS_TYPE;
typedef IO_ACCESS_TYPE  _FAR    *PIO_ACCESS_TYPE;
/*
    Ｉ／Ｏポートのアクセスサイズ型
*/
typedef enum
{
    IO_ACCESS_NONE  =0      ,
    IO_ACCESS_BYTE  =1      ,
    IO_ACCESS_WORD  =2      ,
    IO_ACCESS_DWORD =4
}IO_ACCESS_RANGE;
typedef IO_ACCESS_RANGE _FAR    *PIO_ACCESS_RANGE;
#endif  /*-- end of typedef.h ----------------------------------*/
