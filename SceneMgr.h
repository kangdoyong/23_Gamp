#pragma once
#include "Include.h"

class Scene;
class SceneMgr
{
private:
	// ���� �� ��ü�� ���� �ʵ�
	Scene* currentScene;

public:
	Scene* GetScene() { return currentScene; }

public:
	// �Ķ���ͷ� ���� �� Ÿ������ ���� ���� �����ϴ� ���
	void SetScene(SceneType type);
	void Update(); // ���� �� ������Ʈ
	void Render(HDC hdc); // ���� �� �׸���
	void Release(); // �� �Ŵ��� �ı� ��, �޸� ����

#pragma region �̱��� ó��
private:
	// �� �Ŵ��� �ν��Ͻ��� ���� ���� �ʵ�
	static SceneMgr* instance;

public:
	static SceneMgr* GetInstance()
	{
		// �ν��Ͻ��� �������� �ʴ´ٸ�
		if (instance == nullptr)
			instance = new SceneMgr(); // �ν��Ͻ� ����

		// ��������� �̹� �����Ѵٸ� �ٷ� ��ȯ,
		// ���ٸ� ���� �����ؼ� ��ȯ
		return instance;	}

	static void Destroy() { SafeDelete(instance); }
	~SceneMgr();

private:
	SceneMgr();
#pragma endregion
};

