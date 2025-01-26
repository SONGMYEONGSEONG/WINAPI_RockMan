//UIManager.cpp
#include "UIManager.h"
namespace ENGINE
{
	UIManager::~UIManager() { Clear(); }

	VOID UIManager::Initialize() { Clear(); }

	VOID UIManager::Clear()
	{
		for (std::pair<std::string, UIPanel*> pair : map_UI) DEL(pair.second);
		map_UI.clear();
	}

	VOID UIManager::Update()
	{
		//부모가 있을 경우 부모 쪽에서 Update() 함수를 호출 하고 있다.
		//UIpanel은 부모가 없다.
		for (std::pair<std::string, UIPanel*> pair : map_UI)
			if (!pair.second->GetParent()) pair.second->Update();
	}

	VOID UIManager::Draw()
	{
		//부모가 있을 경우 부모 쪽에서 Draw() 함수를 호출 하고 있다.
		//UIpanel은 부모가 없다.
		for (std::pair<std::string, UIPanel*> pair : map_UI)
			if (!pair.second->GetParent()) pair.second->Draw();
	}

	//이름을 인자값으로 받아서 검색한후 있으면 map_UI의 UIPaner*(second)주소를 반환한다.
	UIPanel* UIManager::GetUI(std::string name)
	{
		auto iter = map_UI.find(name);
		if (map_UI.end() != iter) return iter->second;

		return nullptr;
	}

	//이름을 인자값으로 받아서 검색한후 있으면 map_UI에서 제외 한 후 할당해지한다.
	BOOL UIManager::Remove(std::string name)
	{
		auto ui = GetUI(name);
		if (nullptr != ui)
		{
			map_UI.erase(name);
			DEL(ui);

			return TRUE;
		}

		return FALSE;
	}
}//namespace ENGINE