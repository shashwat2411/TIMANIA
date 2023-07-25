#pragma once
#include "main.h"
#include "renderer.h"
#include "Texture.h"


#define _2D
//#define _3D

#define WHITE D3DXCOLOR(1.0f ,1.0f ,1.0f ,1.0f)
#define SELECTED_COLOR D3DXCOLOR(1.0f, 0.0f, 0.74f, 1.0f);

class UI
{
public:
	D3DXMATRIX mtxWorld;

	D3DXMATRIX mtxView;
	D3DXMATRIX ScalingMatrix;
	D3DXMATRIX TranslateMatrix;

	MATERIAL Material;
	D3DXCOLOR Color;

	D3DXVECTOR3 Position;
	D3DXVECTOR3 Offset;
	D3DXVECTOR2 Size;
	D3DXVECTOR2 Scaling;
	D3DXVECTOR3 Move;

	VERTEX_3D* vertex;

	float left;
	float right;

	bool animate;
	bool animationOver;

	float animationTimer;
	int animationTimerMax;
	float oneFrameTime;

	D3DXVECTOR2 animationOffset;
	int FrameWidth;
	int FrameHeight;
	D3DXVECTOR2 TextureSize;

	//int frameRate;
	//int frameCount;
	//bool animate;
	//D3DXVECTOR2 animationOffset;
	//float yoko;
	//float tate;
	//int yokoNum;
	//int tateNum;
	//int imageNum;
	//bool animationOver;

	bool use;
	unsigned int TextNo;

public:

	void Initialize();
	void UnInitialize();
	void Draw();
	void Animate();

	virtual void Prepare() = 0;
	virtual void Update() = 0;
};