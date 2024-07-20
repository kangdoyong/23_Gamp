#include "Menu.h"
#include "AbstractFactory.h"
#include "SceneMgr.h"
#include "Background.h"
#include "Button.h"


void Menu::Initialize()
{
	// �޴� ������ ����� �̹��� �ε�
	bmpMap["BackBuffer"] = (new Bitmap())->LoadBmp(L"Texture/BackBuffer.bmp");
	bmpMap["BG"] = (new Bitmap())->LoadBmp(L"Texture/Background.bmp");
	bmpMap["StartBtn"] = (new Bitmap())->LoadBmp(L"Texture/Button/Start.bmp");
	bmpMap["EditBtn"] = (new Bitmap())->LoadBmp(L"Texture/Button/Edit.bmp");
	bmpMap["ExitBtn"] = (new Bitmap())->LoadBmp(L"Texture/Button/Exit.bmp");

	// ��� ��ü ���� �� �׸��� Ű ����
	bg = new Background();
	bg->Initialize();
	bg->SetDrawKey("BG");

	// ��ư ��ü ����
	buttons.push_back(Button::CreateButton(200, 400, "StartBtn", OnClickStart));
	buttons.push_back(Button::CreateButton(400, 400, "EditBtn", OnClickEdit));
	buttons.push_back(Button::CreateButton(600, 400, "ExitBtn", OnClickExit));

	// ��� ��ü���� �ؽ��ĸ� �׸� ��, bmpMap�� ������ �� �ֵ��� �ּ� ����
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
	// ����ۿ� ��� �׸���
	bg->Render(bmpMap["BackBuffer"]->GetMemDC());

	// ����ۿ� ��ư �׸���
	for (auto i = buttons.begin(); i != buttons.end(); ++i)
		(*i)->Render(bmpMap["BackBuffer"]->GetMemDC());

	// ����ۿ� ��� ��ü�� �׸� ��, ���������� ���
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
