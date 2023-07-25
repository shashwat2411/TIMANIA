#pragma once
#include "scene.h"
#include "main.h"
#include "renderer.h"
#include "Texture.h"
#include "inputx.h"

#define FADE_SPEED 0.02f
#define FADE_WAIT 30//(0.9f / FADE_SPEED)

enum TYPE
{
	FADENONE = 0,
	FADEIN = 1,
	FADEOUT = 2
};

class FADE
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

	bool use;
	int count;
	unsigned int TextNo;

	TYPE Type;

public:
	void Initialize();
	void UnInitialize();
	void Draw();

	void Prepare();
	void Update();
};


HRESULT InitFade();
void UnInitFade();
void UpdateFade();
void DrawFade();

void SetFade(TYPE type);
void Fader(const bool condition, const SCENE scene);