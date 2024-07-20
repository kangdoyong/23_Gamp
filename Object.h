#pragma once
#include "Include.h"

// ��� �ΰ��� ���͵��� ���̽��� �߻� Ŭ����
class Object abstract
{
protected:
	// �ؽ��ĸ� �׸� ��, ����� Ű ��
	string drawKey;
	INFO info;
	// ��ü�� �������� �־��� Ÿ���� �ε��� ���� ��Ƶ� �ʵ�
	Object* goalActor;
	int lastTileIdx = -1;
	float speed;
	float dirX;
	float dirY;
	// ���������� �ִϸ��̼��� ������ �ð��� ���� �ʵ�
	ULONGLONG lastAnimUpdateTime;
	// �ִϸ��̼� ����� �ʿ��� ������ �ʵ�
	FRAME frame;

	// ���� �� �� ��ü����, �ش� ���� �ʿ��� �ؽ��ĸ� map�� ��� ����
	// �� ��, �� ��ü(����)���� �ڱ� �ڽ� �Ǵ� �� �� �ʿ��� �ؽ��ĸ�
	// ����ϱ� ���ؼ�, �� ��ü�� ���� �ִ� map�� �����ؾ� ��
	// �� ��, �ش� map�� ������ ���ϰ� �ϱ� ����, map�� �ּҸ� ����
	// ���� �ʵ带 ����
	static map<string, Bitmap*>* bmpMapAddress;

public:
	INFO GetInfo() { return info; }
	void SetDrawKey(string key) { drawKey = key; }
	void SetPos(float x, float y) { info.posX = x; info.posY = y; }
	RECT GetRect();
	virtual void InitFrame() {};
	void UpdateFrame(); // ������ ���� �ִϸ��̼ǿ��� �������� �����ϴ� ���
	void UpdateTileActor();
	virtual void OnGoalEvent();

	static void SetBmpMap(map<string, Bitmap*>* address)
	{
		bmpMapAddress = address;
	}

public:
	virtual void Initialize() abstract;
	virtual SceneType Update() abstract;
	virtual void Render(HDC hdc) abstract;
	virtual void Release() abstract;

	// �Ķ���ͷ� ���� ��ġ�� �ش��ϴ� Ÿ�� �ε����� ��ȯ�ϴ� ���
	int GetTileIndex(float posX, float posY);
	// ��ã�� ���� ���
	void AStarStart(float startX, float startY, float goalX, float goalY);
	// ��ã�⸦ ���� ���� ��θ� ���� �̵��ϴ� ���
	void AStarMove();

	float GetDirection(float length);

	Object();
	virtual ~Object();
};

