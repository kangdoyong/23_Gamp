#include "TileBackground.h"

float TileBackground::scrollX = 0;
float TileBackground::scrollY = 0;

void TileBackground::Initialize()
{
	// 타일 정보를 불러온 후,
	// 타일 벡터에 담음
	HANDLE handle;
	DWORD byte;

	handle = CreateFile(L"Data/TileMap.dat", GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	while (true)
	{
		TILE* tile = new TILE();

		ReadFile(handle, tile, sizeof(TILE), &byte, NULL);

		// 더 이상 읽을 데이터가 없을 경우
		if (byte == 0)
		{
			SafeDelete(tile);
			break;
		}

		tiles.push_back(tile);
	}

	CloseHandle(handle);

	drawKey = "Tile";
}

SceneType TileBackground::Update()
{
	return SCENE_NONE;
}

void TileBackground::Render(HDC hdc)
{
	for (int i = 0; i < TILE_CNT_Y; ++i)
	{
		for (int j = 0; j < TILE_CNT_X; ++j)
		{
			// 각각의 타일 원소에 순차적으로 접근하기 위해 
			// 타일 인덱스를 연산
			int idx = i * TILE_CNT_X + j;

			BitBlt(hdc, // 백버퍼에 그리게
				(tiles[idx]->posX - TILE_SIZE_X / 2) + scrollX, // x
				(tiles[idx]->posY - TILE_SIZE_Y / 2) + scrollY, // y
				TILE_SIZE_X, TILE_SIZE_Y, // size
				(*bmpMapAddress)[drawKey]->GetMemDC(), // 그릴 bmp를 가지고 있는 원본 dc
				tiles[idx]->drawId * TILE_SIZE_X, 0,// 이미지 내에서 그리기 시작할 x, y 위치
				SRCCOPY);
		}
	}
}

void TileBackground::Release()
{
	for (int i = 0; i < tiles.size(); ++i)
		SafeDelete(tiles[i]);
	tiles.clear();
}

TileBackground::TileBackground()
{
}

TileBackground::~TileBackground()
{
	Release();
}
