#pragma once

// 씬 종류를 열거
enum SceneType
{
	SCENE_NONE = -1,
	SCENE_TITLE,
	SCENE_MENU,
	SCENE_EDIT,
	SCENE_INGAME,
	SCENE_END,
};

// 인게임 내 사용할 액터의 종류를 열거
enum ActorType
{
	ACTOR_PLAYER,
	ACTOR_MONSTER,
	ACTOR_END,
};

// 인게임 내 액터가 가질 수 있는 상태 값
enum ActorState
{
	STATE_IDLE,
	STATE_WALK,
	STATE_ATK,
	STATE_HIT,
	STATE_DEAD,
};


// 타일 프리셋 수
const int TILE_PRESET_CNT = 24;

// 타일 하나의 사이즈
const int TILE_SIZE_X = 64;
const int TILE_SIZE_Y = 64;

// cnt x * cnt y 로 맵의 크기를 결정
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
