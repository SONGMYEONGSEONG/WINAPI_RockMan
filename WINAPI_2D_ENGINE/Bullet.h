#include "GameMecro.h" 
#include "SceneManager.h" // debug�� 
#include "ScroolManager.h" //�÷��̾� �̵��� �Ѿ� �ӵ� ������ 
#include "ResourceManager.h" // bitmap �ڷ��� 
#include "Components/SpriteRenderer.h" //��������Ʈ bmp ������ ����Ͽ� ���� �ʿ���
#include <cmath>

#ifndef BULLET_H
#define BULLET_H


//�Ѿ��� �浹���� üũ�ϰ� �ؾߵ� 
//(���ݹ޴� ���(�Ѿ�RECT,�� RECT)�� �������� Ȯ���ؼ� ������ ������ѾߵǱ�����)
//������Ʈ Ǯ������ 3������ �������� , �� �ʿ��ϸ� �Ҵ�
namespace GAME
{
	enum
	{
		BULLET_MAX = 5,//ȭ�鿡 ������ �ִ� �Ѿ� ����
	};

	class Bullet : public ENGINE::GameObject
	{
	private:
		enum BulletPoint
		{
			Right_Pointx = 50,//�����ʺ��� ��ݽ� ���� ��ǥ��
			Left_Pointx = -10,//���ʺ��� ��ݽ� ���� ��ǥ��
			Gun_Pointy = -25, //ĳ���� �ѱ� ���� ��ǥ��
		};
		
		ENGINE::Vector2 Init_Pos; // �Ѿ� �ʱ� ��ġ 
		BOOL islife; //�Ѿ� ����

		INT BulletDir;
		RECT BulletRect; // �Ѿ� �浹����üũ 
		SIZE BulletSize; // bullet width,height 

		ENGINE::SpriteRenderer* renderer; //�׷���������Ʈ ��������Ʈ ������ Ȱ��
	public:
		VOID Initialize(FLOAT Init_Posx , FLOAT Init_Posy, Character_Type Type);
		VOID Release();
		BOOL Update(const FLOAT& deltaTime,FLOAT BulletSpeed ,RECT* CharacterRect);
		VOID Draw();

		VOID Set_Bulletlife(BOOL Bulletlife) { islife = Bulletlife; };
		VOID Reset_Bullet_HitArea() { BulletRect = { 0,0,0,0 };	}
		BOOL Get_Bulletlife() { return islife; };

		//�÷��̾� ���⿡ ���� �Ѿ� ��ǥ �� ���� ����
		VOID Set_BulletDir(Direction CharacterDir)
		{
			switch (CharacterDir)
			{
			case Direction::Right:
				BulletDir = 1;

				transform->position.x += Right_Pointx;
				break;
			case Direction::Left:
				BulletDir = -1;
				transform->position.x += Left_Pointx;
				break;
			}
		}
		VOID Set_BulletPositionX(FLOAT Point_X)
		{
			transform->position.x = Point_X;
		}
		VOID Set_BulletPositionY(FLOAT Point_Y)
		{
			transform->position.y = Point_Y + Gun_Pointy;
		}

		//Enemy -> Player ,Player->Enemy
		BOOL RectCheck(RECT* characterHitRect)
		{
			RECT result_Rect = {0,0,0,0};
			if (IntersectRect(&result_Rect, characterHitRect, &BulletRect))
			{
				islife = FALSE;
				transform->position = Init_Pos;
				BulletRect = { 0,0,0,0 };//
				return TRUE;
			}
			return FALSE;
		}

	};
}
#endif //!BULLET_H