#include "Components/SpriteRenderer.h" //스프라이트 bmp 파일을 사용하여 분할 필요함
#include "Components/SpriteAnimation.h" //스프라이트 bmp 파일을 사용하여 애니메이션 필요함
#include "GameMecro.h"

#include <array>
#include "Bullet.h"//총알(공격) 헤더
#include "ObjectManager.h"//각종 오브젝트들 충돌체크용 매니저
#include "UIGameManager.h"//플레이어 체력 인자값 전달 목적 

//이동: 좌, 우 이동가능
//점프 : 위로 점프가능
//(위에서 컨트롤 가능) (더블점프 X)
//공격 : (순수가상함수로 작성)
//죽음 : HP 0 체크후 죽음 처리
//충돌 체크 :
//FSM을 Charater에 구성


#ifndef CHARACTER_H
#define CHARACTER_H
namespace GAME
{

	//Player,적 부모클래스 
	class Character : public ENGINE::GameObject
	{
	protected:
		ENGINE::AnimationComponent* anim; //애니메이션 관리 변수

		FSMState* pCurrState; //FSM 주소(상태 변경시에 필요한 포인터주소)
		State state;	//캐릭터의 FSM상태 
		CharacterState CharState; // 캐릭터의 상태(idle상태일때의 조작가능한 상태들)

		JumpState Jumpdir;	//캐릭터의 점프상태(Move)
		FLOAT Jump_Distance = 0; // 점프길이 
		Direction dir;	//캐릭터의 방향 : 좌,우

		Character_Type Type; // 객체의 타입 ( player,몬스터 등등)

		UINT Health_Point;//객체의 에너지
		BOOL Death; // 객체의 죽음상태(0: 생존 1:죽음)
		RECT HitArea; // 충돌체크 영역 여부

		BOOL Attack_Check; // 공격에 성공/실패 여부 판단
		FLOAT Attack_Time;//character의 공격 쿨타임(공격발사주기)



	public:
		virtual ~Character() {};

		virtual VOID Idle(const FLOAT& deltaTime) abstract;
		virtual VOID Move(const FLOAT& deltaTime) abstract;
		virtual VOID Attack(const FLOAT& deltaTime) abstract;
		virtual VOID Jump(const FLOAT& deltaTime) abstract;
		virtual VOID Hit(const FLOAT& deltaTime) abstract;
		//virtual BOOL IntersectRectRe(RECT& rect1, RECT& rect2) { return TRUE; };//캐릭터 충돌영역 체크 함수 
		
		virtual BOOL Initialize()abstract;
		virtual VOID Release()abstract;
		virtual VOID Update(const FLOAT& deltaTime)abstract;
		virtual VOID Draw()abstract;
		virtual VOID StateChange(FSMState*)abstract;

		//캐릭터 객체가 오브젝트(벽)에 부딪히는지 체크하는 코드
		virtual BOOL Object_Move_Check();

		//캐릭터 객체가 땅바닥에 바닥이 닿는지 체크하는 코드 
		//반환값은 INDEX , 없을시 -1 반환
		virtual UINT Ground_Check();

		//중력코드
		virtual VOID Gravity_Down(const FLOAT& deltaTime);
		

		//천장 체크(점프시에)
		BOOL Ceiling_Check();

		State Get_State() { return state; }
		CharacterState Get_CharState() { return CharState; }
		JumpState Get_JumpState() { return Jumpdir; }
		Direction Get_dir() { return dir; }
		FLOAT Get_JumpDistance() { return Jump_Distance; }
		RECT* Get_HitArea() { return  &HitArea; }
		BOOL Get_AttackCheck() { return Attack_Check; }
		UINT Get_HealthPoint() { return Health_Point; }
		
		VOID Set_State(State State) { state = State; }
		VOID Set_CharState(CharacterState charState) { CharState = charState; }
		VOID Set_JumpState(JumpState JumpState) { Jumpdir = JumpState; }
		VOID Set_Death(BOOL isdeath) { Death = isdeath; }
		VOID ReSet_AttackCheck() { Attack_Check = FALSE; }

		ENGINE::AnimationComponent* Get_anim() { return anim; }
		//업캐스팅 되있어서 가상함수를 사용해서 자식의 함수에 접근하려고 사용
		virtual VOID Player_Move_animation(const FLOAT& deltaTime) {};//플레이어 무브 애니메이션 동작 코드 

	};

}
#endif
