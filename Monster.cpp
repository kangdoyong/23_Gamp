#include "Monster.h"
#include "TileBackground.h"

void Monster::Initialize()
{
	dirX = 0;
	dirY = 0;
	info.sizeX = 160;
	info.sizeY = 128;

	frame = FRAME(true, 0, 0, 7, 100);
	drawKey = "Monster";

	lastAnimUpdateTime = GetTickCount64();
}

SceneType Monster::Update()
{
	UpdateTileActor();
	UpdateFrame();

    return SCENE_NONE;
}

void Monster::Render(HDC hdc)
{
	GdiTransparentBlt(
		hdc,
		info.posX - info.sizeX / 2 + TileBackground::scrollX,
		info.posY - info.sizeY + TileBackground::scrollY,
		info.sizeX, info.sizeY,
		(*bmpMapAddress)[drawKey]->GetMemDC(),
		info.sizeX * frame.current,
		info.sizeY * frame.animType,
		info.sizeX, info.sizeY,
		RGB(255, 255, 255)
	);
}

void Monster::Release()
{
}

Monster::Monster()
{
}

Monster::~Monster()
{
}
