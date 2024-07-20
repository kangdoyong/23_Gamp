#pragma once
#include "Object.h"
class Button :
    public Object
{
private:
	// ���콺���� ���ͷ��� ���� 
	int isHover;
	SceneType (*OnClickEvent)();

public:
	// Object��(��) ���� ��ӵ�
	void Initialize() override;
	SceneType Update() override;
	void Render(HDC hdc) override;
	void Release() override;

	static Object* CreateButton(float x, float y, string drawKey, SceneType(*OnClickEvent)());

	Button();
	virtual ~Button();
};

