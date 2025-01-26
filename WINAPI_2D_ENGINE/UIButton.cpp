//UIButton.cpp
#include "UIButton.h"
#include "ResourceManager.h"
#include "InputManager.h"

namespace ENGINE
{
	//EventListener = std::function<void()> : 함수포인터 define
	UIButton::UIButton() :
		clickListener(nullptr), pressedListener(nullptr),
		state(ButtonState::NONE),
		isUp(FALSE), isInteractable(TRUE),isDown(FALSE),
		normal(nullptr), pressed(nullptr), hover(nullptr), disable(nullptr)
	{
		uiType = UIType::BUTTON;
	}

	VOID UIButton::Initialize(CONST std::string& normal, CONST std::string& pressed,
		CONST std::string& hover, CONST std::string& disable, DrawType type)
	{
		UIImage::Initialize(normal, type);

		//UIImage에서 이니셜라이즈한 UIImage::image 변수를 UIButton객체에 전부 초기화
		//다 같은 비트맵을 가지고 있다는 뜻
		this->disable = this->hover = this->pressed = this->normal = image;
		//?????
		if (!pressed.empty()) this->pressed = ResourceMgr->GetBitmap(pressed);
		if (!hover.empty()) this->hover = ResourceMgr->GetBitmap(hover);
		if (!disable.empty()) this->disable = ResourceMgr->GetBitmap(disable);

	}

	VOID UIButton::SetListener(EventListener click, EventListener pressed)
	{
		clickListener = click;
		pressedListener = pressed;
	}



	VOID UIButton::Update()
	{
		//UIPanel이 존재하지 않으면 리턴(종료)
		if (!isEnable) return;

		//UIPanel의 자식클래스들 전부 업데이트(UIImage 업캐스팅)
		UIImage::Update();

		//버튼 동작을 하지 않았을때 , 버튼상태 및 이미지 초기화(disable)후 리턴
		if (!isInteractable)
		{
			state = ButtonState::NONE;
			if (disable) image = disable;
			return;
		}

		/*버튼 상태에 따른 상태 초기화 및 함수동작*/
		//왼쪽 마우스 클릭버튼이 
		//키에서 손을 땟을때(해당 프레임에서 누르지 않았을때)인경우 isUP은 true
		isUp = InputMgr->GetMouseButtonUp(VK_LBUTTON);
		if (PtInRect(&rect, InputMgr->GetMousePosition()))//충돌영역체크
		{
			switch (state)
			{
			case ButtonState::NONE: state = ButtonState::HOVER;
				// 왼쪽 마우스 버튼이 클릭된지 확인하고 true면 pressed상태로 초기화
				// false 조건 : 마우스 상태가 DOWN 아니면 마우스map에 추가(insert)후 false반환
			case ButtonState::HOVER: if (InputMgr->GetMouseButtonDown(VK_LBUTTON)) state = ButtonState::PRESSED; break;
				//왼쪽 마우스클릭을 손에서 땐 상태가 true 이고 clickListener 함수포인터가 존재하는경우
				//함수포인터 호출(clickListener)
			case ButtonState::PRESSED: if (isUp && clickListener) clickListener(); break;
			}
		}
		//누른상태가 아닌경우 NONE으로 초기화
		else if (ButtonState::PRESSED != state) state = ButtonState::NONE;

		/*버튼 상태에 따른 이미지 초기화*/
		switch (state)
		{
		case ButtonState::NONE: image = normal; break;
		case ButtonState::HOVER: image = hover; break;
		case ButtonState::PRESSED:
			image = pressed;
			//왼쪽 마우스클릭을 손에서 땐 상태가 true인경우 버튼상태를 NONE으로 초기화 후
			//함수포인터 호출(pressedListener)
			if (isUp) state = ButtonState::NONE; if (pressedListener) pressedListener();
			break;
		}
	}

}//namespace ENGINE




