#pragma once
#include "Enemy.h"
#include "Components/SpriteRenderer.h" //스프라이트 bmp 파일을 사용하여 분할 필요함
#include "Components/SpriteAnimation.h" //스프라이트 bmp 파일을 사용하여 애니메이션 필요함
#include "GameMecro.h"

#include <array>
#include "Bullet.h"//총알(공격) 헤더
#include "ObjectManager.h"//각종 오브젝트들 충돌체크용 매니저

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

		// FSM을(를) 통해 상속됨
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
			State_Change_CoolTime = 3,//동작 변경 쿨타임
			Enemy_Tower_Life = 50,
			Enemy_Tower_Bullet_Count = 2, //타워의 총알이 한 화면에 있을수 있는 갯수
			Attack_CoolTime = 10, //타워의 공격 쿨타임
			Enemy_Tower_Bullet_Speed = 50,
			Enemy_Tower_Bullet_Attack = 3, // 총알 공격력
			Enemy_Tower_Attack = 2, // 플레이어와 충돌시 공격력 
		};


		ENGINE::SpriteRenderer* renderer;

		FLOAT State_elipsed_Time;//Idle 및 상태의 유지시간(상태 변경에  필요한 시간)
		FLOAT Attack_Time; //공격 쿨타임 

		std::array<Bullet*, Enemy_Tower_Bullet_Count> arrBullet; //총알 bullet 관리

	public:
		Tower() {};
		virtual ~Tower() {};

		// Enemy을(를) 통해 상속됨
		virtual VOID Idle(const FLOAT& deltaTime) override;
		virtual VOID Move(const FLOAT& deltaTime) override {}; // 사용안함
		virtual VOID Attack(const FLOAT& deltaTime) override ;
		virtual VOID Jump(const FLOAT& deltaTime) override;
		virtual VOID Hit(const FLOAT& deltaTime) override;// 피격시 애니메이션 동작

		virtual BOOL Initialize() override;
		virtual VOID Enemy_Init() override;
		virtual VOID Release() override;
		virtual VOID Update(const FLOAT& deltaTime) override;
		virtual VOID Draw() override;
		virtual VOID StateChange(FSMState*) override;

	};
}
#endif