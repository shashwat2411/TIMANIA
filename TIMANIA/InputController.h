#pragma once

#ifndef XINPUT_H_

#define	XINPUT_H_

#include	"main.h"

void	InitXinput();	//	Xinput������
void	UninitXinput();	//	Xinput�I������
void	UpdateXinput();	//	Xinput�X�V����

const	D3DXVECTOR2&	GetStickL();	//	���X�e�B�b�N�̓��̓x�N�g���擾
const	D3DXVECTOR2&	GetStickR();	//	�E�X�e�B�b�N�̓��̓x�N�g���擾

//bool	GetControllerPress(const char name[]);
bool	GetControllerPress(const char name[]);
//bool	GetControllerTrigger(const char name[]);
bool	GetControllerTrigger(const char name[]);

void StopControlsBool(int frames);
bool GetControlsBool();
#endif // !XINPUT_H_

