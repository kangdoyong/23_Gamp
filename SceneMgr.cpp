#include "SceneMgr.h"
#include "Title.h"
#include "Menu.h"
#include "Ingame.h"
#include "Edit.h"

// ���� �ʵ� �ʱ�ȭ
SceneMgr* SceneMgr::instance = nullptr;

SceneMgr::SceneMgr()
	: currentScene(nullptr)
{
}

void SceneMgr::SetScene(SceneType type)
{
	// ���� ���� �����Ѵٸ�, �޸� ����
	SafeDelete(currentScene);

	// �� Ÿ�Կ� ���� ���ο� �� ��ü �Ҵ�
	switch (type)
	{
	case SCENE_TITLE:
		currentScene = new Title();
		break;
	case SCENE_MENU:
		currentScene = new Menu();
		break;
	case SCENE_EDIT:
		currentScene = new Edit();
		break;
	case SCENE_INGAME:
		currentScene = new Ingame();
		break;
	}

	// ���� ������ �� ��ü �ʱ�ȭ
	currentScene->Initialize();
}

void SceneMgr::Update()
{
	currentScene->Update();
}

void SceneMgr::Render(HDC hdc)
{
	currentScene->Render(hdc);
}

void SceneMgr::Release()
{
	SafeDelete(currentScene);
}

SceneMgr::~SceneMgr()
{
	Release();
}
