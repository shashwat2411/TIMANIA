#include "Sword.h"
#include "player.h"

void SWORD::Prepare()
{
	Initialize();

	if (GetChosenPlayer() == 0){pModel = GetReadModel(READ_MODEL::RM_LASER_1);}
	else if (GetChosenPlayer() == 1){pModel = GetReadModel(READ_MODEL::RM_LASER_2);}
	else if (GetChosenPlayer() == 2){pModel = GetReadModel(READ_MODEL::RM_LASER_3);}
	Size = D3DXVECTOR3(2.0f, 2.0f, 2.0f);
	SizeBackUp = Size;
	CollisionSize = Size;

	Shadow.SetScaling(8.0f);

	use = false;
}

void SWORD::Update()
{
	if (GetPlayer()->attack == true) { use = true; }
	if (use == true)
	{
		Counter++;

		damage = GetPlayer()->GetDamage();
		//Rotation.y = GetPlayer()->GetRotation().y + (Counter * 60);
		Size.x += (GetPlayer()->range.x / (GetPlayer()->attackCoolDownMax));
		Size.y += (GetPlayer()->range.y / (GetPlayer()->attackCoolDownMax));
		Size.z += (GetPlayer()->range.z / (GetPlayer()->attackCoolDownMax));
		CollisionSize = Size;
		//Rotation.y += 20;
		Position = GetPlayer()->GetPosition();

		if (Counter >= GetPlayer()->attackCoolDownMax)
		{
			Size = SizeBackUp;
			use = false;
			GetPlayer()->attack = false;
			Counter = 0;
		}

	}

	Shadow.Update();
	Shadow.SetPosition(D3DXVECTOR3(Position.x, SHADOW_ERROR, Position.z));
}
