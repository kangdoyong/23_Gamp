#pragma once

// �� ������ ����
enum SceneType
{
	SCENE_NONE = -1,
	SCENE_TITLE,
	SCENE_MENU,
	SCENE_EDIT,
	SCENE_INGAME,
	SCENE_END,
};

// �ΰ��� �� ����� ������ ������ ����
enum ActorType
{
	ACTOR_PLAYER,
	ACTOR_MONSTER,
	ACTOR_END,
};

// �ΰ��� �� ���Ͱ� ���� �� �ִ� ���� ��
enum ActorState
{
	STATE_IDLE,
	STATE_WALK,
	STATE_ATK,
	STATE_HIT,
	STATE_DEAD,
};


// Ÿ�� ������ ��
const int TILE_PRESET_CNT = 24;

// Ÿ�� �ϳ��� ������
const int TILE_SIZE_X = 64;
const int TILE_SIZE_Y = 64;

// cnt x * cnt y �� ���� ũ�⸦ ����
const int TILE_CNT_X = 30;
const int TILE_CNT_Y = 30;

const bool TILE_COLLISION_INFO[] =
{
	false, false, false, false, false,
	false, false, false, false, true,
	true, true, false, false, false,
	false, false, false, false, false,
	false, false, false, false
};
