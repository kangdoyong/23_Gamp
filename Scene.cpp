#include "Scene.h"

Scene::Scene()
{
}

Scene::~Scene()
{
	// ¾À °´Ã¼ ÆÄ±« ½Ã, °¡Áö°í ÀÖ´ø ºñÆ®¸Ê °´Ã¼µéÀ» ÇØÁ¦
	for (auto i = bmpMap.begin(); i != bmpMap.end(); ++i)
	{
		SafeDelete(i->second);
	}
	bmpMap.clear();
}
