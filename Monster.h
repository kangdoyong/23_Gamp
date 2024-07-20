#pragma once
#include "Object.h"
class Monster :
    public Object
{
public:
	// Object을(를) 통해 상속됨
	void Initialize() override;
	SceneType Update() override;
	void Render(HDC hdc) override;
	void Release() override;

	Monster();
	virtual ~Monster();
};

