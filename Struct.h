#pragma once

// 특정 객체를 그릴 때, 위치와 사이즈가 필요
// 그럼 그 때마다, 위치와 사이즈에 관련된 변수를
// 새로 선언하기 번거로우므로 자주 사용되는 데이터를 구조체화
typedef struct tagInfo
{
	float posX;
	float posY;
	float sizeX;
	float sizeY;
}INFO;


class Object;
// 타일 객체 하나가 갖는 데이터 집합
typedef struct tagTile
{
	float posX;
	float posY;
	float sizeX;
	float sizeY;
	int drawId;
	bool isColl;
	Object* actor; // 타일 위에 있는 액터의 주소를 담을 필드
}TILE;

// 애니메이션 처리에 사용되는 데이터를 모아놓은 구조체
typedef struct tagFrame
{
	bool isLoop; // 애니메이션의 반복 여부
	int animType; // 현재 애니메이션 타입 (몇번째 행)
	int current; // 현재 애니메이션에서 몇번째 프레임 (몇번째 열)
	int last; // 현재 애니메이션의 마지막 열의 인덱스
	ULONGLONG time; // 현재 프레임에서 다음 프레임으로 변경할 때, 걸리는 시간

	tagFrame() {}
	tagFrame(bool isLoop, int animType, int current, int last, ULONGLONG time)
		: isLoop(isLoop), animType(animType), current(current), last(last), time(time) {}
}FRAME;

typedef struct AStarNode
{
	float cost; // 비용 = 부모 노드까지의 거리 + 도착 노드까지의 거리
	int idx; // 타일 인덱스
	AStarNode* parent; // 이전 노드 (부모 노드) 
}NODE;