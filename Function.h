#pragma once

// TŸ�� ��ü �޸� ���� �Լ�
template <typename T>
inline void SafeDelete(T& instance)
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}
