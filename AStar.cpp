#include "AStar.h"
#include "SceneMgr.h"
#include "Ingame.h"

AStar* AStar::instance = nullptr;

AStar::AStar()
{
}

AStar::~AStar()
{
	Release();
}

void AStar::AStarStart(int startIdx, int goalIdx)
{
	// 이동할 타일이 시작 타일과 동일하다면 리턴
	if (startIdx == goalIdx)
		return;

	// 타일 정보 불러오기
	auto tiles = ((Ingame*)SceneMgr::GetInstance()->GetScene())->GetTiles();

	// 타일 정보가 없다면 리턴
	if (tiles == nullptr)
		return;

	// 도착 타일이 캐릭터가 서있을 수 없는 (충돌하는) 타일이라면 리턴
	if ((*tiles)[goalIdx]->isColl)
		return;

	// 이미 골이 지정된 상태에서, AStar가 또 호출될 경우
	// 기존에 있던 데이터들을 해제하기 위해 호출
	// or 이미 이전 길찾기에서 사용되었던 데이터들을 해제하는 용도
	Release();

	this->startIdx = startIdx;
	this->goalIdx = goalIdx;

	// 경로 생성 시작
	MakeRoute();
}

void AStar::MakeRoute()
{
	// 타일 정보 불러오기
	auto tiles = ((Ingame*)SceneMgr::GetInstance()->GetScene())->GetTiles();

	if (tiles == nullptr)
		return;

	// 시작 노드 생성
	NODE* node = new NODE();
	// 시작 노드의 타일 인덱스를 길찾기 시작한 타일 인덱스로 설정
	node->idx = startIdx;
	// 해당 노드가 시작 노드이므로 이전(부모) 노드가 없음
	node->parent = nullptr;
	node->cost = 0;

	// 시작 노드를 이미 조사한 대상으로 등록
	closeList.push_back(node);

	// 인접 타일 검사 시, 임의로 타일 인덱스를 잠시 담아두기 위한 변수
	int index = 0;

	while (true)
	{
		// 위
		index = node->idx - TILE_CNT_X; // 한 칸 위의 타일 인덱스를 구함

		// 존재하는 타일인지? (올바른 타일 인덱스 값인지)
		// 갈 수 있는 타일인지? (충돌 여부)
		// 이미 조사했거나, 조사할 대상에 포함되어 있다면 제외
		if (index >= 0
			&& (*tiles)[index]->isColl == false
			&& CheckList(index)
			&& CheckActor(index, tiles))
		{
			// 타일 인덱스에 해당하는 타일 정보(노드)를 생성 후
			// 오픈 리스트(조사할 대상)에 추가
			openList.push_back(MakeNode(index, node, tiles));
		}

		// 아래
		index = node->idx + TILE_CNT_X; // 한 칸 위의 타일 인덱스를 구함

		// 존재하는 타일인지? (올바른 타일 인덱스 값인지)
		// 갈 수 있는 타일인지? (충돌 여부)
		// 이미 조사했거나, 조사할 대상에 포함되어 있다면 제외
		if (index < (TILE_CNT_X * TILE_CNT_Y)
			&& (*tiles)[index]->isColl == false
			&& CheckList(index)
			&& CheckActor(index, tiles))
		{
			// 타일 인덱스에 해당하는 타일 정보(노드)를 생성 후
			// 오픈 리스트(조사할 대상)에 추가
			openList.push_back(MakeNode(index, node, tiles));
		}

		// 왼쪽
		index = node->idx - 1; // 한 칸 위의 타일 인덱스를 구함

		// 존재하는 타일인지? (올바른 타일 인덱스 값인지)
		// 갈 수 있는 타일인지? (충돌 여부)
		// 이미 조사했거나, 조사할 대상에 포함되어 있다면 제외
		if (index >= 0 && (index % TILE_CNT_X != TILE_CNT_X - 1)
			&& (*tiles)[index]->isColl == false
			&& CheckList(index)
			&& CheckActor(index, tiles))
		{
			// 타일 인덱스에 해당하는 타일 정보(노드)를 생성 후
			// 오픈 리스트(조사할 대상)에 추가
			openList.push_back(MakeNode(index, node, tiles));
		}

		// 오른쪽
		index = node->idx + 1; // 한 칸 위의 타일 인덱스를 구함

		// 존재하는 타일인지? (올바른 타일 인덱스 값인지)
		// 갈 수 있는 타일인지? (충돌 여부)
		// 이미 조사했거나, 조사할 대상에 포함되어 있다면 제외
		if (index < (TILE_CNT_X * TILE_CNT_Y) && (index % TILE_CNT_X != 0)
			&& (*tiles)[index]->isColl == false
			&& CheckList(index)
			&& CheckActor(index, tiles))
		{
			// 타일 인덱스에 해당하는 타일 정보(노드)를 생성 후
			// 오픈 리스트(조사할 대상)에 추가
			openList.push_back(MakeNode(index, node, tiles));
		}

	    // 오픈 리스트를 정렬
		// -> 비용(거리)를 기준으로 오름차순으로 정렬
		openList.sort(Compare);

		// 오픈 리스트가 비어있다면
		if (openList.empty())
		{
			return;
		}

		// 오픈 리스트에서 비용이 가장 낮은 노드를 가져옴
		auto i = openList.begin();
		// 비용이 가장 낮은 노드를 다음 검사에 사용할 노드로 설정
		node = *i;

		// 비용이 가장 낮은 노드를 가지고, 다음 검사에 사용할 예정이므로
		// 해당 노드의 조사가 끝났다고 판정하고, 클로즈 리스트에 담음
		// 오픈 리스트에서도 제거
		closeList.push_back(*i);
		openList.erase(i);

		// 다음 검사할 노드의 타일 인덱스가 골 인덱스와 같은지 확인
		if (node->idx == goalIdx)
		{
			if ((*tiles)[goalIdx]->actor != nullptr)
			{
				node = node->parent;
			}

			// 골 인덱스에 도달하는 경로를 찾았다는 뜻
			// 따라서, 최적의 경로 데이터를 얻는다.
			while (true)
			{
				// 검사 노드에 접근하여 역순(부모 노드)으로 타일 인덱스를 얻음
				bestList.push_back(node->idx);
				node = node->parent;

				if (node == nullptr)
				{
					bestList.clear();
					break;
				}

				// 시작점까지 역행했다면 종료
				if (node->idx == startIdx)
					break;
			}
			// bestList에 경로를 나타내는 타일 인덱스가 역순으로 담겨 있으므로
			// 원소의 순서를 반전시킨다.
			bestList.reverse();
			return;
		}
	}
}

