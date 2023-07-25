//=============================================================================
//
// �J�������� [camera.h]
// Author : 
//
//=============================================================================
#pragma once


//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include <d3dx9.h>
#include "renderer.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	POS_X_CAM		(6.0f)			// �J�����̏����ʒu(X���W)
#define	POS_Y_CAM		(5.5f)		// �J�����̏����ʒu(Y���W)
#define	POS_Z_CAM		(-10.0f)		// �J�����̏����ʒu(Z���W)

#define MOVE_ROTATION 6.0f

#define VIEW_CHANGE 10.0f
#define	VIEW_ANGLE	40.0f							// �r���[���ʂ̎���p

class CAMERA
{
public:

	D3DXVECTOR3			pos;			// �J�����̎��_(�ʒu)
	D3DXVECTOR3			at;				// �J�����̒����_
	D3DXVECTOR3			up;				// �J�����̏�����x�N�g��
	D3DXVECTOR3			rot;			// �J�����̉�]

	float				len;			// �J�����̎��_�ƒ����_�̋���
	float				fov;			// ����p

	D3DXMATRIX			mtxView;		// �r���[�}�g���b�N�X
	D3DXMATRIX			mtxInvView;		// �r���[�}�g���b�N�X
	D3DXMATRIX			mtxProjection;	// �v���W�F�N�V�����}�g���b�N�X

	bool shake;
	float shakeValue;
	int shakeCounter;

	float viewChanger;
	bool viewAngle;
	float changeValue;
	bool change;
	bool inGame;

	float ViewFar;

	void CameraShake(float value) 
	{ 
		//at.x += D3DXToRadian(value);
		shake = true;
		shakeValue = D3DXToRadian(value)*2;
		shakeCounter = 0;
	}

	void CameraRotate(float value)
	{
		rot.y = value;
		if (rot.y < -D3DX_PI)
		{
			rot.y += D3DX_PI * 2.0f;
		}

		at.x = pos.x + sinf(rot.y) * len;
		at.z = pos.z + cosf(rot.y) * len;
	}

	void SetZoom(bool value)
	{
		changeValue = VIEW_CHANGE;
		viewAngle = value;
		change = true;
	}
	void SetZoom(bool value, float v)
	{
		changeValue = VIEW_CHANGE * v;
		viewAngle = value;
		change = true;
	}
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void SetCamera(void);
CAMERA *GetCamera(void);
void SetCameraAT(D3DXVECTOR3 pos);
void SetCameraATDelay(D3DXVECTOR3 pos);
