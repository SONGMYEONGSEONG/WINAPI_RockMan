#pragma once
#include "GameMecro.h"
#include "Character.h"
#include "EnemyManager.h" // EnemyManager �����뵵 
#include "ResourceManager.h" // bitmap �ڷ��� 
#include "Components/InputComponent.h" // Player�� Input������Ʈ ����(����Ű)
#include "ScroolManager.h"
#include "SceneManager.h"//Test backDC ȣ��뵵(hitarea����Ȯ�ο�)


//Player������ object ��ü�� �浹üũ�Ҽ��ְ��ؾ���

#ifndef PLAYER_H
#define PLAYER_H

namespace GAME
{
#define ATTACK_BUTTON 0x5A // 'Z'Ű

	//�÷��̾� ���ۻ��� FSM 
	class IdleState : public FSMState
	{
	private:
		IdleState() {}
	public:
		static IdleState* Instance()
		{
			static IdleState Instance;
			return &Instance;
		}

		// FSM��(��) ���� ��ӵ�
		virtual VOID Enter(Character*) override;
		virtual VOID Excute(Character*, const FLOAT& deltaTime) override;
		virtual VOID Exit(Character*) override;

	};

	//�÷��̾� �ǰݻ��� FSM(���ۺҰ�)
	class HitState : public FSMState
	{
	private:
		HitState() {}
	public:
		static  HitState* Instance()
		{
			static HitState Instance;
			return &Instance;
		}

		// FSM��(��) ���� ��ӵ�
		virtual VOID Enter(Character*) override;
		virtual VOID Excute(Character*, const FLOAT& deltaTime) override;
		virtual VOID Exit(Character*) override;

	};


	//�÷��̾� ���丮(����)���� FSM(���ۺҰ�)
	class StoryState : public FSMState
	{
	private:
		StoryState() {}
	public:
		static  StoryState* Instance()
		{
			static StoryState Instance;
			return &Instance;
		}

		// FSM��(��) ���� ��ӵ�
		virtual VOID Enter(Character*) override;
		virtual VOID Excute(Character*, const FLOAT& deltaTime) override;
		virtual VOID Exit(Character*) override;

	};

	class Player : public GAME::Character
	{
	private:
		enum Player_AnimationIndex
		{
			Idle_Right = 0, 
			Idle_Left =1,
			Move_Rignt=2,
			Move_Left=3,
			Jump_Right=4,
			Jump_Left=5,
			Attack_Right = 6,
			Attack_Left = 7,
			Attack_Jump_Right = 8,
			Attack_Jump_Left = 9,
			Hit_Right = 10,
			Hit_left = 11,
		};
		enum Player_Data
		{
			SpritesX = 3,
			SpritesY = 12,
			Speed = 200,
			Hit_Speed = 10,//�ǰ� ��������
			JumpSpeed = 300,
			Init_X = 400,
			Init_Y = 500,
			Attack_CoolTime = 2, //������Ÿ�� 0.2��
			Grace_Time = 1, // �ǰ��� �����ð� 
			Player_HP = 10, //�÷��̾� ü��
			Player_Life = 3, //�÷��̾� ���
			Bullet_Count =5, //ȭ�鿡 ������ �ִ� �Ѿ� ���� 
			Bullet_Speed = 400, // �Ѿ� ���ǵ� 
		};

		ENGINE::SpriteRenderer* renderer;

		std::array<Bullet*, Bullet_Count> arrBullet; //�Ѿ� bullet ����
		FLOAT Player_Speed; // �÷��̾��� ���� �̵��ӵ�
		BOOL Grace; // �ǰ��� ���� ���� ���� 
		UINT Life; // ��ü�� �������

		VOID Player_Init(); //�÷��̾� ��ü INIT �Լ�
		VOID Player_Status_Init(); // �÷��̾� ���� Init�Լ�(�װų� , ������ �ٽ� �Ұ�� ȣ���ϴ� �Լ�)
		VOID Player_HitCheck(); // �÷��̾�<-Enemy hit�ߴ��� Ȯ���Լ� 
		VOID Player_Bullet(const FLOAT& deltaTime); // �÷��̾� �Ѿ� ��� �Լ�
		VOID Player_Rect_Set(); // Update�� �÷��̾� ������ �� �����Ӹ��� set�ϴ� �Լ� 
		VOID Player_Interact(const FLOAT& deltaTime); //object��� ��ȣ�ۿ� ���� üũ �Լ� 
		VOID Player_Move(const FLOAT& deltaTime);//�÷��̾� �����̴°�� ��ũ�� �� ��ǥ ����

		VOID Player_Death(); //�÷��̾� ����� ���� �ڵ� 
	
	public:
		Player() {};
		~Player() {};

		virtual VOID Idle(const FLOAT& deltaTime) override;
		virtual VOID Move(const FLOAT& deltaTime) override;
		virtual VOID Attack(const FLOAT& deltaTime) override;
		virtual VOID Jump(const FLOAT& deltaTime) override;
		virtual VOID Hit(const FLOAT& deltaTime) override;
	
		VOID Jump_Animation();		//�����ִϸ��̼� �ε��� ȣ��

		virtual BOOL Initialize() override;
		virtual VOID Release() override;
		virtual VOID Update(const FLOAT& deltaTime) override;
		virtual VOID Draw() override;
		virtual VOID StateChange(FSMState*) override;

		UINT Get_Life() { return Life; }
		FLOAT Get_Speed() { return (FLOAT)Speed; };

		VOID Set_Life(UINT cur_Life) { Life = cur_Life; }

		VOID Player_Move_animation(const FLOAT& deltaTime);//�÷��̾� ���� �ִϸ��̼� ���� �ڵ� 

		
	};

}
#endif
