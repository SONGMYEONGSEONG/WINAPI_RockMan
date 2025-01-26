#pragma once
#include "Character.h"
#include "Components/SpriteRenderer.h" //��������Ʈ bmp ������ ����Ͽ� ���� �ʿ���
#include "Components/SpriteAnimation.h" //��������Ʈ bmp ������ ����Ͽ� �ִϸ��̼� �ʿ���
#include "GameMecro.h"
#include "ScroolManager.h"

#include <array>
#include "Bullet.h"//�Ѿ�(����) ���
#include "ObjectManager.h"//���� ������Ʈ�� �浹üũ�� �Ŵ���
#include <cmath> //vector2 ����ϱ����� ���

#ifndef ENEMY_H
#define ENEMY_H
namespace GAME
{
	class Enemy : public GAME::Character
	{
	protected:

		ENGINE::Vector2 Enemy_Init_Point; //Enemy �ʱ� ��ǥ 
		RECT* Enemy_Target_HitAtea; // Enemy�� ���� ��ǥ (��ǥ: �÷��̾�)

		BOOL islife;	//ȭ�鿡 ��µɋ� �츮�� üũ

		UINT Bullet_Attack; //������ �Ѿ� ���ݷ�
		UINT Body_Attack; // ������ �浹 ���ݷ� 

		BOOL bEnemy_Hit; //�÷��̾�� ������ ���ߴ��� bool ���� 
	public:


		// Character��(��) ���� ��ӵ�
		virtual VOID Idle(const FLOAT& deltaTime) abstract;
		virtual VOID Move(const FLOAT& deltaTime) abstract;
		virtual VOID Attack(const FLOAT& deltaTime) abstract;
		virtual VOID Jump(const FLOAT& deltaTime) abstract;
		virtual VOID Hit(const FLOAT& deltaTime) abstract {};//�̱���

		virtual BOOL Initialize() abstract;
		virtual VOID Enemy_Init() abstract;//���͵� ��ü Init(�÷��̾� ����� , �������� �ʱ�ȭ��)
		virtual VOID Release() abstract;
		virtual VOID Update(const FLOAT& deltaTime)abstract;
		virtual VOID Draw() abstract;
		virtual VOID StateChange(FSMState*) abstract;


		VOID Hit_Check(); // ENEMY �� Hit Check
		 //������ ��Ŭ�ε� ��ġ(��ǥ) + ���� ���� ��ġ + Enemy�� �̵��Ÿ�(Move�Լ����� �̵��ѰŸ�)
		VOID Position_Update(FLOAT Move_Distance = 0);// �̵��ϴ� ���ΰ�쿡�� ���ڰ��� ������� 
		//Enemy Rect����(HitArea) ���� 
		VOID HitArea_Update(const SIZE Enemy_Size, const LONG Left_add, const LONG Top_add, const LONG Right_add, const LONG Bottom_add);

		UINT Get_Bullet_Attack() { return Bullet_Attack; };
		UINT Get_Metol_Attack() { return Body_Attack; };
		BOOL Get_islife() { return islife; };

		//Enemy ��ü�� �ʱ���� ��ǥ Set �Լ�
		VOID Set_Enemy_Init_Point(ENGINE::Vector2 Init_Point);
		VOID Set_PlayerHitArea(RECT* PlayerHitArea);
		//Enemy > Player���� ���ݼ��� bool���� ������ �Լ� 
		VOID Set_HItCheck();

	};
}
#endif
