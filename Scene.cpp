#include "Scene.h"

Scene::Scene()
{
}

Scene::~Scene()
{
	// �� ��ü �ı� ��, ������ �ִ� ��Ʈ�� ��ü���� ����
	for (auto i = bmpMap.begin(); i != bmpMap.end(); ++i)
	{
		SafeDelete(i->second);
	}
	bmpMap.clear();
}
