//UIManager.h
//해당 씬에서 사용할 UI를 가지고, 사용되는 모든 UI를 갱신 및 그리기를 처리하여 준다.
#include "Singleton.h"
#include "UIButton.h" //#include "UIImage.h" (부모클래스) 
#include "UILabel.h" //#include "UIPanel.h"(부모 클래스)
#ifndef UI_MANAGER_H
#define UI_MANAGER_H
namespace ENGINE
{
	class UIManager : public Singleton<UIManager>
	{
	private:
		std::map<std::string, UIPanel*> map_UI;
		std::vector<UIPanel*> child_UI;

		UIManager() {}
	public:
		~UIManager();

		VOID Initialize();
		VOID Clear();
		VOID Update();
		VOID Draw();

		template<typename T> T* AddUI(std::string name, UIPanel* parent = nullptr);
		UIPanel* GetUI(std::string name);
		BOOL Remove(std::string name);

		friend Singleton;
	}; //class UIManager

	template<typename T>
	inline T* UIManager::AddUI(std::string name, UIPanel* parent)
	{
		if (name.empty()) return nullptr; // 빈 문자열을 이름으로 지정할 수 없게 한다.

		auto iter = map_UI.find(name); //이미 같은 이름의 UI가 있을경우 추가 실패.
		if (map_UI.end() != iter) return nullptr; // 이미 있는 UI의 타입이 다를 수 있기에 null반환

		T* ui = new T;
		//인자값으로 부모클래스 주소를 가져왔으면 UIPanel의 자식vector에 저장
		if (parent) parent->AddChildUI(ui);

		map_UI.insert(std::make_pair(name, ui));

		return ui;
	}
	#define UIMgr UIManager::GetInstance()
}
#endif // !UI_MANAGER_H


