
#include "scene.h"
#include "fade.h"
#include "Title.h"
#include "SelectStage.h"
#include "CharacterSelect.h"
#include "Game.h"
#include "Result.h"
#include "model.h"

//======================================================
//	シーン格納変数
//======================================================
static SCENE	g_SceneIndex = NONE;
static SCENE g_SceneNextIndex = g_SceneIndex;

void	InitScene(SCENE ScreenNo)	//	シーン初期化
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
		InitSelectStage();	//	ステージ選択の終了処理
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

void	UnInitScene()	//	シーン終了処理
{
	switch (g_SceneIndex)
	{
	case NONE:
		break;
	case TITLE:
		UnInitTitle();
		break;
	case CHARACTER:
		UnInitCharacterSelect();	//	ステージ選択の終了処理
		break;
	case SELECT:
		UnInitSelectStage();	//	ステージ選択の終了処理
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

void	UpdateScene()	//	シーン更新処理
{
	switch (g_SceneIndex)
	{
	case NONE:
		break;
	case	TITLE:
		UpdateTitle();
		break;
	case CHARACTER:
		UpdateCharacterSelect();	//	ステージ選択の終了処理
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

void	DrawScene()	//	シーン描画処理
{
	switch (g_SceneIndex)
	{
	case	TITLE:
		DrawTitle();
		break;
	case CHARACTER:
		DrawCharacterSelect();	//	ステージ選択の終了処理
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


void	SetScene(const	SCENE	new_Scene)	//	シーン変数のセット
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



