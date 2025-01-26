#pragma once
#include "Character.h"
#include "Components/SpriteRenderer.h" //스프라이트 bmp 파일을 사용하여 분할 필요함
#include "Components/SpriteAnimation.h" //스프라이트 bmp 파일을 사용하여 애니메이션 필요함
#include "GameMecro.h"
#include "ScroolManager.h"

#include <array>
#include "Bullet.h"//총알(공격) 헤더
#include "ObjectManager.h"//각종 오브젝트들 충돌체크용 매니저
#include <cmath> //vector2 사용하기위한 헤더

#ifndef ENEMY_H
#define ENEMY_H
namespace GAME
{
	class Enemy : public GAME::Character
	{
	protected:

		ENGINE::Vector2 Enemy_Init_Point; //Enemy 초기 좌표 
		RECT* Enemy_Target_HitAtea; // Enemy의 공격 목표 (목표: 플레이어)

		BOOL islife;	//화면에 출력될떄 살리는 체크

		UINT Bullet_Attack; //메톨의 총알 공격력
		UINT Body_Attack; // 메톨의 충돌 공격력 

		BOOL bEnemy_Hit; //플레이어에게 공격을 당했는지 bool 변수 
	public:


		// Character을(를) 통해 상속됨
		virtual VOID Idle(const FLOAT& deltaTime) abstract;
		virtual VOID Move(const FLOAT& deltaTime) abstract;
		virtual VOID Attack(const FLOAT& deltaTime) abstract;
		virtual VOID Jump(const FLOAT& deltaTime) abstract;
		virtual VOID Hit(const FLOAT& deltaTime) abstract {};//미구현

		virtual BOOL Initialize() abstract;
		virtual VOID Enemy_Init() abstract;//몬스터들 객체 Init(플레이어 사망시 , 스테이즈 초기화시)
		virtual VOID Release() abstract;
		virtual VOID Update(const FLOAT& deltaTime)abstract;
		virtual VOID Draw() abstract;
		virtual VOID StateChange(FSMState*) abstract;


		VOID Hit_Check(); // ENEMY 용 Hit Check
		 //씬에서 스클로된 위치(좌표) + 몹의 생성 위치 + Enemy의 이동거리(Move함수에서 이동한거리)
		VOID Position_Update(FLOAT Move_Distance = 0);// 이동하는 몹인경우에만 인자값을 넣으면됨 
		//Enemy Rect영역(HitArea) 정의 
		VOID HitArea_Update(const SIZE Enemy_Size, const LONG Left_add, const LONG Top_add, const LONG Right_add, const LONG Bottom_add);

		UINT Get_Bullet_Attack() { return Bullet_Attack; };
		UINT Get_Metol_Attack() { return Body_Attack; };
		BOOL Get_islife() { return islife; };

		//Enemy 객체의 초기등장 좌표 Set 함수
		VOID Set_Enemy_Init_Point(ENGINE::Vector2 Init_Point);
		VOID Set_PlayerHitArea(RECT* PlayerHitArea);
		//Enemy > Player에게 공격성공 bool값을 보내는 함수 
		VOID Set_HItCheck();

	};
}
#endif
