#pragma once
#include "Object.h"
class TileBackground :
    public Object
{
private:
	vector<TILE*> tiles;

	// 화면 스크롤 시, 인게임 내 모든 객체를 그릴 때
	// 해당 스크롤 값을 연산하여 그려야 함
	// -> 모든 객체가 타일 bg 객체의 스크롤 값에 접근해야 함
	// 그 때마다, 타일 객체 참조를 넘겨 받기 불편하므로
	// 일단 사용하기 편하게 정적 필드로 만듬
	// 좋은 방식은 아님
public:
	static float scrollX, scrollY;

public:
	vector<TILE*>* GetTiles() { return &tiles; }

public:
	// Object을(를) 통해 상속됨
	void Initialize() override;
	SceneType Update() override;
	void Render(HDC hdc) override;
	void Release() override;

	TileBackground();
	virtual ~TileBackground();
};

