#pragma once
#include "Include.h"

// 모든 인게임 액터들의 베이스가 추상 클래스
class Object abstract
{
protected:
	// 텍스쳐를 그릴 때, 사용할 키 값
	string drawKey;
	INFO info;
	// 객체가 마지막에 있었던 타일의 인덱스 값을 담아둘 필드
	Object* goalActor;
	int lastTileIdx = -1;
	float speed;
	float dirX;
	float dirY;
	// 마지막으로 애니메이션을 갱신한 시간을 갖는 필드
	ULONGLONG lastAnimUpdateTime;
	// 애니메이션 재생에 필요한 데이터 필드
	FRAME frame;

	// 현재 각 씬 객체마다, 해당 씬에 필요한 텍스쳐를 map에 들고 있음
	// 이 때, 각 객체(액터)들은 자기 자신 또는 그 외 필요한 텍스쳐를
	// 출력하기 위해선, 씬 객체가 갖고 있는 map에 접근해야 함
	// 이 때, 해당 map에 접근을 편리하게 하기 위해, map의 주소를 갖는
	// 정적 필드를 선언
	static map<string, Bitmap*>* bmpMapAddress;

public:
	INFO GetInfo() { return info; }
	void SetDrawKey(string key) { drawKey = key; }
	void SetPos(float x, float y) { info.posX = x; info.posY = y; }
	RECT GetRect();
	virtual void InitFrame() {};
	void UpdateFrame(); // 설정된 현재 애니메이션에서 프레임을 변경하는 기능
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

	// 파라미터로 받은 위치에 해당하는 타일 인덱스를 반환하는 기능
	int GetTileIndex(float posX, float posY);
	// 길찾기 시작 기능
	void AStarStart(float startX, float startY, float goalX, float goalY);
	// 길찾기를 통해 얻은 경로를 따라 이동하는 기능
	void AStarMove();

	float GetDirection(float length);

	Object();
	virtual ~Object();
};

