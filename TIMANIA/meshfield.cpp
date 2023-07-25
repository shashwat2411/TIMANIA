//=============================================================================
//
// ���b�V���n�ʂ̏��� [meshfield.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
//#include "input.h"
#include "texture.h"
#include "meshfield.h"
#include "renderer.h"
#include "player.h"
#include "inputx.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static ID3D11Buffer					*g_VertexBuffer = NULL;	// ���_�o�b�t�@
static ID3D11Buffer					*g_IndexBuffer = NULL;	// �C���f�b�N�X�o�b�t�@

static FIELD	g_Field;	// �t�B�[���h���
static int		g_TexNo;	// �e�N�X�`���ԍ�

static int		g_VertexNum = 0;//���_��
static int		g_IndexNum = 0;	//�C���f�b�N�X��

//=============================================================================
// ����������
//=============================================================================
HRESULT InitMeshField(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int numBlockX, int numBlockZ, float sizeX, float sizeZ)
{
	// �ʒu�E��]�E�X�P�[���̏����ݒ�
	g_Field.pos = pos;
	g_Field.rot = rot;
	g_Field.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	// �e�N�X�`������
	g_TexNo = LoadTexture((char*)"data/TEXTURE/Square1.png");


	int yoko = numBlockX;
	int tate = numBlockZ;

	//�K�v�Ȓ��_���ƃC���f�b�N�X�����v�Z����
	g_VertexNum = (numBlockX + 1) * (numBlockZ + 1);
	g_IndexNum = (((yoko * 2 + 2) * (tate)) + ((tate - 1) * 2));

	// ���_�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * g_VertexNum;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBuffer);


	// �C���f�b�N�X�o�b�t�@����
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(unsigned short) * g_IndexNum;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	GetDevice()->CreateBuffer(&bd, NULL, &g_IndexBuffer);


	{//���_�o�b�t�@�̒��g�𖄂߂�@�@���꒼���ɒ��_������Ă���

		// ���_�o�b�t�@�ւ̃|�C���^���擾
		D3D11_MAPPED_SUBRESOURCE msr;
		GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

		VERTEX_3D* pVtx = (VERTEX_3D*)msr.pData;

		//�c�̃��[�v
		for (int y = 0; y < (tate + 1); y++)
		{
			//���̃��[�v
			for (int x = 0; x < (yoko + 1); x++)
			{
				//�z��̃C���f�b�N�X���v�Z����
				int i = y * (yoko + 1) + x;

				// ���_���W�̐ݒ�
				pVtx[i].Position = D3DXVECTOR3(x * sizeX, 0.0f, y * sizeZ);

				// UV�l�̐ݒ�
				pVtx[i].TexCoord = D3DXVECTOR2(x * 1.0f, y * 1.0f);
				// �@���̐ݒ�
				pVtx[i].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
				// ���_�J���[�̐ݒ�
				pVtx[i].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			}
		}
		GetDeviceContext()->Unmap(g_VertexBuffer, 0);
	}

	{//�C���f�b�N�X�o�b�t�@�̒��g�𖄂߂�  �}�I�ɉ��㉺��̏��Œ��_���l����

		// �C���f�b�N�X�o�b�t�@�̃|�C���^���擾
		D3D11_MAPPED_SUBRESOURCE msr;
		GetDeviceContext()->Map(g_IndexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
		unsigned short *pIdx = (unsigned short*)msr.pData;

		int idx = 0;

		for (int y = 0; y < tate; y++)
		{
			for (int x = 0; x < (yoko + 1); x++)
			{
				pIdx[idx] = y *(yoko + 1) + x;//��
				idx++;
				pIdx[idx] = (y+1)*(yoko + 1) + x;//��	
				idx++;
			}

			//�k�ރ|���S�����̃C���f�b�N�X�@�|���S���������@�I���Ƃ͂��߂�1���d��������
			if (y < (tate - 1))
			{
				pIdx[idx] = (y + 2) * (yoko + 1);
				idx++;
				pIdx[idx] = y * (yoko + 1) + yoko;
				idx++;
			}
		}

 		GetDeviceContext()->Unmap(g_IndexBuffer, 0);
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitMeshField(void)
{
	//�C���f�b�N�X�o�b�t�@�̉��
	if (g_IndexBuffer)
		g_IndexBuffer->Release();

	//���_�o�b�t�@�̉��
	if (g_VertexBuffer)
		g_VertexBuffer->Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateMeshField(void)
{
	//g_Field.pos.x = GetPlayer()->GetPosition().x-250.0f;
	//g_Field.pos.z = GetPlayer()->GetPosition().z-250.0f;

	//if (GetStopAnything() == false) { g_Field.rot.y += (0.03f / GetSlowNum()); }

#ifdef DEBUG
	if (GetKeyboardPress(DIK_K)) { g_Field.pos.y += 1.0f; }
	if (GetKeyboardPress(DIK_L)) { g_Field.pos.y -= 1.0f; }
	char* str = GetDebugStr();
	//sprintf(&str[strlen(str)], "    MeshField.Y : %.2f", g_Field.pos.y);
#endif
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawMeshField(void)
{
	SetCullingMode(CULL_MODE_BACK);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �C���f�b�N�X�o�b�t�@�ݒ�
	GetDeviceContext()->IASetIndexBuffer(g_IndexBuffer, DXGI_FORMAT_R16_UINT, 0);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �}�e���A���ݒ�
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	SetMaterial(material);

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(g_TexNo));


	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Field.mtxWorld);

	// �X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScl, g_Field.scl.x, g_Field.scl.y, g_Field.scl.z);
	D3DXMatrixMultiply(&g_Field.mtxWorld, &g_Field.mtxWorld, &mtxScl);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Field.rot.y, g_Field.rot.x, g_Field.rot.z);
	D3DXMatrixMultiply(&g_Field.mtxWorld, &g_Field.mtxWorld, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, g_Field.pos.x, g_Field.pos.y, g_Field.pos.z);
	D3DXMatrixMultiply(&g_Field.mtxWorld, &g_Field.mtxWorld, &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	SetWorldMatrix(&g_Field.mtxWorld);

	// �|���S���̕`��
	GetDeviceContext()->DrawIndexed(g_IndexNum, 0, 0);
}

