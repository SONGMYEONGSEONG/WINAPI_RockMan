#include "UIPanel.h"

namespace ENGINE
{
	UIPanel::UIPanel() :
		isEnable(TRUE), pivotCenter(FALSE),
		position({0,0}), localPosition({0,0}),
		rect({ 0,0,0,0 }), size({ 0,0 }),
		parent(nullptr) { uiType = UIType::PANEL; }

	UIPanel::~UIPanel() { child.clear(); }

	VOID UIPanel::SetLocalPos(INT32 x, INT32 y)
	{
		position = localPosition = { x,y };
		if (parent) position = { x + parent->rect.left, y + parent->rect.top };
		SetRect(pivotCenter);
		//for-each 반복문
		for (UIPanel* ui : child) ui->RefreshPos();
	}

	VOID UIPanel::SetPosition(INT32 x, INT32 y, BOOL pivotCenter)
	{
		this->pivotCenter = pivotCenter;
		if (parent) SetLocalPos(x - parent->rect.left, y - parent->rect.top);
		else SetLocalPos(x, y);
	}

	VOID UIPanel::SetLocalPosition(INT32 x, INT32 y, BOOL pivotCenter)
	{
		this->pivotCenter = pivotCenter;
		SetLocalPos(x, y);
	}

	VOID UIPanel::Update()
	{
		if (!isEnable) return;
		for (UIPanel* ui : child) ui->Update();
	}

	VOID UIPanel::Draw()
	{
		if (!isEnable) return;
		for (UIPanel* ui : child) ui->Draw();
	}

	UIPanel* UIPanel::AddChildUI(UIPanel* ui)
	{
		if (!ui) return nullptr;

		child.push_back(ui);
		ui->SetParent(this);

		//중복 제거.
		std::sort(child.begin(), child.end());
		//벡터의 중복원소 제거 명령어 std::unique
		//unique로 중복원소를 제거후 ,중복을 제거하고 앞으로 원소를 땡겨온다 뒤는 남은 원소가 있음
		//unique함수의 반환값은 첫번째 원소의 주소를 리턴
		//erase로 남은 원소를 지움 
		child.erase(std::unique(child.begin(), child.end()), child.end());
	
		return ui;
	}

	VOID UIPanel::RemoveChildUI(UIPanel* ui)
	{
		if (!ui) return;

		std::vector<UIPanel*>::iterator iter = std::find(child.begin(), child.end(), ui);
		if (child.end() != iter)
		{
			child.erase(iter);
			(*iter)->SetParent(nullptr);
		}
	}

	VOID UIPanel::RefreshPos()
	{
		SetLocalPos(localPosition.x, localPosition.y);
	}

	UIPanel* UIPanel::GetChild(INT32 index)
	{
		if (0 > index || child.size() <= index) return nullptr;
		return child[index];
	}
}//namespace ENGINE