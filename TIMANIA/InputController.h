#pragma once

#ifndef XINPUT_H_

#define	XINPUT_H_

#include	"main.h"

void	InitXinput();	//	Xinput初期化
void	UninitXinput();	//	Xinput終了処理
void	UpdateXinput();	//	Xinput更新処理

const	D3DXVECTOR2&	GetStickL();	//	左スティックの入力ベクトル取得
const	D3DXVECTOR2&	GetStickR();	//	右スティックの入力ベクトル取得

//bool	GetControllerPress(const char name[]);
bool	GetControllerPress(const char name[]);
//bool	GetControllerTrigger(const char name[]);
bool	GetControllerTrigger(const char name[]);

void StopControlsBool(int frames);
bool GetControlsBool();
#endif // !XINPUT_H_

