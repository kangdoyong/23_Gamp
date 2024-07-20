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
	// �̵��� Ÿ���� ���� Ÿ�ϰ� �����ϴٸ� ����
	if (startIdx == goalIdx)
		return;

	// Ÿ�� ���� �ҷ�����
	auto tiles = ((Ingame*)SceneMgr::GetInstance()->GetScene())->GetTiles();

	// Ÿ�� ������ ���ٸ� ����
	if (tiles == nullptr)
		return;

	// ���� Ÿ���� ĳ���Ͱ� ������ �� ���� (�浹�ϴ�) Ÿ���̶�� ����
	if ((*tiles)[goalIdx]->isColl)
		return;

	// �̹� ���� ������ ���¿���, AStar�� �� ȣ��� ���
	// ������ �ִ� �����͵��� �����ϱ� ���� ȣ��
	// or �̹� ���� ��ã�⿡�� ���Ǿ��� �����͵��� �����ϴ� �뵵
	Release();

	this->startIdx = startIdx;
	this->goalIdx = goalIdx;

	// ��� ���� ����
	MakeRoute();
}

void AStar::MakeRoute()
{
	// Ÿ�� ���� �ҷ�����
	auto tiles = ((Ingame*)SceneMgr::GetInstance()->GetScene())->GetTiles();

	if (tiles == nullptr)
		return;

	// ���� ��� ����
	NODE* node = new NODE();
	// ���� ����� Ÿ�� �ε����� ��ã�� ������ Ÿ�� �ε����� ����
	node->idx = startIdx;
	// �ش� ��尡 ���� ����̹Ƿ� ����(�θ�) ��尡 ����
	node->parent = nullptr;
	node->cost = 0;

	// ���� ��带 �̹� ������ ������� ���
	closeList.push_back(node);

	// ���� Ÿ�� �˻� ��, ���Ƿ� Ÿ�� �ε����� ��� ��Ƶα� ���� ����
	int index = 0;

	while (true)
	{
		// ��
		index = node->idx - TILE_CNT_X; // �� ĭ ���� Ÿ�� �ε����� ����

		// �����ϴ� Ÿ������? (�ùٸ� Ÿ�� �ε��� ������)
		// �� �� �ִ� Ÿ������? (�浹 ����)
		// �̹� �����߰ų�, ������ ��� ���ԵǾ� �ִٸ� ����
		if (index >= 0
			&& (*tiles)[index]->isColl == false
			&& CheckList(index)
			&& CheckActor(index, tiles))
		{
			// Ÿ�� �ε����� �ش��ϴ� Ÿ�� ����(���)�� ���� ��
			// ���� ����Ʈ(������ ���)�� �߰�
			openList.push_back(MakeNode(index, node, tiles));
		}

		// �Ʒ�
		index = node->idx + TILE_CNT_X; // �� ĭ ���� Ÿ�� �ε����� ����

		// �����ϴ� Ÿ������? (�ùٸ� Ÿ�� �ε��� ������)
		// �� �� �ִ� Ÿ������? (�浹 ����)
		// �̹� �����߰ų�, ������ ��� ���ԵǾ� �ִٸ� ����
		if (index < (TILE_CNT_X * TILE_CNT_Y)
			&& (*tiles)[index]->isColl == false
			&& CheckList(index)
			&& CheckActor(index, tiles))
		{
			// Ÿ�� �ε����� �ش��ϴ� Ÿ�� ����(���)�� ���� ��
			// ���� ����Ʈ(������ ���)�� �߰�
			openList.push_back(MakeNode(index, node, tiles));
		}

		// ����
		index = node->idx - 1; // �� ĭ ���� Ÿ�� �ε����� ����

		// �����ϴ� Ÿ������? (�ùٸ� Ÿ�� �ε��� ������)
		// �� �� �ִ� Ÿ������? (�浹 ����)
		// �̹� �����߰ų�, ������ ��� ���ԵǾ� �ִٸ� ����
		if (index >= 0 && (index % TILE_CNT_X != TILE_CNT_X - 1)
			&& (*tiles)[index]->isColl == false
			&& CheckList(index)
			&& CheckActor(index, tiles))
		{
			// Ÿ�� �ε����� �ش��ϴ� Ÿ�� ����(���)�� ���� ��
			// ���� ����Ʈ(������ ���)�� �߰�
			openList.push_back(MakeNode(index, node, tiles));
		}

		// ������
		index = node->idx + 1; // �� ĭ ���� Ÿ�� �ε����� ����

		// �����ϴ� Ÿ������? (�ùٸ� Ÿ�� �ε��� ������)
		// �� �� �ִ� Ÿ������? (�浹 ����)
		// �̹� �����߰ų�, ������ ��� ���ԵǾ� �ִٸ� ����
		if (index < (TILE_CNT_X * TILE_CNT_Y) && (index % TILE_CNT_X != 0)
			&& (*tiles)[index]->isColl == false
			&& CheckList(index)
			&& CheckActor(index, tiles))
		{
			// Ÿ�� �ε����� �ش��ϴ� Ÿ�� ����(���)�� ���� ��
			// ���� ����Ʈ(������ ���)�� �߰�
			openList.push_back(MakeNode(index, node, tiles));
		}

	    // ���� ����Ʈ�� ����
		// -> ���(�Ÿ�)�� �������� ������������ ����
		openList.sort(Compare);

		// ���� ����Ʈ�� ����ִٸ�
		if (openList.empty())
		{
			return;
		}

		// ���� ����Ʈ���� ����� ���� ���� ��带 ������
		auto i = openList.begin();
		// ����� ���� ���� ��带 ���� �˻翡 ����� ���� ����
		node = *i;

		// ����� ���� ���� ��带 ������, ���� �˻翡 ����� �����̹Ƿ�
		// �ش� ����� ���簡 �����ٰ� �����ϰ�, Ŭ���� ����Ʈ�� ����
		// ���� ����Ʈ������ ����
		closeList.push_back(*i);
		openList.erase(i);

		// ���� �˻��� ����� Ÿ�� �ε����� �� �ε����� ������ Ȯ��
		if (node->idx == goalIdx)
		{
			if ((*tiles)[goalIdx]->actor != nullptr)
			{
				node = node->parent;
			}

			// �� �ε����� �����ϴ� ��θ� ã�Ҵٴ� ��
			// ����, ������ ��� �����͸� ��´�.
			while (true)
			{
				// �˻� ��忡 �����Ͽ� ����(�θ� ���)���� Ÿ�� �ε����� ����
				bestList.push_back(node->idx);
				node = node->parent;

				if (node == nullptr)
				{
					bestList.clear();
					break;
				}

				// ���������� �����ߴٸ� ����
				if (node->idx == startIdx)
					break;
			}
			// bestList�� ��θ� ��Ÿ���� Ÿ�� �ε����� �������� ��� �����Ƿ�
			// ������ ������ ������Ų��.
			bestList.reverse();
			return;
		}
	}
}

bool AStar::CheckList(int idx)
{
	// ���� or Ŭ���� ����Ʈ�� �����Ѵٸ� false
	// �������� �ʴ´ٸ� true
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
	
	// ���� ������ ��忡�� ����(�θ�) �������� ���� �Ÿ�
	float distanceX = (*tiles)[parent->idx]->posX - (*tiles)[idx]->posX;
	float distanceY = (*tiles)[parent->idx]->posY - (*tiles)[idx]->posY;
	float gCost = sqrt(distanceX * distanceX + distanceY * distanceY);

	// ���� ������ ��忡�� ���� �������� ���� �Ÿ�
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
