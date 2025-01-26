#pragma once
#include "Enemy.h"
#include "Components/SpriteRenderer.h" //스프라이트 bmp 파일을 사용하여 분할 필요함
#include "Components/SpriteAnimation.h" //스프라이트 bmp 파일을 사용하여 애니메이션 필요함
#include "GameMecro.h"

#include <array>
#include "Bullet.h"//총알(공격) 헤더
#include "ObjectManager.h"//각종 오브젝트들 충돌체크용 매니저

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

		// FSM을(를) 통해 상속됨
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
		//파일입출력으로 다 뺴서 짤수있게해야함 (이부분은 기획자가 건드리는 부분이기 때문에)
		enum Enemy_Metol_Data
		{
			SpritesX = 1,
			SpritesY = 6,
			Move_Distance = 100,
			Speed = 100,
			JumpSpeed = 0,
			Init_X = 400,
			Init_Y = 500,
			State_Change_CoolTime = 5,//동작 변경 쿨타임
			Enemy_Metol_Life = 30,
			Enemy_Metol_Bullet_Count = 2, //메톨의 총알이 한 화면에 있을수 있는 갯수
			Attack_CoolTime = 3, //메톨의 공격 쿨타임
			Enemy_Metol_Bullet_Speed = 70,
			Enemy_Metol_Bullet_Attack = 1, // 총알 공격력
			Enemy_Metol_Attack = 2, // 플레이어와 충돌시 공격력 
		};

		
		ENGINE::SpriteRenderer* renderer;
		
		FLOAT Metol_Distance; //메톨이 생성되고 움직인 거리
		FLOAT Distance_Count; //메톨이 움직임제한을 두기위한 카운트 
		FLOAT State_elipsed_Time;//Idle 및 상태의 유지시간(상태 변경에  필요한 시간)
		FLOAT Attack_Time; //공격 쿨타임 

		std::array<Bullet*, Enemy_Metol_Bullet_Count> arrBullet; //총알 bullet 관리

	public:
		Metol() {};
		virtual ~Metol() {};

		// Enemy을(를) 통해 상속됨
		virtual VOID Idle(const FLOAT& deltaTime) override;
		virtual VOID Move(const FLOAT& deltaTime) override;
		virtual VOID Attack(const FLOAT& deltaTime) override;
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
