#include "shadow.h"
#include "Texture.h"
#include "renderer.h"

//=========================================
//�}�N����`
//=========================================
#define SHADOW_SIZE_X	1.0f
#define SHADOW_SIZE_Z	1.0f
#define SHADOW_MAX		1

//=========================================
//�O���[�o���ϐ�
//=========================================
static		ID3D11Buffer	*g_VertexBufferShadow = NULL;

//static SHADOW g_Shadow[SHADOW_MAX];
static int g_TexNoShadow;	// �e�N�X�`���ԍ�

//�����o�[�֐�
void SHADOW::Init()
{
	// ���_�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBufferShadow);

	//���_�o�b�t�@�̏�����
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(g_VertexBufferShadow, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);	//�o�b�t�@�ւ̏������݋������炤
	VERTEX_3D *vertex = (VERTEX_3D*)msr.pData;	//�������ݐ�̃|�C���^���擾

	//���_���W
	vertex[0].Position = D3DXVECTOR3(-SHADOW_SIZE_X / 2.0f, 0.0f, SHADOW_SIZE_Z / 2.0f);
	vertex[1].Position = D3DXVECTOR3(SHADOW_SIZE_X / 2.0f, 0.0f, SHADOW_SIZE_Z / 2.0f);
	vertex[2].Position = D3DXVECTOR3(-SHADOW_SIZE_X / 2.0f, 0.0f, -SHADOW_SIZE_Z / 2.0f);
	vertex[3].Position = D3DXVECTOR3(SHADOW_SIZE_X / 2.0f, 0.0f, -SHADOW_SIZE_Z / 2.0f);
	//���_�@��
	vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//���_�F
	vertex[0].Diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.8f);
	vertex[1].Diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.8f);
	vertex[2].Diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.8f);
	vertex[3].Diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.8f);
	//���_�̃e�N�X�`�����W
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);
	vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);
	vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);

	//	���_�o�b�t�@�ւ̏������ݏI��
	GetDeviceContext()->Unmap(g_VertexBufferShadow, 0);

	g_TexNoShadow = LoadTexture((char*)"data/TEXTURE/shadow000.jpg");

	ZeroMemory(&Material, sizeof(Material));
	Material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Scaling = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	use = true;
}

void SHADOW::UnInit()
{
	if (g_VertexBufferShadow)
	{
		g_VertexBufferShadow->Release();
		g_VertexBufferShadow = NULL;
	}
}

void SHADOW::Update()
{
	if (use)
	{

	}
}

void SHADOW::Draw()
{
	if (use)
	{
		SetAlphaTestEnable(true);
		SetLightEnable(false);
		SetDepthEnable(false);	//���s����

		// ���_�o�b�t�@�ݒ�
		UINT stride = sizeof(VERTEX_3D);
		UINT offset = 0;
		GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBufferShadow, &stride, &offset);

		// �v���~�e�B�u�g�|���W�ݒ�
		GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
		//���_�o�b�t�@�̏�����
		D3D11_MAPPED_SUBRESOURCE msr;
		GetDeviceContext()->Map(g_VertexBufferShadow, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);	//�o�b�t�@�ւ̏������݋������炤
		VERTEX_3D *vertex = (VERTEX_3D*)msr.pData;	//�������ݐ�̃|�C���^���擾

		//���_���W
		vertex[0].Position = D3DXVECTOR3(-SHADOW_SIZE_X / 2.0f, 0.0f, SHADOW_SIZE_Z / 2.0f);
		vertex[1].Position = D3DXVECTOR3(SHADOW_SIZE_X / 2.0f, 0.0f, SHADOW_SIZE_Z / 2.0f);
		vertex[2].Position = D3DXVECTOR3(-SHADOW_SIZE_X / 2.0f, 0.0f, -SHADOW_SIZE_Z / 2.0f);
		vertex[3].Position = D3DXVECTOR3(SHADOW_SIZE_X / 2.0f, 0.0f, -SHADOW_SIZE_Z / 2.0f);
		//���_�@��
		vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		//���_�F
		vertex[0].Diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.8f);
		vertex[1].Diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.8f);
		vertex[2].Diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.8f);
		vertex[3].Diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.8f);
		//���_�̃e�N�X�`�����W
		vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);
		vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);
		vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);
		vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);

		//	���_�o�b�t�@�ւ̏������ݏI��
		GetDeviceContext()->Unmap(g_VertexBufferShadow, 0);


		SetBlendState(BLEND_MODE_ADD);



		////���_�o�b�t�@�Z�b�g
		//UINT stride = sizeof(VERTEX_3D);
		//UINT offset = 0;
		//GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);
		////Primitive Topolgy Setting
		//GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

		////�e�N�X�`���̃Z�b�g
		//GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_TexNoShadow));

		//�e�̕`��
		D3DXMatrixIdentity(&mtxWorld);	//���[���h�s��̏�����

		D3DXMatrixScaling(&ScalingMatrix, Scaling.x, Scaling.y, Scaling.z);
		D3DXMatrixRotationYawPitchRoll(&RotationMatrix, Rotation.y, Rotation.x, Rotation.z);
		D3DXMatrixTranslation(&TranslationMatrix, Position.x, Position.y, Position.z);

		D3DXMatrixMultiply(&mtxWorld, &ScalingMatrix, &RotationMatrix);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &TranslationMatrix);

		SetWorldMatrix(&mtxWorld);

		//SetMaterial(Material);
		//�e�N�X�`���̃Z�b�g
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_TexNoShadow));

		GetDeviceContext()->Draw(4, 0);

		SetDepthEnable(true);
		SetAlphaTestEnable(false);
		SetBlendState(BLEND_MODE_ALPHABLEND);
	}
}



////�O���[�o���֐�
//HRESULT InitShadow()
//{
//	for (int i = 0; i < SHADOW_MAX; i++)
//	{
//		g_Shadow[i].Init();
//	}
//	return S_OK;
//}
//
//void UnInitShadow()
//{
//	for (int i = 0; i < SHADOW_MAX; i++)
//	{
//		g_Shadow[i].UnInit();
//	}
//}
//
//void UpdateShadow()
//{
//	for (int i = 0; i < SHADOW_MAX; i++)
//	{
//		g_Shadow[i].Update();
//	}
//}
//
//void DrawShadow()
//{
//	for (int i = 0; i < SHADOW_MAX; i++)
//	{
//		g_Shadow[i].Draw();
//	}
//}
//
//int SetShadow(D3DXVECTOR3 pos, float size)
//{
//	int index = -1;
//
//	for (int i = 0; i < SHADOW_MAX; i++)
//	{
//		if (g_Shadow[i].GetUse() == false)
//		{
//			g_Shadow[i].SetPosition(pos);
//			g_Shadow[i].SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
//			g_Shadow[i].SetScaling(size);
//			g_Shadow[i].SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
//			g_Shadow[i].SetUse(true);
//
//			index = i;
//			break;
//		}
//	}
//
//	return index;	//�쐬�����e�̃C���f�b�N�X��Ԃ��A-1�͍쐬���s
//}
//
//void ReleaseShadow(int index)
//{
//	if (index >= 0 && index < SHADOW_MAX)
//	{
//		g_Shadow[index].SetUse(false);
//	}
//}
//
//void SetPositionShadow(int index, D3DXVECTOR3 pos)
//{
//	if (index >= 0 && index < SHADOW_MAX)
//	{
//		g_Shadow[index].SetPosition(pos);
//	}
//}