REMON_Readme


千谷，おはよう，南角です．

REMON一式送付します．
圧縮しているので展開して，いつものEMB2022_Workspaceの下に
プロジェクトとして追加してください．

mainはtest.cですので，別途添付しますが，圧縮ファイルの中のものと同じです．
test.cを元に概要に関して説明します．


並行処理は３つでtask0，task1，task6です．

◇ task0は最高優先度のタスクでタイマーa1(ta1int)から1回だけ起動(sta_tsk())されます．
処理内容は
0-1 LEDを真ん中から両端に向かって点灯させる
0-2 ext_tsk()で処理終了
排他制御は実施しません．
タイマーa0とa1のタイマー始動はtask6で実施します．
開始時間はtest.cの前の方にある
/* 初回起動タイミング および 起動周期（単位ms）適時変更する */
#define TA1_ms	1100	/* タイマA1 (1100ms)カウンタ値 */
で指定します．
上記はタイマー始動から1ms毎にタイマーa1割り込みが発生して
1.1秒後にtask0を起動します．


◇ task1は中間優先度のタスクでタイマーa0(ta0int)から1回だけ起動(sta_tsk())されます．
最低優先度のtask6とはLEDを排他制御します．
開始時間はtest.cの前の方にある
/* 初回起動タイミング および 起動周期（単位ms）適時変更する */
#define TA0_ms	1200	/* タイマA0 (1200ms)カウンタ値 */
で指定します．
上記はタイマー始動から1ms毎にタイマーa1割り込みが発生して
1.2秒後にtask1を起動します．
処理は以下の部分に分かれています．
1-1 LED を全点灯
1-2 wai_sem()またはDIによって排他制御開始
1-3 LEDを下位側から上位側に順次8個点灯
1-4 sig_sem()またはEIによって排他制御終了
1-5 LED を全点灯
1-6 ext_tsk()で処理終了

排他制御方法の選択はtest.cの最初の方にある
/* Mutual Exclusion Type */

//#define MUTUAL_EX // DI/EI
#define REMON_SEM	// REMON Semaphore
で選択します．
使用しない方をコメントアウトして指定します．
実際のコードは以下のようになっています．
#ifdef MUTUAL_EX
		_asm( "\tFCLR	I");		/* 割り込み禁止 */
#else
#ifdef REMON_SEM
		wai_sem((unsigned short)0);
#endif
#endif

両方をコメントアウトすれば排他制御を実施しません．
なお，task0，task1，task6は全てのレベルの割り込みを許可した状態で実行されます．


◇ task6は最低優先度のタスクでmainから起動(sta_tsk())され，無限に以下の処理を繰り返します．
中間優先度のtask1とはLEDを排他制御します．
6-1 LED を下位側4つ点灯
6-2 wai_sem()またはDIによって排他制御開始
6-3 LEDを上位側から下位側に順次8個点灯
6-4 sig_sem()またはEIによって排他制御終了
6-5 LED を上位側4つ点灯
6-6 6-1から繰り返す



◇ 以下セマフォを使用した場合(#define REMON_SEM)のシナリオです
・最初にtask6が実行開始
・6-1実行
・task6がセマフォ獲得(6-2)
・6-3実行中にタイマa1からtask0起動
・task0が実行を開始し
・task0実行中にタイマa0によりtask1が起動される（task1はRTEADYになる）が，
  task0の方が優先度が高いためtask0が実行を続ける
・task0がext_tsk()によって終了
・次に優先度が高いtask1が実行を開始して1-1を実行
・task1がwai_sem(1-2)するが，すでにtask6がロックしているためtask6が実行再開
・6-3を終了
・task6がsig_sem()(6-4)によりロック解除
・task1が1-2から抜け，1-3，1-4，1-5，1-6を終了
・task6がsig_sem(6-4)から抜けてきて，6-5実行
・以後はtask6しかREADYではないので，6-1から6-5を無限に繰り返す

◇ #define MUTUAL_EXにすると動作が上と変化します．

◇ 以下の3パターンの波形をよろしく
#define REMON_SEM を有効にする
#define MUTUAL_EX を有効にする
両方とも無効（コメントアウト）する，つまり優先度のみで処理が動作する


◇ 最後になりましたが，おそらくE8aのバグまたは限界だと思うのですが
最初にtask6の先頭部分にブレークポイントをセットしてください
void task6(void) /* Lowest Priority */
{  ← ここ
そうでないとシステムが飛びます
task6で1回だけ停止させた後は，そのまま再開すれば正常に動作します．
以後はブレークポイントをセットする必要はありません．

# システムが飛ぶ原因ですが，昔ののM16C/62CのデバッガはCPUのブレークポイントレジスタによる
# ハードウェアブレークポイント
# M16C/62PのブレークポイントがE8aによってフラッシュの命令をBRK命令に書き換えることによる
# ソフトウェアブレーポイントであることが関係しているのではないかと思っています．


以上，よろしく
