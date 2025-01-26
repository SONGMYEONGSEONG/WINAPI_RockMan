#include "Components/SpriteRenderer.h" //��������Ʈ bmp ������ ����Ͽ� ���� �ʿ���
#include "Components/SpriteAnimation.h" //��������Ʈ bmp ������ ����Ͽ� �ִϸ��̼� �ʿ���
#include "GameMecro.h"

#include <array>
#include "Bullet.h"//�Ѿ�(����) ���
#include "ObjectManager.h"//���� ������Ʈ�� �浹üũ�� �Ŵ���
#include "UIGameManager.h"//�÷��̾� ü�� ���ڰ� ���� ���� 

//�̵�: ��, �� �̵�����
//���� : ���� ��������
//(������ ��Ʈ�� ����) (�������� X)
//���� : (���������Լ��� �ۼ�)
//���� : HP 0 üũ�� ���� ó��
//�浹 üũ :
//FSM�� Charater�� ����


#ifndef CHARACTER_H
#define CHARACTER_H
namespace GAME
{

	//Player,�� �θ�Ŭ���� 
	class Character : public ENGINE::GameObject
	{
	protected:
		ENGINE::AnimationComponent* anim; //�ִϸ��̼� ���� ����

		FSMState* pCurrState; //FSM �ּ�(���� ����ÿ� �ʿ��� �������ּ�)
		State state;	//ĳ������ FSM���� 
		CharacterState CharState; // ĳ������ ����(idle�����϶��� ���۰����� ���µ�)

		JumpState Jumpdir;	//ĳ������ ��������(Move)
		FLOAT Jump_Distance = 0; // �������� 
		Direction dir;	//ĳ������ ���� : ��,��

		Character_Type Type; // ��ü�� Ÿ�� ( player,���� ���)

		UINT Health_Point;//��ü�� ������
		BOOL Death; // ��ü�� ��������(0: ���� 1:����)
		RECT HitArea; // �浹üũ ���� ����

		BOOL Attack_Check; // ���ݿ� ����/���� ���� �Ǵ�
		FLOAT Attack_Time;//character�� ���� ��Ÿ��(���ݹ߻��ֱ�)



	public:
		virtual ~Character() {};

		virtual VOID Idle(const FLOAT& deltaTime) abstract;
		virtual VOID Move(const FLOAT& deltaTime) abstract;
		virtual VOID Attack(const FLOAT& deltaTime) abstract;
		virtual VOID Jump(const FLOAT& deltaTime) abstract;
		virtual VOID Hit(const FLOAT& deltaTime) abstract;
		//virtual BOOL IntersectRectRe(RECT& rect1, RECT& rect2) { return TRUE; };//ĳ���� �浹���� üũ �Լ� 
		
		virtual BOOL Initialize()abstract;
		virtual VOID Release()abstract;
		virtual VOID Update(const FLOAT& deltaTime)abstract;
		virtual VOID Draw()abstract;
		virtual VOID StateChange(FSMState*)abstract;

		//ĳ���� ��ü�� ������Ʈ(��)�� �ε������� üũ�ϴ� �ڵ�
		virtual BOOL Object_Move_Check();

		//ĳ���� ��ü�� ���ٴڿ� �ٴ��� ����� üũ�ϴ� �ڵ� 
		//��ȯ���� INDEX , ������ -1 ��ȯ
		virtual UINT Ground_Check();

		//�߷��ڵ�
		virtual VOID Gravity_Down(const FLOAT& deltaTime);
		

		//õ�� üũ(�����ÿ�)
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
		//��ĳ���� ���־ �����Լ��� ����ؼ� �ڽ��� �Լ��� �����Ϸ��� ���
		virtual VOID Player_Move_animation(const FLOAT& deltaTime) {};//�÷��̾� ���� �ִϸ��̼� ���� �ڵ� 

	};

}
#endif
