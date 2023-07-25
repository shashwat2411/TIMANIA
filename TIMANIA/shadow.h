#pragma once
#include "main.h"
#include "renderer.h"

class SHADOW
{
private:
	bool use;
	D3DXVECTOR3	Position;		// �|���S���̈ʒu
	D3DXVECTOR3	Rotation;		// �|���S���̌���(��])
	D3DXVECTOR3	Scaling;		// �|���S���̑傫��(�X�P�[��)

	D3DXCOLOR Color;

	MATERIAL Material;

	D3DXMATRIX mtxWorld;	// ���[���h�}�g���b�N�X
	D3DXMATRIX TranslationMatrix;
	D3DXMATRIX RotationMatrix;
	D3DXMATRIX ScalingMatrix;

public:
	void SetUse(const bool value) { use = value; }
	void SetMaterial(const MATERIAL material) { Material = material; }
	void SetPosition(const D3DXVECTOR3 value) { Position = value; }
	void SetRotation(const D3DXVECTOR3 value) { Rotation = value; }
	void SetScaling(const float value) { Scaling.x = value; Scaling.z = value; }
	void SetColor(const D3DXCOLOR value) { Color = value; }

	bool		GetUse()const { return use; }
	D3DXVECTOR3	GetPosition()const { return Position; }
	D3DXVECTOR3	GetRotation()const { return Rotation; }
	D3DXVECTOR3	GetScaling()const { return Scaling; }
	D3DXCOLOR	GetColor()const { return Color; }
	MATERIAL	GetMaterial()const { return Material; }

	void Init();
	void UnInit();
	void Update();
	void Draw();
};
//====================================================
//�v���g�^�C�v�錾
//====================================================
//HRESULT InitShadow();
//void UnInitShadow();
//void UpdateShadow();
//void DrawShadow();
//
//int	 SetShadow(D3DXVECTOR3 pos, float size);
//void ReleaseShadow(int index);
//void SetPositionShadow(int index, D3DXVECTOR3 pos);