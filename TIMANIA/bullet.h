//=============================================================================
//
// �e���� [bullet.h]
// Author : 
//
//=============================================================================
#pragma once

#include "UI.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define BULLET_MAX		(300)		// �o���b�g��Max��
#define BULLET_SPEED	(5.0f)		// �o���b�g�̈ړ��X�s�[�h



// �o���b�g�\����
class BULLET:public UI
{
public:
	int count = 0;
	void Prepare() override;
	void Update() override;

};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitBullet(void);
void UnInitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);

BULLET *GetBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 direction);

