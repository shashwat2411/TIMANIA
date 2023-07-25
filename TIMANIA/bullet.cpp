//=============================================================================
//
// �e���� [bullet.cpp]
// Author : 
//
//=============================================================================
#include "bullet.h"
#include "camera.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static ID3D11Buffer		*g_VertexBuffer = NULL;	// ���_�o�b�t�@

static BULLET		g_Bullet[BULLET_MAX];	// �e�f�[�^



//=============================================================================
// ����������
//=============================================================================


void BULLET::Prepare()
{
	Initialize();

	Offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Size = D3DXVECTOR2(1.0f, 1.0f);

	animate = true;
	animationTimer = 0.0f;
	animationTimerMax = 8.0f;
	oneFrameTime = 0.2f;

	FrameWidth = 8;
	FrameHeight = 1;

	TextureSize.x = 1.0f / FrameWidth;
	TextureSize.y = 1.0f / FrameHeight;

	TextNo = LoadTexture((char*)"data/TEXTURE/explosion000.png");
}
void BULLET::Update()
{
	if (use)
	{
		if (animationOver == true)
		{
			use = false;
		}
	}
}

void InitBullet(void)
{
	// �}�e���A��������

	// ������
	for(int i = 0; i < BULLET_MAX; i++)
	{
		g_Bullet[i].Prepare();
	}
}

//=============================================================================
// �I������
//=============================================================================
void UnInitBullet(void)
{
	for (int i = 0; i < BULLET_MAX; i++)
		g_Bullet[i].UnInitialize();
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBullet(void)
{
	for(int i = 0; i < BULLET_MAX; i++)
	{
		g_Bullet[i].Update();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBullet(void)
{
	for (int i = 0; i < BULLET_MAX; i++)
		g_Bullet[i].Draw();
}


//=============================================================================
// �e�̃p�����[�^���Z�b�g
//=============================================================================
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 direction)
{
	for(int i = 0; i < BULLET_MAX; i++)
	{
		//�܂��\������Ă��Ȃ��ꏊ��T��
		if(g_Bullet[i].use == false)
		{
			D3DXVec3Normalize(&direction, &direction);
			direction *= BULLET_SPEED;
			g_Bullet[i].Position = pos;
			g_Bullet[i].Move = direction;
			g_Bullet[i].count = 0.0f;
			g_Bullet[i].use = true;
			g_Bullet[i].animationOver = false;
			break;
		}
	}
}

BULLET* GetBullet(void)
{
	return &g_Bullet[0];
}
