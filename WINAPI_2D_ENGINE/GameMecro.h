#include "EngineMecro.h"

#ifndef GAME_MECRO_H
#define GAME_MECRO_H

namespace GAME
{
	//��׶���(���) Ÿ��
	enum class BackGround_Type { Stage1 = 0, Title = 1, Clear = 2 };

	//FSM State���� 
	//Idle, ������		//Move, �̵�����   //Story, ���丮,���� ����
	enum class State { Idle, Hit, Story };
	//ĳ������ state ���� ( FSM �ȿ��ִ� ��������)
	enum class CharacterState { None, Move, Attack, Jump };
	enum class JumpState { None, Up, Down };
	enum class ScrollDirection { None, Right, Left };
	enum class Direction { Right, Left };
	enum JumpLimit { Jump_Height_Min = 350, Jump_Height_Max = 500 };
	//enum class Enemy_Type { METOL = 0, TOWER = 1};
	enum class Character_Type { PLAYER = 99, METOL = 0, TOWER = 1 };
	enum ObjectType { Ground_Obj = 0, Block_Obj = 1, Ceiling_Obj = 2, Door_Obj = 3, };
	//enum BulletType { Player_Bullet = 0, Enemy_Metol_Bullet = 1 };
		
		
	class Character;
	__interface FSMState
	{
		VOID Enter(Character* );
		VOID Excute(Character* ,CONST FLOAT& deltaTime);
		VOID Exit(Character*);
	};

}

#endif //!GAME_MECRO_H