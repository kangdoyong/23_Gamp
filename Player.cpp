#include "Player.h"
#include "TileBackground.h"

void Player::Initialize()
{
	dirX = 0;
	dirY = 0;
	info.posX = WIN_SIZE_X / 2;
	info.posY = WIN_SIZE_Y / 2;
	info.sizeX = 200;
	info.sizeY = 200;

	// 초기 방향 설정 (어떤 방향의 텍스쳐를 그릴건지)
	drawKey = "PlayerDown";
	// 초기 애니메이션 설정 (대기 모션)
	frame = FRAME(true, 0, 0, 3, 100);
	// 초기 상태 설정
	state = STATE_IDLE;

	speed = 5.f;
	lastAnimUpdateTime = GetTickCount64();
}

SceneType Player::Update()
{
	InputKey();

	auto posX = info.posX;
	auto posY = info.posY;
	AStarMove();
	auto dispX = info.posX - posX;
	auto dispY = info.posY - posY;

	TileBackground::scrollX -= dispX;
	TileBackground::scrollY -= dispY;

	UpdateDrawKey();
	UpdateMotion();
	UpdateFrame();

    return SCENE_NONE;
}

void Player::Render(HDC hdc)
{
	GdiTransparentBlt(
		hdc,
		info.posX - info.sizeX / 2 + TileBackground::scrollX,
		info.posY - info.sizeY / 2 + TileBackground::scrollY,
		info.sizeX, info.sizeY,
		(*bmpMapAddress)[drawKey]->GetMemDC(),
		info.sizeX * frame.current,
		info.sizeY * frame.animType,
		info.sizeX, info.sizeY,
		RGB(0, 0, 0)
	);
}

void Player::Release()
{
}

void Player::InputKey()
{
	if (GetAsyncKeyState(VK_LBUTTON))
	{
		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		if (pt.x >= 0 && pt.x <= WIN_SIZE_X
			&& pt.y >= 0 && pt.y <= WIN_SIZE_Y)
		{
			float goalX = pt.x - TileBackground::scrollX;
			float goalY = pt.y - TileBackground::scrollY;

			AStarStart(info.posX, info.posY, goalX, goalY);
		}
	}
}

void Player::UpdateMotion()
{
	if (state != STATE_ATK)
		dirX != 0 || dirY != 0 ? SetState(STATE_WALK) : SetState(STATE_IDLE);

	switch (state)
	{
	case STATE_IDLE:
		frame.isLoop = true;
		frame.animType = 0;
		frame.last = 3;
		break;
	case STATE_WALK:
		frame.isLoop = true;
		frame.animType = 1;
		frame.last = 5;
		break;
	case STATE_ATK:
		frame.isLoop = false;
		frame.animType = 2;
		frame.last = 5;
		break;
	case STATE_HIT:
		break;
	case STATE_DEAD:
		break;
	}
}

void Player::UpdateDrawKey()
{
	if (dirX > 0)
	{
		drawKey = "PlayerRight";
	}
	else if (dirX < 0)
	{
		drawKey = "PlayerLeft";
	}
	else
	{
		if (dirY > 0)
			drawKey = "PlayerDown";
		else if (dirY < 0)
			drawKey = "PlayerUp";
	}
}

void Player::SetState(ActorState state)
{
	if (this->state == state)
		return;

	frame.current = 0;
	this->state = state;
}

void Player::InitFrame()
{
	SetState(STATE_IDLE);
}

void Player::OnGoalEvent()
{
	Object::OnGoalEvent();
	SetState(STATE_ATK);
}

Player::Player()
{
}

Player::~Player()
{
}
