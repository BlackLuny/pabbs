#pragma once
#include "MonsterBase.h"
class person :
	public MonsterBase
{
public:
	person(DWORD dwNodeBase);
	~person();

	//��ȡ��ҵ���ͨ��������
	float GetAttackRange()const;

};

