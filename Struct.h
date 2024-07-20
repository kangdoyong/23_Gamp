#pragma once

// Ư�� ��ü�� �׸� ��, ��ġ�� ����� �ʿ�
// �׷� �� ������, ��ġ�� ����� ���õ� ������
// ���� �����ϱ� ���ŷο�Ƿ� ���� ���Ǵ� �����͸� ����üȭ
typedef struct tagInfo
{
	float posX;
	float posY;
	float sizeX;
	float sizeY;
}INFO;


class Object;
// Ÿ�� ��ü �ϳ��� ���� ������ ����
typedef struct tagTile
{
	float posX;
	float posY;
	float sizeX;
	float sizeY;
	int drawId;
	bool isColl;
	Object* actor; // Ÿ�� ���� �ִ� ������ �ּҸ� ���� �ʵ�
}TILE;

// �ִϸ��̼� ó���� ���Ǵ� �����͸� ��Ƴ��� ����ü
typedef struct tagFrame
{
	bool isLoop; // �ִϸ��̼��� �ݺ� ����
	int animType; // ���� �ִϸ��̼� Ÿ�� (���° ��)
	int current; // ���� �ִϸ��̼ǿ��� ���° ������ (���° ��)
	int last; // ���� �ִϸ��̼��� ������ ���� �ε���
	ULONGLONG time; // ���� �����ӿ��� ���� ���������� ������ ��, �ɸ��� �ð�

	tagFrame() {}
	tagFrame(bool isLoop, int animType, int current, int last, ULONGLONG time)
		: isLoop(isLoop), animType(animType), current(current), last(last), time(time) {}
}FRAME;

typedef struct AStarNode
{
	float cost; // ��� = �θ� �������� �Ÿ� + ���� �������� �Ÿ�
	int idx; // Ÿ�� �ε���
	AStarNode* parent; // ���� ��� (�θ� ���) 
}NODE;