//게임 엔진 UI TOOL 
//특별한 기능이 없는 UI Tool Base, 계층구조 등을 만들 때 사용가능 
#include "EngineMecro.h"
#ifndef UI_PANEL_H
#define UI_PANEL_H

namespace ENGINE
{ 
	enum class UIType { PANEL,IMAGE,BUTTON,LABEL};
	
	//부모클래스
	class UIPanel
	{
	protected:
		BOOL isEnable, pivotCenter;
		POINT position, localPosition;
		RECT rect;
		SIZE size;
		UIPanel* parent;
		std::vector<UIPanel*> child;
		UIType uiType;

	public:
		UIPanel();
		virtual ~UIPanel();

	private:
		VOID SetParent(UIPanel* parent) { this->parent = parent; }
		VOID SetLocalPos(INT32 x, INT32 y);
	protected:
		virtual VOID SetRect(BOOL pivotCenter)
		{
			rect = { localPosition.x, localPosition.y,localPosition.x, localPosition.y };
		}
	public:
		virtual VOID SetPosition(INT32 x, INT32 y, BOOL pivotCenter = FALSE); //월드(스크린)좌표 상의 위치
		virtual VOID SetLocalPosition(INT32 x, INT32 y, BOOL pivotCenter = FALSE); //부모 UI를 중점으로 한 위치
		virtual VOID Update();
		virtual VOID Draw();
		//자식으로 추가되는 ui는 알아서 메모리를 헤제한다.
		UIPanel* AddChildUI(UIPanel* ui); //계층구조, 자식 UI추가.
		VOID RemoveChildUI(UIPanel* ui); //자식에서 제외하고 메모리 해제를 하지않는다.
		VOID RefreshPos(); //변경된 자신의 위치를 중심으로 자식 UI의 위치를 재배치.
		VOID SetEnable(BOOL enable) { isEnable = enable; }
		BOOL Enable() CONST { return isEnable; }
		UINT32 GetChildCount() CONST { return child.size(); }
		UIPanel* GetChild(INT32 index);
		UIPanel* GetParent() CONST { return parent; }
		POINT GetPosition() CONST { return position; }
		POINT GetLocalPosition() CONST { return localPosition; }
		UIType GetUIType() CONST  { return uiType; }
		SIZE GetSize() CONST { return size; }
	}; // clase UIPanel
} //namespace ENGINE
#endif //!UI_PANEL_H
