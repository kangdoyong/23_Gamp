#include "Background.h"

void Background::Initialize()
{
	drawKey = "";
}

SceneType Background::Update()
{
	return SCENE_NONE;
}

void Background::Render(HDC hdc)
{
	if (drawKey == "")
		return;

	BitBlt(hdc, 0, 0, WIN_SIZE_X, WIN_SIZE_Y,
		(*bmpMapAddress)[drawKey]->GetMemDC(),
		0, 0, SRCCOPY);
}

void Background::Release()
{
}

Background::Background()
{
}

Background::~Background()
{
}
