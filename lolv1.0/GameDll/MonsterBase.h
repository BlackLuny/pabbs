#pragma once
#include "base.h"
/*
���������ࣨ��������:������С��������Ұ�֣����
*/

//����
typedef struct EM_POINT_3D
{
	float x;
	float z;	
	float y;
}EM_POINT_3D, *PEM_POINT_3D;

//��Ӫ
enum EM_CAMP
{
	CAM_UNKNOW = 0,
	CAMP_BULE =100,
	CAMP_RED = 200,
	CAM_NEUTRAL = 300,
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

	//��ȡ����
	virtual char* GetName()const;

	//�ӿ�
	float GetCurHp()const;
	float GetMaxHp()const;
	float GetCurMp()const;
	float GetMaxMp()const;

	//��ȡ����
	EM_POINT_3D GetPoint()const;

	EM_CAMP GetCamp()const;

	DWORD GetType()const;

	//�Ƿ���ս�������� (true ��ʾ��)
	virtual bool BInShowInFag()const;

	//�Ƿ�����
	bool BDead()const;

	//��ȡ����
	float GetDistance(EM_POINT_3D* mon);

	//��ȡ���� ����ֵΪ ����
	EM_POINT_3D GetMonsterOrientation()const;

	//��ȡ�ƶ��ٶ�
	float GetMoveSpeed()const;

	//��ȡ����Ƿ��ƶ�
	bool GetBMoving()const;
};

