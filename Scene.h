#pragma once
#include "Include.h"

class Scene abstract
{
protected:
	// 각 씬 마다, 모두 복수의 이미지를 사용
	// 현재 이미지를 나타낼 때, 비트맵 객체를 이용
	// 복수의 비트맵 객체를 담아둘 컨테이너를 선언

	// map은 key와 value로 한 쌍(pair)을 만들어 원소로 갖음
	// key는 데이터를 식별할 식별자
	// value는 실제 활용하고자하는 데이터
	map<string, Bitmap*> bmpMap;

public:
	virtual void Initialize() abstract;
	virtual void Update() abstract;
	virtual void Render(HDC hdc) abstract;
	virtual void Release() abstract;

	Scene();
	virtual ~Scene();
};

