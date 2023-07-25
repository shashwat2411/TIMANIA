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
//	�V�[��enum	(macro.h�ɒ�`���Ă���)
//===========================================================

void	InitScene(SCENE SceneNo);	//	�V�[��������
void	UnInitScene();	//	�V�[���I������
void	UpdateScene();	//	�V�[���X�V����
void	DrawScene();	//	�V�[���`�揈��

void	SetScene(const	SCENE	new_Scene);	//	�V�[���ϐ��̃Z�b�g
const	SCENE& GetScene();
void	CheckScene();

#endif // !SCENE_H_

