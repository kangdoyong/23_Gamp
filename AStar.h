#pragma once
#include "Include.h"

// AStar �˰����� ��ǥ���� �޸���ƽ �˰���

// �޸���ƽ�̶�?
// ���������� �ð��̳� ������ ������Ͽ� �ո����� �Ǵ���
// �� �� ���ų�, ���� ü�����̰� �ո����� �Ǵ��� �� �ʿ䰡
// ���� ��Ȳ���� �ż��ϰ� ����ϴ� ������� ���...
// -> ����ϸ� �ΰ��� ������ �̿��� �Ǵ�

// AStar���� ������ �̿�Ǵ� ��
// ��ο� ���� ����� ���� ��, �޸���ƽ�� �̿��� ����� ���
// ����� �̵� �Ÿ��� �ǹ��ϰ�,
// ����� ��� ���� ����� F = G + H

// F = ���� ���
// G = ���������� ��������� �̵� ���
// H = ��ֹ����� ������ ���� Ÿ�Ͽ��� ���� Ÿ�ϱ����� ���� ���
//     (�޸���ƽ�� �̿�)

// ���������� ����� ����
// �ֺ��� ������ �̵��� ������ Ÿ�ϵ��� ������ ��,
// �湮�� ���� ���� Ÿ��(����/Ŭ���� ����Ʈ�� ����)�̶��
// ���� ����Ʈ(���� ��� Ÿ��)�� �ִ´�.

// ���� ����Ʈ���� ���� ���(F)���� ���� Ÿ���� ���� ��,
// Ŭ���� ����Ʈ(���簡 ���� Ÿ��)�� ����
// �ش� Ÿ���� ������ Ÿ������ Ȯ�� ��,
// ������ Ÿ���̶�� �˻� ����,
// �ƴ϶�� ������ Ÿ���� ���� ����� ���� Ÿ�Ϸ� ���� ��, 
// ������ Ÿ���� ã�� ������, ���� ������ �ݺ�


class AStar
{
#pragma region �̱��� ó��
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
	list<NODE*> openList; // �����ؾ��� Ÿ�� ����
	list<NODE*> closeList; // �̹� ������ Ÿ�� ����
	list<int> bestList; // ������ ������ ����� Ÿ�ϵ��� �ε���

public:
	int startIdx; // ��ã�⸦ ������ Ÿ���� �ε��� (���콺 Ŭ�� ��, ĳ���Ͱ� �� �ִ� Ÿ��)
	int goalIdx; // �̵� ��ǥ Ÿ���� �ε��� (���콺�� Ŭ���� Ÿ��)

public:
	// ��ã�� ���� ��, ȣ���� �Լ�
	void AStarStart(int startIdx, int goalIdx);
	// ������ ��θ� �����ϴ� �Լ�
	void MakeRoute();
	// �Ķ���ͷ� Ư�� Ÿ���� �ε����� �޾�, �ش� Ÿ����
	// ���� or Ŭ���� ����Ʈ�� �̹� �����ϴ��� Ȯ���ϴ� �Լ�
	bool CheckList(int idx);
	bool CheckActor(int idx, vector<TILE*>* tiles);
	// ��� ������ ������ ���� �Լ�
	NODE* MakeNode(int idx, NODE* parent, vector<TILE*>* tiles);
	void Release();
	// ���� ��θ� ���� ����� �ּҸ� ��ȯ
	list<int>* GetBestList() { return &bestList; }

	// ��带 ��뿡 ���� ���� ��, sort �Լ��� �Ķ���ͷ� ������ ���� �޼���
	static bool Compare(NODE* a, NODE* b)
	{
		return a->cost < b->cost;
	}
};

