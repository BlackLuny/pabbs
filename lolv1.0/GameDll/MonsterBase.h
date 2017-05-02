#pragma once
#include "base.h"
/*
���������ࣨ��������:������С��������Ұ�֣����
*/

//����
typedef struct EM_POINT_3D
{
	float x;
	float y;
	float z;
}EM_POINT_3D, *PEM_POINT_3D;

//��Ӫ
enum EM_CAMP
{
	CAMP_EM,
};
//����
enum EM_TYPE
{
	CAMP_EM1,
};

class MonsterBase :
	public base
{
public:
	MonsterBase(DWORD dwNodeBase);
	~MonsterBase();

	//�ӿ�
	float GetCurHp()const;
	float GetMaxHp()const;
	float GetCurMp()const;
	float GetMaxMp()const;

	//��ȡ����
	EM_POINT_3D GetPoint()const;

	EM_CAMP GetCamp()const;

	EM_TYPE GetType()const;

	//�Ƿ���ս��������
	virtual bool BInShowInFag()const;

	//�Ƿ�����
	bool BDead()const;
};

