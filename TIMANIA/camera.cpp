//=============================================================================
//
// �J�������� [camera.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "inputx.h"
#include "keyboard.h"
#include "camera.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

#define	VIEW_ASPECT		((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)	// �r���[���ʂ̃A�X�y�N�g��	
#define	VIEW_NEAR_Z		(0.5f)											// �r���[���ʂ�NearZ�l
#define	VIEW_FAR_Z		(400.0f)										// �r���[���ʂ�FarZ�l

#define	VALUE_MOVE_CAMERA	(20.0f)										// �J�����̈ړ���
#define	VALUE_ROTATE_CAMERA	(D3DX_PI * 0.01f)							// �J�����̉�]��

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static CAMERA			g_Camera;		// �J�����f�[�^
//=============================================================================
// ����������
//=============================================================================
void InitCamera(void)
{
	g_Camera.pos = D3DXVECTOR3(POS_X_CAM, POS_Y_CAM, POS_Z_CAM);
	g_Camera.at = D3DXVECTOR3(0.0f, 1.0f, 0.0f);	//�J�����̒����_
	g_Camera.up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);	//�J�����̏�������K���x�N�g��
	g_Camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_Camera.fov = VIEW_ANGLE;	//����p40��

	g_Camera.shake = false;
	g_Camera.shakeValue = 0.0f;
	g_Camera.shakeCounter = 0;

	g_Camera.viewChanger = 20.0f;
	g_Camera.viewAngle = false;
	g_Camera.changeValue = VIEW_CHANGE;
	g_Camera.change = false;

	g_Camera.ViewFar = 1000.0f;

	// ���_�ƒ����_�̋������v�Z
	float vx, vz;
	vx = g_Camera.pos.x - g_Camera.at.x;
	vz = g_Camera.pos.z - g_Camera.at.z;
	g_Camera.len = sqrtf(vx * vx + vz * vz);

}


//=============================================================================
// �J�����̏I������
//=============================================================================
void UninitCamera(void)
{

}


//=============================================================================
// �J�����̍X�V����
//=============================================================================
void UpdateCamera(void)
{
	if (g_Camera.inGame == true) { g_Camera.ViewFar = VIEW_FAR_Z; }
	else { g_Camera.ViewFar = 1000.0f; }

	if (g_Camera.shake == true)
	{
		g_Camera.shakeCounter++;
		if (g_Camera.shakeCounter % 3 == 0) { g_Camera.shakeValue *= -1; }
		g_Camera.at.x += g_Camera.shakeValue;

		if (g_Camera.shakeCounter % 15 == 0) { g_Camera.shake = false; }
	}

	if (g_Camera.viewAngle == true/* && g_Camera.fov < VIEW_ANGLE+20.0f*/)
	{
		/*if (g_Camera.fov <= (VIEW_ANGLE + g_Camera.viewChanger)) { */g_Camera.fov += g_Camera.changeValue*0.5f; g_Camera.changeValue *= 0.8f;
	}
	else if (g_Camera.viewAngle == false && g_Camera.change == true/*&& g_Camera.fov> VIEW_ANGLE*/)
	{
		/*if (g_Camera.fov >= (VIEW_ANGLE - g_Camera.viewChanger)) { */g_Camera.fov -= g_Camera.changeValue*0.5f; g_Camera.changeValue *= 0.8f;
	}

#ifdef DEBUG

	if (Keyboard_IsKeyDown(KK_D1))
	{// ���_�ړ��u��v
		g_Camera.pos.y += VALUE_MOVE_CAMERA;
	}

	if (Keyboard_IsKeyDown(KK_D2))
	{// ���_�ړ��u���v
		g_Camera.pos.y -= VALUE_MOVE_CAMERA;
	}

	if (Keyboard_IsKeyDown(KK_D3))
	{// �����_����u���v
		g_Camera.rot.y -= VALUE_ROTATE_CAMERA;
		if (g_Camera.rot.y < -D3DX_PI)
		{
			g_Camera.rot.y += D3DX_PI * 2.0f;
		}

		g_Camera.at.x = g_Camera.pos.x + sinf(g_Camera.rot.y) * g_Camera.len;
		g_Camera.at.z = g_Camera.pos.z + cosf(g_Camera.rot.y) * g_Camera.len;
	}

	if (Keyboard_IsKeyDown(KK_D4))
	{// �����_����u�E�v
		g_Camera.rot.y += VALUE_ROTATE_CAMERA;
		if (g_Camera.rot.y > D3DX_PI)
		{
			g_Camera.rot.y -= D3DX_PI * 2.0f;
		}

		g_Camera.at.x = g_Camera.pos.x + sinf(g_Camera.rot.y) * g_Camera.len;
		g_Camera.at.z = g_Camera.pos.z + cosf(g_Camera.rot.y) * g_Camera.len;
	}

	if (Keyboard_IsKeyDown(KK_D5))
	{// �����_�ړ��u��v
		g_Camera.at.y += VALUE_MOVE_CAMERA;
	}

	if (Keyboard_IsKeyDown(KK_D6))
	{// �����_�ړ��u���v
		g_Camera.at.y -= VALUE_MOVE_CAMERA;
	}

	if (Keyboard_IsKeyDown(KK_D7))
	{// �߂Â�
		g_Camera.len -= VALUE_MOVE_CAMERA;
		g_Camera.pos.x = g_Camera.at.x - sinf(g_Camera.rot.y) * g_Camera.len;
		g_Camera.pos.z = g_Camera.at.z - cosf(g_Camera.rot.y) * g_Camera.len;
	}

	if (Keyboard_IsKeyDown(KK_D8))
	{// �����
		g_Camera.len += VALUE_MOVE_CAMERA;
		g_Camera.pos.x = g_Camera.at.x - sinf(g_Camera.rot.y) * g_Camera.len;
		g_Camera.pos.z = g_Camera.at.z - cosf(g_Camera.rot.y) * g_Camera.len;
	}

	if (Keyboard_IsKeyDown(KK_N))
	{
		//g_Camera.fov -= 1.0f;
	}
	if (Keyboard_IsKeyDown(KK_M))
	{
		//g_Camera.fov += 1.0f;
	}
	// �J�����������ɖ߂�
	if (Keyboard_IsKeyDown(KK_D0))
	{
		UninitCamera();
		InitCamera();
	}
#endif
}


