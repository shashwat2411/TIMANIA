#pragma once

#ifndef SCENE_H_

#define	SCENE_H_

enum SCENE
{
	NONE = 0,
	TITLE,
	SELECT,
	CHARACTER,
	GAME,
	RESULT,

	MAX
};

//===========================================================
//	シーンenum	(macro.hに定義してある)
//===========================================================

void	InitScene(SCENE SceneNo);	//	シーン初期化
void	UnInitScene();	//	シーン終了処理
void	UpdateScene();	//	シーン更新処理
void	DrawScene();	//	シーン描画処理

void	SetScene(const	SCENE	new_Scene);	//	シーン変数のセット
const	SCENE& GetScene();
void	CheckScene();

#endif // !SCENE_H_

