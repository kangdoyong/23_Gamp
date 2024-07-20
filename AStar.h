#pragma once
#include "Include.h"

// AStar 알고리즘은 대표적인 휴리스틱 알고리즘

// 휴리스틱이란?
// 사전적으로 시간이나 정보가 불충분하여 합리적인 판단을
// 할 수 없거나, 굳이 체계적이고 합리적인 판단을 할 필요가
// 없는 상황에서 신속하게 사용하는 어림짐작의 기술...
// -> 요약하면 인간의 직관을 이용한 판단

// AStar에서 직관이 이용되는 곳
// 경로에 대한 비용을 산정 시, 휴리스틱을 이용한 방법을 사용
// 비용은 이동 거리를 의미하고,
// 경로의 비용 산정 방식은 F = G + H

// F = 최종 비용
// G = 시작점에서 현재까지의 이동 비용
// H = 장애물들을 제외한 현재 타일에서 도착 타일까지의 예상 비용
//     (휴리스틱을 이용)

// 시작점부터 비용을 연산
// 주변에 인접한 이동한 가능한 타일들을 조사한 후,
// 방문한 적이 없는 타일(오픈/클로즈 리스트에 없음)이라면
// 오픈 리스트(조사 대상 타일)에 넣는다.

// 오픈 리스트에서 가장 비용(F)이이 낮은 타일을 꺼낸 후,
// 클로즈 리스트(조사가 끝난 타일)에 넣음
// 해당 타일이 도착점 타일인지 확인 후,
// 도착점 타일이라면 검사 종료,
// 아니라면 시작점 타일을 가장 비용이 낮은 타일로 변경 후, 
// 도착점 타일을 찾을 때까지, 위의 과정을 반복


class AStar
{
#pragma region 싱글톤 처리
private:
	static AStar* instance;

public:
	static AStar* GetInstance()
	{
		if (instance == nullptr)
			instance = new AStar();

		return instance;
	}
	static void Destroy() { SafeDelete(instance); }

private:
	AStar();
public:
	~AStar();
#pragma endregion

private:
	list<NODE*> openList; // 조사해야할 타일 대상들
	list<NODE*> closeList; // 이미 조사한 타일 대상들
	list<int> bestList; // 조사한 최적의 경로인 타일들의 인덱스

public:
	int startIdx; // 길찾기를 시작할 타일의 인덱스 (마우스 클릭 전, 캐릭터가 서 있는 타일)
	int goalIdx; // 이동 목표 타일의 인덱스 (마우스로 클릭한 타일)

public:
	// 길찾기 시작 시, 호출할 함수
	void AStarStart(int startIdx, int goalIdx);
	// 최적의 경로를 생성하는 함수
	void MakeRoute();
	// 파라미터로 특정 타일의 인덱스를 받아, 해당 타일이
	// 오픈 or 클로즈 리스트에 이미 존재하는지 확인하는 함수
	bool CheckList(int idx);
	bool CheckActor(int idx, vector<TILE*>* tiles);
	// 노드 데이터 생성을 위한 함수
	NODE* MakeNode(int idx, NODE* parent, vector<TILE*>* tiles);
	void Release();
	// 최적 경로를 갖는 목록의 주소를 반환
	list<int>* GetBestList() { return &bestList; }

	// 노드를 비용에 따라 정렬 시, sort 함수에 파라미터로 전달할 정적 메서드
	static bool Compare(NODE* a, NODE* b)
	{
		return a->cost < b->cost;
	}
};

