//UIButton.cpp
#include "UIButton.h"
#include "ResourceManager.h"
#include "InputManager.h"

namespace ENGINE
{
	//EventListener = std::function<void()> : �Լ������� define
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

		//UIImage���� �̴ϼȶ������� UIImage::image ������ UIButton��ü�� ���� �ʱ�ȭ
		//�� ���� ��Ʈ���� ������ �ִٴ� ��
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
		//UIPanel�� �������� ������ ����(����)
		if (!isEnable) return;

		//UIPanel�� �ڽ�Ŭ������ ���� ������Ʈ(UIImage ��ĳ����)
		UIImage::Update();

		//��ư ������ ���� �ʾ����� , ��ư���� �� �̹��� �ʱ�ȭ(disable)�� ����
		if (!isInteractable)
		{
			state = ButtonState::NONE;
			if (disable) image = disable;
			return;
		}

		/*��ư ���¿� ���� ���� �ʱ�ȭ �� �Լ�����*/
		//���� ���콺 Ŭ����ư�� 
		//Ű���� ���� ������(�ش� �����ӿ��� ������ �ʾ�����)�ΰ�� isUP�� true
		isUp = InputMgr->GetMouseButtonUp(VK_LBUTTON);
		if (PtInRect(&rect, InputMgr->GetMousePosition()))//�浹����üũ
		{
			switch (state)
			{
			case ButtonState::NONE: state = ButtonState::HOVER;
				// ���� ���콺 ��ư�� Ŭ������ Ȯ���ϰ� true�� pressed���·� �ʱ�ȭ
				// false ���� : ���콺 ���°� DOWN �ƴϸ� ���콺map�� �߰�(insert)�� false��ȯ
			case ButtonState::HOVER: if (InputMgr->GetMouseButtonDown(VK_LBUTTON)) state = ButtonState::PRESSED; break;
				//���� ���콺Ŭ���� �տ��� �� ���°� true �̰� clickListener �Լ������Ͱ� �����ϴ°��
				//�Լ������� ȣ��(clickListener)
			case ButtonState::PRESSED: if (isUp && clickListener) clickListener(); break;
			}
		}
		//�������°� �ƴѰ�� NONE���� �ʱ�ȭ
		else if (ButtonState::PRESSED != state) state = ButtonState::NONE;

		/*��ư ���¿� ���� �̹��� �ʱ�ȭ*/
		switch (state)
		{
		case ButtonState::NONE: image = normal; break;
		case ButtonState::HOVER: image = hover; break;
		case ButtonState::PRESSED:
			image = pressed;
			//���� ���콺Ŭ���� �տ��� �� ���°� true�ΰ�� ��ư���¸� NONE���� �ʱ�ȭ ��
			//�Լ������� ȣ��(pressedListener)
			if (isUp) state = ButtonState::NONE; if (pressedListener) pressedListener();
			break;
		}
	}

}//namespace ENGINE




