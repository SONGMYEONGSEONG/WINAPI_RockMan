//UIButton.h
//MouswButtonPressed,click Event가 발생하면 Callback으로 Handler를 호출하여 
//해당 이벤트를 실행한다.
#include "UIImage.h"
#ifndef UI_BUTTON_H
#define UI_BUTTON_H
namespace ENGINE
{
	class UIButton : public UIImage
	{
		enum class ButtonState {NONE,HOVER,PRESSED};
	protected:
		EventListener clickListener, pressedListener;
		ButtonState state;
		BOOL isUp, isInteractable,isDown;
		Bitmap* normal, * pressed, * hover, * disable;

	public:
		UIButton();

		VOID Initialize(CONST std::string& normal, CONST std::string& pressed = "",
			CONST std::string& hover ="",CONST std::string& disable = "",
			DrawType type = DrawType::Normal);
		VOID SetListener(EventListener click, EventListener Pressed = nullptr);
		VOID SetInteracterble(BOOL interactable) { isInteractable = interactable; }
		BOOL Isinteracterable() CONST { return isInteractable; }
		virtual VOID Update() override;
	};
}
#endif //!UI_BUTTON_H