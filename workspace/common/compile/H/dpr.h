//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//　【ヘッダ名】
//　　　ｄｐｒ
//　【ヘッダレベル】
//　　　ＬＥＶＥＬ：Ｈ－１
//  【ヘッダ説明】
//      デュアルポート関連定義（不要？）
//  【備考】
//      なし
//  【更新履歴】
//      2006.07.06  H.Ihara
//
//            Copyright(C)2006 MATSUSHITA Welding Systems Co., Ltd. ALL RIGHT RESERVED
//
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//              （注意）
//              ifdpr.cも修正すること
//  メインからコマンドを受信するときは、ifdprcmdRecive_??
//  ＩＦからコマンドを送信するときは、ifdprcmd*****
//  と定義する
//  CmdData_Tbl[ ]と順番が同じにする
/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      コマンド番号定義    (Ｍａｉｎ～Ｉ／ＦＣＰＵ）                       */
/*--------------------------------------------------------------------------*/
#define     ifdprcmdRecive_1         1      //メインレディ
#define     ifdprcmdIFREADY          2      //ＩＦレディ
#define     ifdprcmdRecive_3         3      //溶接固定パラメータ
#define     ifdprcmdRecive_4         4      //溶接電源動作指令
#define     ifdprcmdRecive_5         5      //溶接制御出力
#define     ifdprcmdRecive_6         6      //溶接条件指令
#define     ifdprcmdRecive_7         7      //半固定パラメータ
#define     ifdprcmdINWLDERR         8      //溶接異常検出
#define     ifdprcmdINWLDPWRERR      9      //溶接電源異常検出
#define     ifdprcmdINWLDSTS        10      //溶接電流検出状態
#define     ifdprcmdINWLDIN         11      //溶接制御入力
#define     ifdprcmdRecive_12       12      //サーボ固定パラメータ
#define     ifdprcmdRecive_13       13      //サーボ電源制御
#define     ifdprcmdRecive_14       14      //サーボ制御指令
#define     ifdprcmdRecive_15       15      //サーボ速度指令
#define     ifdprcmdINSRVERR        16      //サーボ/ＣＰＵエラー
#define     ifdprcmdINITEND         17      //初期化完了
#define     ifdprcmdRecive_18       18      //ダウンロード
#define     ifdprcmdRecive_19       19      //可変パラメータ
#define     ifdprcmdRecive_20       20      //品質モニタ条件    
#define     ifdprcmdRecive_21       21      //品質モニタリセット
#define     ifdprcmdRecive_22       22      //溶接データ記録設定
#define     ifdprcmdRecive_23       23      //記録データ取得要求
#define     ifdprcmdWLDMONANS       24      //品質モニタ応答
#define     ifdprcmdWLDDATSET       25      //記録データセット
#define     ifdprcmdRecive_26       26      //溶接種別
#define     ifdprcmdRecive_27       27      //パルス種別
#define     ifdprcmdRecive_28       28      //加速度
#define     ifdprcmdRecive_29       29      //DELAY 
#define     ifdprcmdRecive_30       30      //可変パラメータ変更
#define     ifdprcmdRecive_31       31      //半固定パラメータ変更
#define     ifdprcmdRecive_32       32      //スローダウン速度変更
#define     ifdprcmdWLDDATSTS       33      //溶接データ記録状態
#define     ifdprcmdRecive_34       34      //溶接データ記録要求
#define     ifdprcmdSHIFT           35      //シフトデータ
#define     ifdprcmdWeldIfErr       36      //溶接IFエラー
#define     ifdprcmdRecive_37       37      //CRATER実行中
#define     ifdprcmdRecive_38       38      //溶接ログ設定
#define     ifdprcmdRecive_39       39      //溶接ログ要求
#define     ifdprcmdRecive_40       40      //溶接ログリセット
#define     ifdprcmdWELDLOGANS      41      //溶接ログ応答
#define     ifdprcmdWELDLOGREQ      42      //溶接ログ要求
#define     ifdprcmdWIREADJ_CHG     43      //ワイヤ送給微調
#define     ifdprcmdWELDADJ_CHG     44      //溶接微調
#define     ifdprcmdWIREADJ         45      //ワイヤ送給微調（一括送信）
#define     ifdprcmdWELDADJ         46      //溶接微調（一括送信）
#define     ifdprcmdRecive_47       47      //溶接設定データ
#define     ifdprcmdWLDSETDATA1     48      //溶接設定データ１
#define     ifdprcmdWLD1GENREQ      49      //一元データ( 要求 )
#define     ifdprcmdWLD1GENDATA     50      //一元データ( 送信 )
#define     ifdprcmdRecive_51       51      //ｵｰﾄｴｸｽﾃﾝｼｮﾝ  ｽｲｯﾁ    @-R040701RTW [ｵｰﾄｴｸｽﾃﾝｼｮﾝ]
#define     ifdprcmdRecive_52       52      //ｵｰﾄｴｸｽﾃﾝｼｮﾝ  ﾊﾟﾗﾒｰﾀ  @-R040701RTW [ｵｰﾄｴｸｽﾃﾝｼｮﾝ]
#define     ifdprcmdWLDSEQ1         53      //溶接シーケンス１( 送信 )
#define     ifdprcmdRecive_54       54      //主電源制御    NY20041017
#define     ifdprcmdRecive_55       55      //溶接条件リセット @-R050103RK1
#define     ifdprcmdRecive_56       56      //溶接種別ＩＤ要求  // @-R050204RK1
#define     ifdprcmdWLDKINDID       57      //溶接種別ＩＤ      // @-R050204RK1
#define     ifdprcmdRecive_58       58      //アークセンサ：スイッチ @-R050309RK1
#define     ifdprcmdRecive_59       59      //アークセンサ：パラメータ１ @-R050309RK1
#define     ifdprcmdRecive_60       60      //アークセンサ：パラメータ２ @-R050309RK1
#define     ifdprcmdARCSNSDATA      61      //アークセンサ：シフトデータ @-R050309RK1
#define     ifdprcmdWLDDATANS       62      //溶接データ記録開始応答 @-R050701RK1
#define     ifdprcmdWLDDATPOST      63      //溶接データ記録通知 @-R050701RK1
#define     ifdprcmdRecive_64       64      //溶接データ取得要求(PC) @-R050701RK1
#define     ifdprcmdRecive_65       65      //溶接データ通信 @-R050701RK1
#define     ifdprcmdRecive_66       66      //溶接データ記録バッファ取得要求 @-R050701RK1 <ALT3>
#define     ifdprcmdWLDDATBUFFANS   67      //溶接データ記録バッファ取得応答 @-R050701RK1 <ALT3>
#define     ifdprcmdRecive_68       68      //溶接データ記録バッファ取得要求 @-R050701RK1 <ALT3>
#define     ifdprcmdWLDKINDNAME     69      //溶接種別名称定義応答 @-R050902RK1
/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      ステータス番号定義    (Ｍａｉｎ～Ｉ／ＦＣＰＵ）                     */
/*--------------------------------------------------------------------------*/
#define     ifdprstsOUTLIFTOUP          1       //リフトアップ
#define     ifdprstsOUTLIFTDOWN         2       //リフトダウン
#define     ifdprstsOUTWLDOUT           3       //溶接出力状態
#define     ifdprstsOUTSRVFEDBACK       4       //サーボフィードバック
#define     ifdprstsOUTSRVOUT           5       //サーボ出力状態
#define     ifdprstsOUTWLDLOG           6       //データ記録ステイタス
//@-R040701RTW
//#define     ifdprstsOUTWLDSNDSTS    7     //データ送信用ステータス
#define     ifdprstsERRFLAG             7       //エラーフラグ
#define     ifdprstsWELDPWR_FIEDBACK    8       //溶接電源フィードバック
#define     ifdprstsWLDRECCNT           9       //溶接記録バッファ使用数
/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      コマンド番号定義    (Ｉ／ＦＣＰＵ～ＤＳＰ）                         */
/*--------------------------------------------------------------------------*/
#define     hpicmdDSPREADY           1      //ＤＳＰレディー
#define     hpicmdIFREADY            2      //ＩＦレディー
#define     hpicmdOUTWLDINIT         3      //溶接固定パラメータ
#define     hpicmdOUTWLDMOV          4      //溶接電源動作指令
#define     hpicmdOUTWLDADJST        5      //半固定パラメータ
#define     hpicmdINWLDERR           6      //溶接異常検出
#define     hpicmdINWLDPWRERR        7      //溶接電源異常検出
#define     hpicmdINWLDSTS           8      //溶接電流検出状態
#define     hpicmdOUTSRVINIT         9      //サーボ固定パラメータ
#define     hpicmdOUTSRVSEQ         10      //サーボシーケンス制御
#define     hpicmdINSRVINITEND      11      //サーボ初期化完了
#define     hpicmdINTSRVERR         12      //サーボエラー
#define     hpicmdINTSRVFEDBACK     13      //サーボフィードバック
#define     hpicmdOUTWLDOUT         14      //溶接制御出力
#define     hpicmdOUTWLDADJST2      15      //半固定パラメータ２
#define     hpicmdOUTWLDSET1        16      //溶接設定データ１
#define     hpicmdINWLDSEQ1         17      //溶接シーケンス１// NY20041013
#define     hpicmdOUTWLDADJST3      18      //半固定パラメータ３ 2007.2.13追加

/*--------------------------------------------------------------------------*/
/*  [概要]                                                                  */
/*      ステータス番号定義    (Ｉ／ＦＣＰＵ～ＤＳＰ）                       */
/*--------------------------------------------------------------------------*/
#define     hpistsOUTWLDCND         1       //溶接条件指令
#define     hpistsINWLDOUT          2       //溶接出力状態
#define     hpistsOUTSRVSPD         3       //サーボ速度指令
#define     hpistsINSRVPLS          4       //サーボパルスカウンタ/モータ電流

#define     hpistsOUTWLDCND_2       5       //溶接条件指令２ 2008.09.03


//  -------------[ Main/IF DPR API ]------------------------
void    ifdprWrite( int CmdNo , pusint pRec );
void    ifdprStsWrite( int StsNo , pusint pRec );
void    ifdprStsRead( int StsNo , pusint pRec );
void    ifdprLiftUpDown( int UpDown , int Parm );
void    ifdprIntr( void );
pusint  ifdprWeldDataPtr( int BuffNo );
void    ifdprWrite_2( int CmdNo , usint Flag , pusint pRec );// @-R040701RTW [一元]
//  -------------[ hpi API ]--------------------------------
void    hpiOpen( void );
int     hpiInit( void );
int     hpiDownLoad( void );
void    hpiBoot( void );
void    hpiWrite( int CmdNo , pusint pRec );
void    hpiStsWrite( int StsNo , pusint pRec );
void    hpiStsRead( int StsNo , pusint pRec );
void    hpiWcondWrite( pusint pRec );
void    hpiIntr( void );
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//  End of dpr.h
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
