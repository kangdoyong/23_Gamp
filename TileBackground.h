#pragma once
#include "Object.h"
class TileBackground :
    public Object
{
private:
	vector<TILE*> tiles;

	// ȭ�� ��ũ�� ��, �ΰ��� �� ��� ��ü�� �׸� ��
	// �ش� ��ũ�� ���� �����Ͽ� �׷��� ��
	// -> ��� ��ü�� Ÿ�� bg ��ü�� ��ũ�� ���� �����ؾ� ��
	// �� ������, Ÿ�� ��ü ������ �Ѱ� �ޱ� �����ϹǷ�
	// �ϴ� ����ϱ� ���ϰ� ���� �ʵ�� ����
	// ���� ����� �ƴ�
public:
	static float scrollX, scrollY;

public:
	vector<TILE*>* GetTiles() { return &tiles; }

public:
	// Object��(��) ���� ��ӵ�
	void Initialize() override;
	SceneType Update() override;
	void Render(HDC hdc) override;
	void Release() override;

	TileBackground();
	virtual ~TileBackground();
};

