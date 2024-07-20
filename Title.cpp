#include "Title.h"
#include "SceneMgr.h"
#pragma comment (lib, "vfw32.lib")
#include <Vfw.h>

void Title::Initialize()
{
	// 영상을 재생시킬 창 생성
	video = MCIWndCreate(g_hWnd, NULL, MCIWNDF_NOPLAYBAR | WS_VISIBLE | WS_CHILD,
		L"Video/Logo.wmv");

	// 창 위치 및 크기 설정
	MoveWindow(video, 0, 0, WIN_SIZE_X, WIN_SIZE_Y, FALSE);
	// 영상 재생
	MCIWndPlay(video);
}

void Title::Update()
{
	if (GetAsyncKeyState(VK_RETURN))
		SceneMgr::GetInstance()->SetScene(SCENE_MENU);
}

void Title::Render(HDC hdc)
{
}

void Title::Release()
{
	MCIWndClose(video);
}

Title::Title()
{
}

Title::~Title()
{
	Release();
}
