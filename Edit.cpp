#include "Edit.h"

void Edit::Initialize()
{
	bmpMap["BackBuffer"] = (new Bitmap())->LoadBmp(L"Texture/BackBuffer.bmp");
	bmpMap["Tile"] = (new Bitmap())->LoadBmp(L"Texture/Tile.bmp");

	mapTools = new MapTools();
	mapTools->Initialize();

	Object::SetBmpMap(&bmpMap);
}

void Edit::Update()
{
	mapTools->Update();
}

void Edit::Render(HDC hdc)
{
	mapTools->Render(bmpMap["BackBuffer"]->GetMemDC());

	BitBlt(hdc, 0, 0, WIN_SIZE_X, WIN_SIZE_Y,
		bmpMap["BackBuffer"]->GetMemDC(), 0, 0, SRCCOPY);
}

void Edit::Release()
{
	SafeDelete(mapTools);
}

Edit::Edit()
{
}

Edit::~Edit()
{
	Release();
}
