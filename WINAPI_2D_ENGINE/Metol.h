#pragma once
#include "Enemy.h"
#include "Components/SpriteRenderer.h" //��������Ʈ bmp ������ ����Ͽ� ���� �ʿ���
#include "Components/SpriteAnimation.h" //��������Ʈ bmp ������ ����Ͽ� �ִϸ��̼� �ʿ���
#include "GameMecro.h"

#include <array>
#include "Bullet.h"//�Ѿ�(����) ���
#include "ObjectManager.h"//���� ������Ʈ�� �浹üũ�� �Ŵ���

#ifndef METOL_H
#define METOL_H
namespace GAME
{
	class Metol_IdleState : public FSMState
	{
	private:
		Metol_IdleState() {}
	public:
		static Metol_IdleState* Instance()
		{
			static Metol_IdleState Instance;
			return &Instance;
		}

		// FSM��(��) ���� ��ӵ�
		virtual VOID Enter(Character*) override;
		virtual VOID Excute(Character*, const FLOAT& deltaTime) override;
		virtual VOID Exit(Character*) override;

	};


	class Metol : public GAME::Enemy
	{
	private:
		enum Enemy_Metol_AnimationIndex
		{
			Idle_Left = 0,
			Idle_Right = 1,
			Move_Left = 2,
			Move_Rignt = 3,
			Hit_Left = 4,
			Hit_Right = 5,
			
		};
		//������������� �� ���� ©���ְ��ؾ��� (�̺κ��� ��ȹ�ڰ� �ǵ帮�� �κ��̱� ������)
		enum Enemy_Metol_Data
		{
			SpritesX = 1,
			SpritesY = 6,
			Move_Distance = 100,
			Speed = 100,
			JumpSpeed = 0,
			Init_X = 400,
			Init_Y = 500,
			State_Change_CoolTime = 5,//���� ���� ��Ÿ��
			Enemy_Metol_Life = 30,
			Enemy_Metol_Bullet_Count = 2, //������ �Ѿ��� �� ȭ�鿡 ������ �ִ� ����
			Attack_CoolTime = 3, //������ ���� ��Ÿ��
			Enemy_Metol_Bullet_Speed = 70,
			Enemy_Metol_Bullet_Attack = 1, // �Ѿ� ���ݷ�
			Enemy_Metol_Attack = 2, // �÷��̾�� �浹�� ���ݷ� 
		};

		
		ENGINE::SpriteRenderer* renderer;
		
		FLOAT Metol_Distance; //������ �����ǰ� ������ �Ÿ�
		FLOAT Distance_Count; //������ ������������ �α����� ī��Ʈ 
		FLOAT State_elipsed_Time;//Idle �� ������ �����ð�(���� ���濡  �ʿ��� �ð�)
		FLOAT Attack_Time; //���� ��Ÿ�� 

		std::array<Bullet*, Enemy_Metol_Bullet_Count> arrBullet; //�Ѿ� bullet ����

	public:
		Metol() {};
		virtual ~Metol() {};

		// Enemy��(��) ���� ��ӵ�
		virtual VOID Idle(const FLOAT& deltaTime) override;
		virtual VOID Move(const FLOAT& deltaTime) override;
		virtual VOID Attack(const FLOAT& deltaTime) override;
		virtual VOID Jump(const FLOAT& deltaTime) override;
		virtual VOID Hit(const FLOAT& deltaTime) override;// �ǰݽ� �ִϸ��̼� ����

		virtual BOOL Initialize() override;
		virtual VOID Enemy_Init() override;
		virtual VOID Release() override;
		virtual VOID Update(const FLOAT& deltaTime) override;
		virtual VOID Draw() override;
		virtual VOID StateChange(FSMState*) override;

	};
}
#endif
