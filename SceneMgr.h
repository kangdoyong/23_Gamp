#pragma once
#include "Include.h"

class Scene;
class SceneMgr
{
private:
	// 현재 씬 객체를 담을 필드
	Scene* currentScene;

public:
	Scene* GetScene() { return currentScene; }

public:
	// 파라미터로 받은 씬 타입으로 현재 씬을 변경하는 기능
	void SetScene(SceneType type);
	void Update(); // 현재 씬 업데이트
	void Render(HDC hdc); // 현재 씬 그리기
	void Release(); // 씬 매니저 파괴 시, 메모리 해제

#pragma region 싱글톤 처리
private:
	// 씬 매니저 인스턴스를 담을 정적 필드
	static SceneMgr* instance;

public:
	static SceneMgr* GetInstance()
	{
		// 인스턴스가 존재하지 않는다면
		if (instance == nullptr)
			instance = new SceneMgr(); // 인스턴스 생성

		// 결과적으로 이미 존재한다면 바로 반환,
		// 없다면 새로 생성해서 반환
		return instance;	}

	static void Destroy() { SafeDelete(instance); }
	~SceneMgr();

private:
	SceneMgr();
#pragma endregion
};

