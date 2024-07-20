#pragma once
#include "Object.h"
class Background :
    public Object
{
public:
	// Object��(��) ���� ��ӵ�
	void Initialize() override;
	SceneType Update() override;
	void Render(HDC hdc) override;
	void Release() override;

	Background();
	virtual ~Background();
};

