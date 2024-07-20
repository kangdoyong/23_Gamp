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
	// ��ư�� �簢�� ���� ������ ������
	auto rc = GetRect();

	// ���콺 ��ǥ�� �޾ƿ�
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	// Ư�� ����Ʈ(���콺 ��ġ)�� �簢�� ���� �ȿ� �ִ��� Ȯ��
	if (PtInRect(&rc, pt))
	{
		// ��ư ���� �ȿ� ���콺�� ��ġ�� ���
		isHover = 1;

		// ��ư�� ������ ���
		if (GetAsyncKeyState(VK_LBUTTON))
		{
			// �ش� ��ư ��ü�� ���ε��� �̺�Ʈ�� ȣ��
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
		hdc, // ��� �׸�����
		info.posX - info.sizeX / 2, // x
		info.posY - info.sizeY / 2, // y
		info.sizeX, info.sizeY, // size
		(*bmpMapAddress)[drawKey]->GetMemDC(), // �׸����� �ϴ� �ؽ��ĸ� ���� dc
		info.sizeX * isHover, 0, // �̹��� ������ �׸��� ������ ��ġ x, y
		info.sizeX, info.sizeY, // �̹��� ������ �󸶸�ŭ ������� �׸�����
		RGB(255, 255, 255) // � ���� ���� �����Ұ���
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
