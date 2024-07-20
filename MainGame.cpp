#include "MainGame.h"
#include "SceneMgr.h"

void MainGame::Initialize()
{
	hdc = GetDC(g_hWnd);

	// ÃÊ±â ¾À ¼³Á¤
	SceneMgr::GetInstance()->SetScene(SCENE_TITLE);
}

void MainGame::Update()
{
	SceneMgr::GetInstance()->Update();
}

void MainGame::Render()
{
	SceneMgr::GetInstance()->Render(hdc);
}

void MainGame::Release()
{
	SceneMgr::Destroy();
	ReleaseDC(g_hWnd, hdc);
}

MainGame::MainGame()
{
}

MainGame::~MainGame()
{
	Release();
}
