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
	//��ȡ��ҹ����ٶ�
	float GetAttackSpeed()const;
	//��ȡ��ҽ��
	float GetGold()const;
};

