#pragma once
#include "Scene.h"
class Title :
    public Scene
{
private:
	HWND video;

public:
	// Scene을(를) 통해 상속됨
	void Initialize() override;
	void Update() override;
	void Render(HDC hdc) override;
	void Release() override;

	Title();
	virtual ~Title();
};

