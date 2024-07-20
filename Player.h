#pragma once
#include "Object.h"
class Player :
    public Object
{
private:

	// �÷��̾��� ���� ����
	ActorState state;

private:
	void InputKey(); // Ű �Է�
	void UpdateMotion(); // �÷��̾� ���� ���� ���� ��ǰ� ���õ� ������ ����
	void UpdateDrawKey(); // �÷��̾��� ���� ���⿡ ���� ��ο� Ű�� ����
	void SetState(ActorState state); // �÷����� ���� ���� ���� ��� 
	virtual void InitFrame();
	virtual void OnGoalEvent();

public:
	// Object��(��) ���� ��ӵ�
	void Initialize() override;
	SceneType Update() override;
	void Render(HDC hdc) override;
	void Release() override;

	Player();
	virtual ~Player();
};

