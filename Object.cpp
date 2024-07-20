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
	// ���������� �������� ������ �ð����� ������ ������ ���� ����
	// ���� �ð����� �۴ٸ� �������� ������ �ð��̶�� ��
	auto t = GetTickCount64();
	if (lastAnimUpdateTime + frame.time < t)
	{
		// ���� �����ϹǷ�, ������ ���� �ð� ����
		lastAnimUpdateTime = t;
		// �������� ���� ���� ����
		++frame.current;

		// ������ ������ �ε����� ������ ������ �ε�����
		// �Ѿ���� Ȯ��
		if (frame.current > frame.last)
		{
			// �ִϸ��̼� ���� ���ο� ���� ó��
			if (frame.isLoop)
			{
				// ���� ������ �ε����� �ʱ�ȭ
				frame.current = 0;
			}
			else
			{
				// ������ �ƴ϶��, ��ȹ�� ���� ���������� ����
				InitFrame();
			}
		}
	}
}

void Object::UpdateTileActor()
{
	// ��ü�� ��ġ�� ������� Ÿ�� �ε����� ��������
	auto idx = GetTileIndex(info.posX, info.posY);

	// ������ Ÿ�� �ε����� ��ü�� �������� �־��� Ÿ�� �ε�����
	// ������ ��
	//  -> ���ٸ� �̵��� ���ߴٴ� ��,
	//     �ٸ��ٸ� ��ü�� �̵��� �ߴٴ� ��
	if (lastTileIdx == idx)
		return;

	// ��ü�� ������ �ִ� Ÿ�� �ε����� ��� ���� Ÿ�� �ε�����
	// �ٸ� ���, ��ü�� ������ �ִ� Ÿ�� �ε��� ���� ��
	// �ش� Ÿ���� actor �ʵ��� ������ ����
	auto tiles = ((Ingame*)SceneMgr::GetInstance()->GetScene())->GetTiles();
	
	// ���� Ÿ�Ͽ� �ִ� actor�� �ּҸ� ���
	if (lastTileIdx > 0)
		(*tiles)[lastTileIdx]->actor = nullptr;
	// ��ü�� ���� Ÿ�� �ε����� ��� ���� Ÿ�� �ε����� ����
	lastTileIdx = idx;
	// ��� ���� Ÿ�� �ε����� Ÿ�Ͽ� ��ü�� �ּҸ� ����
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
	// ���� ��ġ�� Ÿ�� �ε����� ����
	int startIdx = GetTileIndex(startX, startY);
	// �ε��� ������ ������� Ȯ��
	if (startIdx < 0 || startIdx >= TILE_CNT_X * TILE_CNT_Y)
		return;

	int goalIdx = GetTileIndex(goalX, goalY);
	if (goalIdx < 0 || goalIdx >= TILE_CNT_X * TILE_CNT_Y)
		return;

	auto tiles = ((Ingame*)SceneMgr::GetInstance()->GetScene())->GetTiles();
	goalActor = (*tiles)[goalIdx]->actor;
	// ���� Ÿ�� �ε����� ������� ��ã�� ����
	AStar::GetInstance()->AStarStart(startIdx, goalIdx);
}

void Object::AStarMove()
{
	// ���������� ���� ����� Ÿ�ϵ��� �ε����� ���� ����� ������
	auto bestList = AStar::GetInstance()->GetBestList();

	// ���� ������ ���� ��θ� ���� �̵��ϱ� ���� Ÿ�� �������� ������
	auto tiles = ((Ingame*)SceneMgr::GetInstance()->GetScene())->GetTiles();

	// ���� ��ΰ� ���� ��� ����
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

	// ���� ��� ��Ͽ��� �� ���� ����(�̵��� Ÿ�� 1��) ������ ������
	int destIdx = bestList->front();

	/*if ((*tiles)[destIdx]->actor != nullptr)
	{
		bestList->clear();
		return;
	}*/

	// ���� ��ü�� ��ġ���� �̵��� Ÿ�Ϸ��� ������ ����
	
	// �� ������ ���̸� ����
	float distanceX = (*tiles)[destIdx]->posX - info.posX;
	float distanceY = (*tiles)[destIdx]->posY - info.posY;

	// ���� �Ÿ��� ����
	float distance = sqrt(distanceX * distanceX + distanceY * distanceY);

	// �̵��� Ÿ�Ͽ� ������ ���
	// Ÿ�� ���� ������ ���� ���� �Ÿ��� �����Ͽ� �˻�
	if (distance < 5.f)
	{
		// �� ���� ���Դٴ� ����, �̵��� Ÿ�Ͽ� �����ߴٴ� ��
		// ���� ��� ��Ͽ��� ù��° ���Ҹ� ����
		bestList->pop_front();
		return;
	}

	// �̵��� Ÿ�Ͽ� �������� ���� ��� (�̵� ��)

	// ���� (x), ���� (y) �̵����� Ȯ��
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
