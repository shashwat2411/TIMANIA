#include "fade.h"
#include "camera.h"
#include "sound.h"
#include "UI.h"
//============================
//�}�N����`
//============================

//============================
//�v���g�^�C�v�錾
//============================

//============================
//�O���[�o���ϐ�
//============================
FADE g_Fade;

static bool over = true;
bool out = false;

bool FadeNext = false;
int FadeTimer = 0;

static ID3D11Buffer		*g_VertexBuffer = NULL;	// ���_�o�b�t�@
//============================
//������
//============================
void FADE::Initialize()
{
	Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Scaling = D3DXVECTOR2(1.0f, 1.0f);
	Size = D3DXVECTOR2(1.0, 1.0f);
	Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Offset = D3DXVECTOR3(0.0f, 0.0f, -3.0f);
	Color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	use = false;

	// ���_�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBuffer);


	//// ���_�o�b�t�@�ɒl���Z�b�g����
	//{
	//	D3D11_MAPPED_SUBRESOURCE msr;
	//	GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	//	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

	//	// ���_���W�̐ݒ�
	//	vertex[0].Position = D3DXVECTOR3(-(Size.x * Scaling.x) / 2.0f, 0.0f, 0.0f);
	//	vertex[1].Position = D3DXVECTOR3(-(Size.x * Scaling.x) / 2.0f, (Size.y * Scaling.y), 0.0f);
	//	vertex[2].Position = D3DXVECTOR3((Size.x * Scaling.x) / 2.0f, 0.0f, 0.0f);
	//	vertex[3].Position = D3DXVECTOR3((Size.x * Scaling.x) / 2.0f, (Size.y * Scaling.y), 0.0f);

	//	// ���_�J���[�̐ݒ�
	//	vertex[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//	vertex[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//	vertex[2].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//	vertex[3].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//	// �e�N�X�`�����W�̐ݒ�
	//	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 1.0f);
	//	vertex[1].TexCoord = D3DXVECTOR2(0.0f, 0.0f);
	//	vertex[2].TexCoord = D3DXVECTOR2(1.0f, 1.0f);
	//	vertex[3].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

	//	GetDeviceContext()->Unmap(g_VertexBuffer, 0);
	//}


	TextNo = 0;
	count = 0;

	ZeroMemory(&Material, sizeof(Material));
	Material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

}

void FADE::UnInitialize()
{
	if (g_VertexBuffer != NULL)
	{// ���_�o�b�t�@�̉��
		g_VertexBuffer->Release();
		g_VertexBuffer = NULL;
	}
}

void FADE::Draw()
{
	SetWorldViewProjection2D();
	// ���e�X�g��L����
	SetAlphaTestEnable(true);
	SetDepthEnable(false);

	// ���C�e�B���O�𖳌�
	SetLightEnable(false);



	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// ���_�o�b�t�@�ɒl���Z�b�g����
	{
		D3D11_MAPPED_SUBRESOURCE msr;
		GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

		VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

		// ���_���W�̐ݒ�
		vertex[0].Position = D3DXVECTOR3(-(Size.x * Scaling.x) / 2.0f, -(Size.y * Scaling.y) / 2.0f, 0.0f);
		vertex[1].Position = D3DXVECTOR3(+(Size.x * Scaling.x) / 2.0f, -(Size.y * Scaling.y) / 2.0f, 0.0f);
		vertex[2].Position = D3DXVECTOR3(-(Size.x * Scaling.x) / 2.0f, +(Size.y * Scaling.y) / 2.0f, 0.0f);
		vertex[3].Position = D3DXVECTOR3(+(Size.x * Scaling.x) / 2.0f, +(Size.y * Scaling.y) / 2.0f, 0.0f);

		// ���_�J���[�̐ݒ�
		vertex[0].Diffuse = Color;
		vertex[1].Diffuse = Color;
		vertex[2].Diffuse = Color;
		vertex[3].Diffuse = Color;

		// �e�N�X�`�����W�̐ݒ�
		vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);
		vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);
		vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);
		vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);

