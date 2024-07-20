#include "Button.h"
#include "AbstractFactory.h"

void Button::Initialize()
{
	isHover = 0;
	info.sizeX = 150;
	info.sizeY = 150;
}

SceneType Button::Update()
{
	// 버튼의 사각형 영역 정보를 가져옴
	auto rc = GetRect();

	// 마우스 좌표를 받아옴
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	// 특정 포인트(마우스 위치)가 사각형 영역 안에 있는지 확인
	if (PtInRect(&rc, pt))
	{
		// 버튼 영역 안에 마우스가 위치한 경우
		isHover = 1;

		// 버튼을 눌렀을 경우
		if (GetAsyncKeyState(VK_LBUTTON))
		{
			// 해당 버튼 객체에 바인딩된 이벤트를 호출
			return OnClickEvent();
		}
	}
	else
	{
		isHover = 0;
	}

	return SCENE_NONE;
}

void Button::Render(HDC hdc)
{
	GdiTransparentBlt(
		hdc, // 어디에 그릴건지
		info.posX - info.sizeX / 2, // x
		info.posY - info.sizeY / 2, // y
		info.sizeX, info.sizeY, // size
		(*bmpMapAddress)[drawKey]->GetMemDC(), // 그리고자 하는 텍스쳐를 갖는 dc
		info.sizeX * isHover, 0, // 이미지 내에서 그리기 시작할 위치 x, y
		info.sizeX, info.sizeY, // 이미지 내에서 얼마만큼 사이즈로 그릴건지
		RGB(255, 255, 255) // 어떤 색상 값을 제외할건지
	);
}

void Button::Release()
{
}


Object* Button::CreateButton(float x, float y, string drawKey, SceneType (*OnClickEvent)())
{
	Object* button = AbstractFactory<Button>::CreateObject(x, y);
	button->SetDrawKey(drawKey);
	((Button*)button)->OnClickEvent = OnClickEvent;

	return button;
}

Button::Button()
{
}

Button::~Button()
{
}
