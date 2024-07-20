#include "TileBackground.h"

float TileBackground::scrollX = 0;
float TileBackground::scrollY = 0;

void TileBackground::Initialize()
{
	// Ÿ�� ������ �ҷ��� ��,
	// Ÿ�� ���Ϳ� ����
	HANDLE handle;
	DWORD byte;

	handle = CreateFile(L"Data/TileMap.dat", GENERIC_READ, NULL, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	while (true)
	{
		TILE* tile = new TILE();

		ReadFile(handle, tile, sizeof(TILE), &byte, NULL);

		// �� �̻� ���� �����Ͱ� ���� ���
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
			// ������ Ÿ�� ���ҿ� ���������� �����ϱ� ���� 
			// Ÿ�� �ε����� ����
			int idx = i * TILE_CNT_X + j;

			BitBlt(hdc, // ����ۿ� �׸���
				(tiles[idx]->posX - TILE_SIZE_X / 2) + scrollX, // x
				(tiles[idx]->posY - TILE_SIZE_Y / 2) + scrollY, // y
				TILE_SIZE_X, TILE_SIZE_Y, // size
				(*bmpMapAddress)[drawKey]->GetMemDC(), // �׸� bmp�� ������ �ִ� ���� dc
				tiles[idx]->drawId * TILE_SIZE_X, 0,// �̹��� ������ �׸��� ������ x, y ��ġ
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