#ifdef _2D
		for (int i = 0; i < 4; i++)
		{
			vertex[i].Position.x += Position.x;
			vertex[i].Position.y += Position.y;
			vertex[i].Position.z = 0.0f;
		}

		// �e�N�X�`���ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(TextNo));
#endif

		GetDeviceContext()->Unmap(g_VertexBuffer, 0);

#ifdef _2D
		// �|���S���̕`��
		GetDeviceContext()->Draw(4, 0);
#endif
	}

#ifdef _3D
	if (use)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&mtxWorld);

		CAMERA* cam = GetCamera();

		mtxView = cam->mtxInvView;
		mtxView._41 = 0;
		mtxView._42 = 0;
		mtxView._43 = 0;

		Position = cam->pos + Offset + D3DXVECTOR3(0.0f, -0.5f, 3.0f);
		mtxWorld = mtxView;
		// �ړ��𔽉f
		D3DXMatrixScaling(&ScalingMatrix, (Size.x * Scaling.x), (Size.y * Scaling.y), 0.0f);
		D3DXMatrixTranslation(&TranslateMatrix, Position.x, Position.y, Position.z);

		//D3DXMatrixMultiply(&mtxWorld, &ScalingWorld, &TranslateMatrix);
		//D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxView);

		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &TranslateMatrix);
		// ���[���h�}�g���b�N�X�̐ݒ�
		SetWorldMatrix(&mtxWorld);

		// �}�e���A���ݒ�
		//SetMaterial(Material);

		// �e�N�X�`���ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(TextNo));

		// �|���S���̕`��
		GetDeviceContext()->Draw(4, 0);
	}
#endif

	//// ���C�e�B���O��L����
	//SetLightEnable(true);

	// ���e�X�g�𖳌���
	SetDepthEnable(true);
	SetAlphaTestEnable(false);
}
void FADE::Prepare()
{
	Initialize();

	TextNo = LoadTexture((char*) "data/TEXTURE/fade.png");

	Offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Position = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
	Size = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);

	use = true;

}


//============================
//�X�V����
//============================
void FADE::Update()
{
	if (use == true)
	{
		over = false;
		if (Type == FADEIN)
		{
			Color.a -= FADE_SPEED;
			if (Color.a <= ALPHA_LOWEST)
			{
				Type = FADENONE;
				over = true;
			}
		}
		if (Type == FADEOUT)
		{
			Color.a += FADE_SPEED;
			if (Color.a >= 1.0f)
			{
				//Type = FADENONE;
				Color.a = 1.0f;
				over = true;
			}
		}
		if (Type == FADENONE)
		{
			Color.a = ALPHA_LOWEST;
		}

#ifdef DEBUG
		char* str = GetDebugStr();
		//sprintf(&str[strlen(str)], "     CamX : %.2f, CamY : %.2f, CamZ : %.2f", GetCamera()->pos.x, GetCamera()->pos.y, GetCamera()->pos.z);
		//sprintf(&str[strlen(str)], "     Color Alpha : %.2f", g_Fade.Color.a);
#endif
	}
}


HRESULT InitFade()
{
	g_Fade.Prepare();
	return S_OK;
}

void UnInitFade()
{
	g_Fade.UnInitialize();
}

void UpdateFade()
{
	g_Fade.Update();
}

void DrawFade()
{
	//SetBlendState(BLEND_MODE_SUBTRACT);
	g_Fade.Draw();
	//SetBlendState(BLEND_MODE_ALPHABLEND);
}


void SetFade(TYPE type)
{
	if (g_Fade.use == true)
	{
		g_Fade.Type = type;

		if (g_Fade.Type == FADEIN) { g_Fade.Color.a = 1.0f; }
		else if (g_Fade.Type == FADEOUT) { g_Fade.Color.a = ALPHA_LOWEST; }
		
	}
}


void Fader(const bool condition, const SCENE scene)
{
	if (condition == true && FadeNext == false)
	{
		SetFade(FADEOUT);
		FadeNext = true;
	}
	if (FadeNext == true)
	{
		FadeTimer += 1;
		if (FadeTimer >= FADE_WAIT)
		{
			StopSoundAll();
			SetScene(scene);
			FadeNext = false;
			FadeTimer = 0;
		}
	}
}

