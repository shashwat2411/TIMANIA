
#pragma once

#include <windows.h>
#include "xaudio2.h"  //XAudioを利用したときにインクルード


bool InitSound(HWND hWnd);  //サウンドの初期化
void UninitSound(void);  //サウンドの終了処理

int LoadSound(char* pFilename); //データのロード
void PlaySoundInGame(int index, int loopCount); //データの再生、フラグ0で一回、-1でループ再生
void StopSound(int index);  //データの生成停止


void StopSoundAll(void);  //全ての再生を停止
void SetVolume(int index, float vol);  //ボリュームの変更


//サウンド追加
//１　コントローラと同じタイミングで初期化＆終了処理を行う
//２　タイトルなどのシーンの初期化でデータロード＆再生開始（BGM）
//　終了処理で再生停止（BGM）
//３　弾・爆発なども初期化でロードしておく。
//　　再生はそれぞれのタイミングで行う、ループごとに毎回再生されないように注意が必要。
//　　同様にロードも初期化の一回のみになるよう注意