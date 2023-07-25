#pragma once
#include "object.h"

class SWORD :public OBJECT
{
private:
	D3DXVECTOR3 SizeBackUp;

public:

	void Prepare() override;
	void Update() override;

};

SWORD* GetSword();