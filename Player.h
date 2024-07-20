#pragma once
#include "Object.h"
class Player :
    public Object
{
private:

	// 플레이어의 현재 상태
	ActorState state;

private:
	void InputKey(); // 키 입력
	void UpdateMotion(); // 플레이어 상태 값에 따라 모션과 관련된 데이터 갱신
	void UpdateDrawKey(); // 플레이어의 현재 방향에 따라 드로우 키를 갱신
	void SetState(ActorState state); // 플레이의 현재 상태 변경 기능 
	virtual void InitFrame();
	virtual void OnGoalEvent();

public:
	// Object을(를) 통해 상속됨
	void Initialize() override;
	SceneType Update() override;
	void Render(HDC hdc) override;
	void Release() override;

	Player();
	virtual ~Player();
};

