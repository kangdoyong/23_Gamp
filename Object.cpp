#include "Object.h"
#include "AStar.h"
#include "SceneMgr.h"
#include "Ingame.h"

map<string, Bitmap*>* Object::bmpMapAddress = nullptr;

RECT Object::GetRect()
{
	RECT rc =
	{
		info.posX - info.sizeX / 2,
		info.posY - info.sizeY / 2,
		info.posX + info.sizeX / 2,
		info.posY + info.sizeY / 2
	};

    return rc;
}

void Object::UpdateFrame()
{
	// 마지막으로 프레임을 갱신한 시간에서 설정한 간격을 더한 값이
	// 현재 시간보다 작다면 프레임을 갱신할 시간이라는 뜻
	auto t = GetTickCount64();
	if (lastAnimUpdateTime + frame.time < t)
	{
		// 새로 갱신하므로, 마지막 갱신 시간 변경
		lastAnimUpdateTime = t;
		// 프레임을 다음 열로 변경
		++frame.current;

		// 변경한 프레임 인덱스가 마지막 프레임 인덱스를
		// 넘어섰는지 확인
		if (frame.current > frame.last)
		{
			// 애니메이션 루프 여부에 따라 처리
			if (frame.isLoop)
			{
				// 현재 프레임 인덱스를 초기화
				frame.current = 0;
			}
			else
			{
				// 루프가 아니라면, 기획에 따른 설정값으로 세팅
				InitFrame();
			}
		}
	}
}

void Object::UpdateTileActor()
{
	// 객체의 위치를 기반으로 타일 인덱스를 가져오고
	auto idx = GetTileIndex(info.posX, info.posY);

	// 가져온 타일 인덱스가 객체가 마지막에 있었던 타일 인덱스와
	// 같은지 비교
	//  -> 같다면 이동을 안했다는 뜻,
	//     다르다면 객체가 이동을 했다는 뜻
	if (lastTileIdx == idx)
		return;

	// 객체가 가지고 있는 타일 인덱스와 방금 구한 타일 인덱스가
	// 다른 경우, 객체가 가지고 있는 타일 인덱스 정보 및
	// 해당 타일의 actor 필드의 정보를 수정
	auto tiles = ((Ingame*)SceneMgr::GetInstance()->GetScene())->GetTiles();
	
	// 이전 타일에 있던 actor의 주소를 비움
	if (lastTileIdx > 0)
		(*tiles)[lastTileIdx]->actor = nullptr;
	// 객체가 갖는 타일 인덱스를 방금 구한 타일 인덱스로 갱신
	lastTileIdx = idx;
	// 방금 구한 타일 인덱스의 타일에 객체의 주소를 넣음
	(*tiles)[idx]->actor = this;
}

void Object::OnGoalEvent()
{
	auto goalActorInfo = goalActor->GetInfo();
	auto dispX = goalActorInfo.posX - info.posX;
	auto dispY = goalActorInfo.posY - info.posY;

	auto isHorizontal = abs(dispX) > abs(dispY);

	dirX = isHorizontal ? GetDirection(dispX) : 0;
	dirY = isHorizontal ? 0 : GetDirection(dispY);
	goalActor = nullptr;
}

Object::Object()
{
}

Object::~Object()
{
}

int Object::GetTileIndex(float posX, float posY)
{
	int c = posX / TILE_SIZE_X;
	int r = posY / TILE_SIZE_Y;

    return r * TILE_CNT_X + c;
}

void Object::AStarStart(float startX, float startY, float goalX, float goalY)
{
	// 시작 위치의 타일 인덱스를 구함
	int startIdx = GetTileIndex(startX, startY);
	// 인덱스 범위를 벗어나는지 확인
	if (startIdx < 0 || startIdx >= TILE_CNT_X * TILE_CNT_Y)
		return;

	int goalIdx = GetTileIndex(goalX, goalY);
	if (goalIdx < 0 || goalIdx >= TILE_CNT_X * TILE_CNT_Y)
		return;

	auto tiles = ((Ingame*)SceneMgr::GetInstance()->GetScene())->GetTiles();
	goalActor = (*tiles)[goalIdx]->actor;
	// 구한 타일 인덱스를 기반으로 길찾기 시작
	AStar::GetInstance()->AStarStart(startIdx, goalIdx);
}

void Object::AStarMove()
{
	// 목적지까지 최적 경로인 타일들의 인덱스를 갖는 목록을 가져옴
	auto bestList = AStar::GetInstance()->GetBestList();

	// 위에 가져온 최적 경로를 따라 이동하기 위해 타일 정보들을 가져옴
	auto tiles = ((Ingame*)SceneMgr::GetInstance()->GetScene())->GetTiles();

	// 최적 경로가 없을 경우 리턴
	if (bestList == nullptr || bestList->empty() || tiles == nullptr)
	{
		if (goalActor == nullptr)
		{
			dirX = 0;
			dirY = 0;
		}
		else
		{
			OnGoalEvent();
		}
		
		return;
	}

	// 최적 경로 목록에서 맨 앞의 원소(이동할 타일 1개) 정보를 가져옴
	int destIdx = bestList->front();

	/*if ((*tiles)[destIdx]->actor != nullptr)
	{
		bestList->clear();
		return;
	}*/

	// 현재 객체의 위치에서 이동할 타일로의 방향을 구함
	
	// 각 축으로 길이를 구함
	float distanceX = (*tiles)[destIdx]->posX - info.posX;
	float distanceY = (*tiles)[destIdx]->posY - info.posY;

	// 직선 거리를 구함
	float distance = sqrt(distanceX * distanceX + distanceY * distanceY);

	// 이동할 타일에 도착한 경우
	// 타일 도착 판정을 위한 정지 거리를 지정하여 검사
	if (distance < 5.f)
	{
		// 이 곳에 들어왔다는 것은, 이동할 타일에 도착했다는 뜻
		// 최적 경로 목록에서 첫번째 원소를 꺼냄
		bestList->pop_front();
		return;
	}

	// 이동할 타일에 도착하지 않은 경우 (이동 중)

	// 수평 (x), 수직 (y) 이동인지 확인
	auto isHorizontal = abs(distanceX) > abs(distanceY) ? true : false;

	dirX = isHorizontal ? GetDirection(distanceX) : 0;
	dirY = isHorizontal ? 0 : GetDirection(distanceY);

	info.posX += dirX * speed;
	info.posY += dirY * speed;
}

float Object::GetDirection(float length)
{
	if (length > 0)
		return 1.f;
	else if (length < 0)
		return -1.f;

	return 0.0f;
}
