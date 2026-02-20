# BZ5_RX66T

＜ ＢＺ５用制御プログラム　ＲＸ６６Ｔ ＞

## e2staudio向けＢＺ５開発プロジェクト

設定デバイス      ：`RX66T(R5F566TKCxFB)` -> `RX66T(R5F566TKGxFB)`</br>
開発フォルダ      ：`workspace\BZ5`</br>
使用e2studio     ：`2025-10`</br>
試用ツールチェーン ：`GCC for Renesas RZ 14.2.0.202511`</br>

## スマート・コンフィグレーターで組み込んだコンポーネント

CPUクロック設定</br>
入出力ポート設定</br>
　※使用していないポートは未設定</br>
通信関係</br>
　SCI1</br>
　SCI5</br>
　SCI8</br>
　SCI9</br>
　I2C(RIIC0)</br>
A/Dコンバーター</br>
　AD0xx系</br>
　AD1xx系</br>
D/Aコンバーター</br>
　DA0：ベース指令</br>
　DA1：ピーク指令</br>
タイマ関連</br>
　ベース/ピーク切り替え用ＰＷＭ出力タイマー</br>
　　※カウンタクロックの逓倍設定を最大(/1024)にして「1.8Hz～25kHz」範囲が使用可能</br>
　フリーランタイマー(100μ秒)</br>

### Ｒ２Ｒ回路向けの電流指令値の出力処理を作成した

    「workspace\BZ5\src\common\compile\P7_Output_prog\class\member\L3_R2R_output_member.C」

### ＤＣ ＴＩＧ アナログＲ２Ｒデータテーブルを組み込んだ

    「workspace\BZ5\src\common\compile\H\analog.h」
    　※元データ：ANALOG12.H By BZ3(Ver2.11@2017.03.06)
</br>
