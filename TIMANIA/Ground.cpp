#include "Ground.h"

void GROUND::Prepare()
{
	Initialize();

	pModel = GetReadModel(READ_MODEL::RM_PLANE_3);
	if (GetStage() == 0) { pModel = GetReadModel(READ_MODEL::RM_PLANE_1); }
	else if (GetStage() == 1) { pModel = GetReadModel(READ_MODEL::RM_PLANE_2); }
	else if (GetStage() == 2) { pModel = GetReadModel(READ_MODEL::RM_PLANE_3); }

	Position = D3DXVECTOR3(0.0f, -Y_AXIS, 0.0f);

	Size = D3DXVECTOR3(100000.0f, 1.0f, 100000.0f);
	use = true;
}

void GROUND::Update()
{

}