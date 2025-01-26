#pragma once
#include "Enemy.h"
#include "Components/SpriteRenderer.h" //��������Ʈ bmp ������ ����Ͽ� ���� �ʿ���
#include "Components/SpriteAnimation.h" //��������Ʈ bmp ������ ����Ͽ� �ִϸ��̼� �ʿ���
#include "GameMecro.h"

#include <array>
#include "Bullet.h"//�Ѿ�(����) ���
#include "ObjectManager.h"//���� ������Ʈ�� �浹üũ�� �Ŵ���

#ifndef TOWER_H
#define TOWER_H
namespace GAME
{
	class Tower_IdleState : public FSMState
	{
	private:
		Tower_IdleState() {}
	public:
		static Tower_IdleState* Instance()
		{
			static Tower_IdleState Instance;
			return &Instance;
		}

		// FSM��(��) ���� ��ӵ�
		virtual VOID Enter(Character*) override;
		virtual VOID Excute(Character*, const FLOAT& deltaTime) override;
		virtual VOID Exit(Character*) override;

	};


	class Tower : public GAME::Enemy
	{
	private:
		enum Enemy_Tower_AnimationIndex
		{
			Idle_Left = 0,
			Idle_Right = 1,
			Attack_Left = 2,
			Attack_Right = 3,
			Idle_Hit_Left ,
			Idle_Hit_Right ,
			Attack_Hit_Left ,
			Attack_Hit_Right ,

		};
		enum Enemy_Tower_Data
		{
			SpritesX = 1,
			SpritesY = 8,
			Speed = 0,
			JumpSpeed = 0,
			Init_X = 400,
			Init_Y = 500,
			State_Change_CoolTime = 3,//���� ���� ��Ÿ��
			Enemy_Tower_Life = 50,
			Enemy_Tower_Bullet_Count = 2, //Ÿ���� �Ѿ��� �� ȭ�鿡 ������ �ִ� ����
			Attack_CoolTime = 10, //Ÿ���� ���� ��Ÿ��
			Enemy_Tower_Bullet_Speed = 50,
			Enemy_Tower_Bullet_Attack = 3, // �Ѿ� ���ݷ�
			Enemy_Tower_Attack = 2, // �÷��̾�� �浹�� ���ݷ� 
		};


		ENGINE::SpriteRenderer* renderer;

		FLOAT State_elipsed_Time;//Idle �� ������ �����ð�(���� ���濡  �ʿ��� �ð�)
		FLOAT Attack_Time; //���� ��Ÿ�� 

		std::array<Bullet*, Enemy_Tower_Bullet_Count> arrBullet; //�Ѿ� bullet ����

	public:
		Tower() {};
		virtual ~Tower() {};

		// Enemy��(��) ���� ��ӵ�
		virtual VOID Idle(const FLOAT& deltaTime) override;
		virtual VOID Move(const FLOAT& deltaTime) override {}; // ������
		virtual VOID Attack(const FLOAT& deltaTime) override ;
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