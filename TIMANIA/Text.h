#pragma once
#include "UI.h"

class TEXT :public UI
{
protected:
	bool blink = false;

public:
	D3DXVECTOR2 SizeBackUp;

	void Prepare() override
	{
		Initialize();

		TextNo = LoadTexture((char*)"data/TEXTURE/hp.png");
		use = false;
	}

	void Update() override
	{

	}

	void SetText(unsigned int texture, D3DXVECTOR3 offset, D3DXVECTOR2 size)
	{
		Prepare();
		TextNo = texture;
		Offset = offset;
		Size = size;
		SizeBackUp = size;
	}
	void SetText(unsigned int texture, D3DXVECTOR3 offset, D3DXVECTOR2 size, bool u)
	{
		SetText(texture, offset, size);
		use = u;
	}
	void SetText(unsigned int texture, D3DXVECTOR3 offset, D3DXVECTOR2 size, bool u, D3DXCOLOR color)
	{
		SetText(texture, offset, size, u);
		Color = color;
	}
	void SetText(unsigned int texture, D3DXVECTOR3 offset, D3DXVECTOR2 size, bool u, D3DXVECTOR2 num)
	{
		SetText(texture, offset, size, u);
		TextureSize.x = 1.0f / num.x;
		TextureSize.y = 1.0f / num.y;
	}
	void SetText(unsigned int texture, D3DXVECTOR3 offset, D3DXVECTOR2 size, bool u, D3DXCOLOR color, float num)
	{
		SetText(texture, offset, size, u, color);
		TextureSize.y = 1.0f/num;
	}

	void Blink(float value)
	{
		if(blink == true)
		{
			Color.a += value;
			if (Color.a >= 1.0f)
			{
				Color.a = 1.0f;
				blink = false;
			}
		}
		else if (blink == false)
		{
			Color.a -= value;
			if (Color.a <= (ALPHA_LOWEST*1.01f))
			{
				Color.a = (ALPHA_LOWEST*1.01f);
				blink = true;
			}
		}
	}

	void Appear(float value)
	{
		if (Color.a <= 1.0f) { Color.a += value; }
	}

};