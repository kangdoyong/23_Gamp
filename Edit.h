#pragma once
#include "Scene.h"
#include "MapTools.h"

class Edit :
    public Scene
{
private:
	MapTools* mapTools;

public:
	// Scene��(��) ���� ��ӵ�
	void Initialize() override;
	void Update() override;
	void Render(HDC hdc) override;
	void Release() override;

	Edit();
	virtual ~Edit();
};