bool AStar::CheckList(int idx)
{
	// 오픈 or 클로즈 리스트에 존재한다면 false
	// 존재하지 않는다면 true
	for (auto i = openList.begin(); i != openList.end(); ++i)
	{
		if ((*i)->idx == idx)
			return false;
	}

	for (auto i = closeList.begin(); i != closeList.end(); ++i)
	{
		if ((*i)->idx == idx)
			return false;
	}

	return true;
}

bool AStar::CheckActor(int idx, vector<TILE*>* tiles)
{
	if (idx == goalIdx)
		return true;

	return (*tiles)[idx]->actor == nullptr;
}

NODE* AStar::MakeNode(int idx, NODE* parent, vector<TILE*>* tiles)
{
	NODE* node = new NODE();
	node->idx = idx;
	node->parent = parent;

	// F = G + H
	
	// 현재 생성한 노드에서 이전(부모) 노드까지의 직선 거리
	float distanceX = (*tiles)[parent->idx]->posX - (*tiles)[idx]->posX;
	float distanceY = (*tiles)[parent->idx]->posY - (*tiles)[idx]->posY;
	float gCost = sqrt(distanceX * distanceX + distanceY * distanceY);

	// 현재 생성한 노드에서 도착 노드까지의 직선 거리
	distanceX = (*tiles)[goalIdx]->posX - (*tiles)[idx]->posX;
	distanceY = (*tiles)[goalIdx]->posY - (*tiles)[idx]->posY;
	float hCost = sqrt(distanceX * distanceX + distanceY * distanceY);

	node->cost = gCost + hCost;

	return node;
}

void AStar::Release()
{
	for (auto i = openList.begin(); i != openList.end(); ++i)
		SafeDelete(*i);
	openList.clear();

	for (auto i = closeList.begin(); i != closeList.end(); ++i)
		SafeDelete(*i);
	closeList.clear();

	bestList.clear();
}