//=============================================================================
// �J�����̍X�V
//=============================================================================
void SetCamera(void)
{

	// �r���[�}�g���b�N�X�ݒ�
	D3DXMatrixLookAtLH(&g_Camera.mtxView, &g_Camera.pos, &g_Camera.at, &g_Camera.up);
	SetViewMatrix(&g_Camera.mtxView);

	float det;
	D3DXMatrixInverse(&g_Camera.mtxInvView, &det, &g_Camera.mtxView);

	// �v���W�F�N�V�����}�g���b�N�X�ݒ�
	D3DXMatrixPerspectiveFovLH(&g_Camera.mtxProjection, D3DXToRadian(g_Camera.fov), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, VIEW_NEAR_Z, g_Camera.ViewFar);
	SetProjectionMatrix(&g_Camera.mtxProjection);


}


//=============================================================================
// �J�����̎擾
//=============================================================================
CAMERA *GetCamera(void) 
{
	return &g_Camera;
}


// �J�����̎��_�ƒ����_���Z�b�g
void SetCameraAT(D3DXVECTOR3 pos)
{
	// �J�����̒����_���v���C���[�̍��W�ɂ��Ă݂�
	g_Camera.at = pos;

	// �J�����̎��_���J������Y����]�ɑΉ������Ă���	
	g_Camera.pos.x = g_Camera.at.x - sinf(g_Camera.rot.y) * g_Camera.len;
	g_Camera.pos.z = g_Camera.at.z - cosf(g_Camera.rot.y) * g_Camera.len;

}

// �J�����̎��_�ƒ����_���Z�b�g
void SetCameraATDelay(D3DXVECTOR3 pos)
{
	D3DXVECTOR3 AtVec;
	D3DXVECTOR3 PosVec;
	
	//����̃J�����̍��W
	PosVec.x = g_Camera.at.x - sinf(g_Camera.rot.y) * g_Camera.len;
	PosVec.y = g_Camera.pos.y;
	PosVec.z = g_Camera.at.z - cosf(g_Camera.rot.y) * g_Camera.len;
	
	AtVec = pos - g_Camera.at;	//�����_�̕ω��x�N�g��
	PosVec = PosVec - g_Camera.pos;	//����W�̕ω�

	PosVec *= 0.2f;	//�x�N�g���X�P�[�����O
	AtVec *= 0.3f;	//�x�N�g���X�P�[�����O

	// �J�����̒����_���v���C���[�̍��W�ɂ��Ă݂�
	g_Camera.at += AtVec;
	g_Camera.pos += PosVec;
}
