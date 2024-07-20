#pragma once

// T타입 객체 메모리 해제 함수
template <typename T>
inline void SafeDelete(T& instance)
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}
