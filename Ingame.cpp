#include "Ingame.h"
#include "AbstractFactory.h"
#include "TileBackground.h"
#include "Player.h"
#include "Monster.h"

void Ingame::Initialize()
{
	bmpMap["BackBuffer"] = (new Bitmap())->LoadBmp(L"Texture/BackBuffer.bmp");
	bmpMap["Tile"] = (new Bitmap())->LoadBmp(L"Texture/Tile.bmp");

	bmpMap["PlayerDown"] = (new Bitmap())->LoadBmp(L"Texture/Player/Player_DOWN.bmp");
	bmpMap["PlayerUp"] = (new Bitmap())->LoadBmp(L"Texture/Player/Player_UP.bmp");
	bmpMap["PlayerLeft"] = (new Bitmap())->LoadBmp(L"Texture/Player/Player_LEFT.bmp");
	bmpMap["PlayerRight"] = (new Bitmap())->LoadBmp(L"Texture/Player/Player_RIGHT.bmp");
	
	bmpMap["Monster"] = (new Bitmap())->LoadBmp(L"Texture/Necromancer.bmp");

	bg = AbstractFactory<TileBackground>::CreateObject();

	actors[ACTOR_PLAYER].push_back(AbstractFactory<Player>::CreateObject());
	
	auto tiles = GetTiles();
	for (int i = 0; i < 10; ++i)
	{
		int randTileIdx = rand() % (TILE_CNT_X * TILE_CNT_Y);

		while ((*tiles)[randTileIdx]->isColl)
		{
			randTileIdx = rand() % (TILE_CNT_X * TILE_CNT_Y);
		}

		auto posX = (*tiles)[randTileIdx]->posX;
		auto posY = (*tiles)[randTileIdx]->posY;

		actors[ACTOR_MONSTER].push_back(AbstractFactory<Monster>::CreateObject(posX, posY));
	}

	Object::SetBmpMap(&bmpMap);
}

void Ingame::Update()
{
	// 액터의 종류만큼 반복
	for (int i = 0; i < ACTOR_END; ++i)
	{
		// 각 액터의 리스트를 순회
		for (auto j = actors[i].begin(); j != actors[i].end(); ++j)
		{
			(*j)->Update();
		}
	}
}

void Ingame::Render(HDC hdc)
{
	Rectangle(bmpMap["BackBuffer"]->GetMemDC(), 0, 0, WIN_SIZE_X, WIN_SIZE_Y);
	// 백버퍼에 타일 그리기
	bg->Render(bmpMap["BackBuffer"]->GetMemDC());

	// 액터의 종류만큼 반복
	for (int i = 0; i < ACTOR_END; ++i)
	{
		// 각 액터의 리스트를 순회
		for (auto j = actors[i].begin(); j != actors[i].end(); ++j)
		{
			(*j)->Render(bmpMap["BackBuffer"]->GetMemDC());
		}
	}

	// 백버퍼에 모든 객체를 그린 후, 최종적으로 출력
	BitBlt(hdc, 0, 0, WIN_SIZE_X, WIN_SIZE_Y,
		bmpMap["BackBuffer"]->GetMemDC(), 0, 0, SRCCOPY);
}

void Ingame::Release()
{
	SafeDelete(bg);

	// 액터의 종류만큼 반복
	for (int i = 0; i < ACTOR_END; ++i)
	{
		// 각 액터의 리스트를 순회
		for (auto j = actors[i].begin(); j != actors[i].end(); ++j)
		{
			SafeDelete(*j);
		}
		actors[i].clear();
	}
}

Ingame::Ingame()
{
}

Ingame::~Ingame()
{
	Release();
}
