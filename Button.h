#pragma once
#include "Object.h"
class Button :
    public Object
{
private:
	// 마우스와의 인터렉션 여부 
	int isHover;
	SceneType (*OnClickEvent)();

public:
	// Object을(를) 통해 상속됨
	void Initialize() override;
	SceneType Update() override;
	void Render(HDC hdc) override;
	void Release() override;

	static Object* CreateButton(float x, float y, string drawKey, SceneType(*OnClickEvent)());

	Button();
	virtual ~Button();
};

