
#include "scene.h"
#include "fade.h"
#include "Title.h"
#include "SelectStage.h"
#include "CharacterSelect.h"
#include "Game.h"
#include "Result.h"
#include "model.h"

//======================================================
//	�V�[���i�[�ϐ�
//======================================================
static SCENE	g_SceneIndex = NONE;
static SCENE g_SceneNextIndex = g_SceneIndex;

void	InitScene(SCENE ScreenNo)	//	�V�[��������
{
	g_SceneIndex = g_SceneNextIndex = ScreenNo;

	switch (g_SceneIndex)
	{
	case NONE:
		break;
	case TITLE:
		InitTitle();
		break;
	case CHARACTER:
		InitCharacterSelect();
		break;
	case SELECT:
		InitSelectStage();	//	�X�e�[�W�I���̏I������
		break;
	case GAME:
		InitGame();
		break;
	case RESULT:
		InitResult();
		break;
	default:
		exit(999);
		break;
	}

}

void	UnInitScene()	//	�V�[���I������
{
	switch (g_SceneIndex)
	{
	case NONE:
		break;
	case TITLE:
		UnInitTitle();
		break;
	case CHARACTER:
		UnInitCharacterSelect();	//	�X�e�[�W�I���̏I������
		break;
	case SELECT:
		UnInitSelectStage();	//	�X�e�[�W�I���̏I������
		break;
	case GAME:
		UnInitGame();
		break;
	case RESULT:
		UnInitResult();
		break;
	default:
		exit(999);
		break;
	}
}

void	UpdateScene()	//	�V�[���X�V����
{
	switch (g_SceneIndex)
	{
	case NONE:
		break;
	case	TITLE:
		UpdateTitle();
		break;
	case CHARACTER:
		UpdateCharacterSelect();	//	�X�e�[�W�I���̏I������
		break;
	case	SELECT:
		UpdateSelectStage();
		break;
	case	GAME:	
		UpdateGame();
		break;
	case	RESULT:
		UpdateResult();
		break;
	default:
		exit(999);
		break;
	}

}

void	DrawScene()	//	�V�[���`�揈��
{
	switch (g_SceneIndex)
	{
	case	TITLE:
		DrawTitle();
		break;
	case CHARACTER:
		DrawCharacterSelect();	//	�X�e�[�W�I���̏I������
		break;
	case	SELECT:	
		DrawSelectStage();
		break;
	case	GAME:
		DrawGame();
		break;
	case	RESULT:
		DrawResult();
		break;
	}
}


void	SetScene(const	SCENE	new_Scene)	//	�V�[���ϐ��̃Z�b�g
{
	g_SceneNextIndex = new_Scene;
}
const	SCENE& GetScene()
{
	return g_SceneIndex;
}

void CheckScene()
{
	if (g_SceneIndex != g_SceneNextIndex)
	{
		UnInitScene();
		InitScene(g_SceneNextIndex);
	}
}



