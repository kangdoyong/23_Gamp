#pragma once
#include "Include.h"

class Scene abstract
{
protected:
	// �� �� ����, ��� ������ �̹����� ���
	// ���� �̹����� ��Ÿ�� ��, ��Ʈ�� ��ü�� �̿�
	// ������ ��Ʈ�� ��ü�� ��Ƶ� �����̳ʸ� ����

	// map�� key�� value�� �� ��(pair)�� ����� ���ҷ� ����
	// key�� �����͸� �ĺ��� �ĺ���
	// value�� ���� Ȱ���ϰ����ϴ� ������
	map<string, Bitmap*> bmpMap;

public:
	virtual void Initialize() abstract;
	virtual void Update() abstract;
	virtual void Render(HDC hdc) abstract;
	virtual void Release() abstract;

	Scene();
	virtual ~Scene();
};

