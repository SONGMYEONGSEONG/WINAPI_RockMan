#pragma once
#include "GameMecro.h"
#include "Character.h"
#include "EnemyManager.h" // EnemyManager 목적용도 
#include "ResourceManager.h" // bitmap 자료형 
#include "Components/InputComponent.h" // Player의 Input컴포넌트 참조(조작키)
#include "ScroolManager.h"
#include "SceneManager.h"//Test backDC 호출용도(hitarea영역확인요)


//Player내에서 object 객체와 충돌체크할수있게해야함

#ifndef PLAYER_H
#define PLAYER_H

namespace GAME
{
#define ATTACK_BUTTON 0x5A // 'Z'키

	//플레이어 조작상태 FSM 
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

		// FSM을(를) 통해 상속됨
		virtual VOID Enter(Character*) override;
		virtual VOID Excute(Character*, const FLOAT& deltaTime) override;
		virtual VOID Exit(Character*) override;

	};

	//플레이어 피격상태 FSM(조작불가)
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

		// FSM을(를) 통해 상속됨
		virtual VOID Enter(Character*) override;
		virtual VOID Excute(Character*, const FLOAT& deltaTime) override;
		virtual VOID Exit(Character*) override;

	};


	//플레이어 스토리(연출)상태 FSM(조작불가)
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

		// FSM을(를) 통해 상속됨
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
			Hit_Speed = 10,//피격 당했을때
			JumpSpeed = 300,
			Init_X = 400,
			Init_Y = 500,
			Attack_CoolTime = 2, //공격쿨타임 0.2초
			Grace_Time = 1, // 피격후 무적시간 
			Player_HP = 10, //플레이어 체력
			Player_Life = 3, //플레이어 목숨
			Bullet_Count =5, //화면에 있을수 있는 총알 갯수 
			Bullet_Speed = 400, // 총알 스피드 
		};

		ENGINE::SpriteRenderer* renderer;

		std::array<Bullet*, Bullet_Count> arrBullet; //총알 bullet 관리
		FLOAT Player_Speed; // 플레이어의 현재 이동속도
		BOOL Grace; // 피격후 무적 상태 변수 
		UINT Life; // 객체의 목숨갯수

		VOID Player_Init(); //플레이어 객체 INIT 함수
		VOID Player_Status_Init(); // 플레이어 상태 Init함수(죽거나 , 게임을 다시 할경우 호출하는 함수)
		VOID Player_HitCheck(); // 플레이어<-Enemy hit했는지 확인함수 
		VOID Player_Bullet(const FLOAT& deltaTime); // 플레이어 총알 사용 함수
		VOID Player_Rect_Set(); // Update시 플레이어 영역을 매 프레임마드 set하는 함수 
		VOID Player_Interact(const FLOAT& deltaTime); //object들과 상호작용 영역 체크 함수 
		VOID Player_Move(const FLOAT& deltaTime);//플레이어 움직이는경우 스크롤 및 좌표 갱신

		VOID Player_Death(); //플레이어 사망시 구현 코드 
	
	public:
		Player() {};
		~Player() {};

		virtual VOID Idle(const FLOAT& deltaTime) override;
		virtual VOID Move(const FLOAT& deltaTime) override;
		virtual VOID Attack(const FLOAT& deltaTime) override;
		virtual VOID Jump(const FLOAT& deltaTime) override;
		virtual VOID Hit(const FLOAT& deltaTime) override;
	
		VOID Jump_Animation();		//점프애니매이션 인덱스 호출

		virtual BOOL Initialize() override;
		virtual VOID Release() override;
		virtual VOID Update(const FLOAT& deltaTime) override;
		virtual VOID Draw() override;
		virtual VOID StateChange(FSMState*) override;

		UINT Get_Life() { return Life; }
		FLOAT Get_Speed() { return (FLOAT)Speed; };

		VOID Set_Life(UINT cur_Life) { Life = cur_Life; }

		VOID Player_Move_animation(const FLOAT& deltaTime);//플레이어 무브 애니메이션 동작 코드 

		
	};

}
#endif
