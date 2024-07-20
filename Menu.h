#pragma once
#include "Scene.h"

class Object;
class Menu :
    public Scene
{
private:
	Object* bg;
	list<Object*> buttons;

private:
	static SceneType OnClickStart() { return SCENE_INGAME; }
	static SceneType OnClickEdit() { return SCENE_EDIT; }
	static SceneType OnClickExit() { return SCENE_NONE; }

public:
	// Scene을(를) 통해 상속됨
	void Initialize() override;
	void Update() override;
	void Render(HDC hdc) override;
	void Release() override;

	Menu();
	virtual ~Menu();
};

