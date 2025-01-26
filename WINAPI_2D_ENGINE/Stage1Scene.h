//Player�� �����ӿ� ���� ȭ���� ���,������Ʈ�� ���� �̵��ϰ� �ϴ� Ŭ����
//1.��ũ�ѸŴ����� ���ҽ��Ŵ������� ������ ���ȭ���� w,h�� �˾ƾߵȴ�.
//2.���ȭ���� ���� �����Ѱ�� �ٽ� ������ ����� �׸���.
//3.��ũ�ѸŴ����� Stage_N_Scnen������ ���ȴ�. 
//4.��ũ�ѸŴ����� Player��ǥ�� �������� ��ũ�ѵǸ�, ��ũ�� ��ǥ�� left,botoom�� ���������Ѵ�.

#include <array>
#include "EngineMecro.h"
#include "UIManager.h"

//Stage1Scene �ʼ� ���
#include "ScroolManager.h"
#include "BackGround.h" // ��� ��� 
#include "Player.h"
#include "ObjectManager.h"
#include "EnemyManager.h"
#include "UIGameManager.h"


#ifndef STAGE_1_SCENE_H
#define STAGE_1_SCENE_H
namespace GAME
{
	class Stage1Scene : public ENGINE::Scene
	{
	private:
		BackGround* pBackGround = nullptr;
		Player* pPlayer = nullptr;


	public:
		// Scene��(��) ���� ��ӵ�
		virtual VOID Initialize() override;
		virtual VOID Release() override;
		virtual VOID Update(const FLOAT& deltaTime) override;
		virtual VOID Draw() override;
	};
}
#endif //!STAGE_1_SCENE_H
