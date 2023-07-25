#pragma once
#include "object.h"

class POINTER :public OBJECT
{
public:
	D3DXVECTOR3 PointerMoveSpeed;
	int flicker;

public:

	void Prepare() override;
	void Update() override;

};

HRESULT InitPointer();
void UnInitPointer();
void UpdatePointer();
void DrawPointer();
POINTER* GetPointer();
void SetPointer(D3DXVECTOR3 pos);