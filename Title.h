#pragma once
#include "Scene.h"
class Title :
    public Scene
{
private:
	HWND video;

public:
	// Scene��(��) ���� ��ӵ�
	void Initialize() override;
	void Update() override;
	void Render(HDC hdc) override;
	void Release() override;

	Title();
	virtual ~Title();
};

