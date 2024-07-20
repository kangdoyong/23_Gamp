#include "Menu.h"
#include "AbstractFactory.h"
#include "SceneMgr.h"
#include "Background.h"
#include "Button.h"


void Menu::Initialize()
{
	// 메뉴 씬에서 사용할 이미지 로드
	bmpMap["BackBuffer"] = (new Bitmap())->LoadBmp(L"Texture/BackBuffer.bmp");
	bmpMap["BG"] = (new Bitmap())->LoadBmp(L"Texture/Background.bmp");
	bmpMap["StartBtn"] = (new Bitmap())->LoadBmp(L"Texture/Button/Start.bmp");
	bmpMap["EditBtn"] = (new Bitmap())->LoadBmp(L"Texture/Button/Edit.bmp");
	bmpMap["ExitBtn"] = (new Bitmap())->LoadBmp(L"Texture/Button/Exit.bmp");

	// 배경 객체 생성 및 그리기 키 설정
	bg = new Background();
	bg->Initialize();
	bg->SetDrawKey("BG");

	// 버튼 객체 생성
	buttons.push_back(Button::CreateButton(200, 400, "StartBtn", OnClickStart));
	buttons.push_back(Button::CreateButton(400, 400, "EditBtn", OnClickEdit));
	buttons.push_back(Button::CreateButton(600, 400, "ExitBtn", OnClickExit));

	// 모든 객체들이 텍스쳐를 그릴 때, bmpMap에 접근할 수 있도록 주소 전달
	Object::SetBmpMap(&bmpMap);
}

void Menu::Update()
{
	for (auto i = buttons.begin(); i != buttons.end(); ++i)
	{
		auto t = (*i)->Update();

		if (t > SCENE_NONE)
		{
			SceneMgr::GetInstance()->SetScene(t);
			return;
		}
	}
}

void Menu::Render(HDC hdc)
{
	// 백버퍼에 배경 그리기
	bg->Render(bmpMap["BackBuffer"]->GetMemDC());

	// 백버퍼에 버튼 그리기
	for (auto i = buttons.begin(); i != buttons.end(); ++i)
		(*i)->Render(bmpMap["BackBuffer"]->GetMemDC());

	// 백버퍼에 모든 객체를 그린 후, 최종적으로 출력
	BitBlt(hdc, 0, 0, WIN_SIZE_X, WIN_SIZE_Y,
		bmpMap["BackBuffer"]->GetMemDC(), 0, 0, SRCCOPY);
}

void Menu::Release()
{
	SafeDelete(bg);

	for (auto i = buttons.begin(); i != buttons.end(); ++i)
		SafeDelete(*i);
	buttons.clear();
}

Menu::Menu()
{
}

Menu::~Menu()
{
	Release();
}
