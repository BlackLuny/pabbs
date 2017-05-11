#pragma once
#include "base.h"

enum EM_SKILL_INDEX
{
	Q,
	W,
	E,
	R,
};


enum EM_SKILL_TYPE
{
	EM_LOCKING = 0x100, //��������
	EM_UNLOCKING,
	EM_UNKNOWN,
};

class skill :
	public base
{
public:
	skill(EM_SKILL_INDEX _index,DWORD dwNodeBase);
	~skill();
	//��ȡ��������
	virtual char* GetName() const;
	//��ȡ���ܵȼ�
	DWORD GetLevel()const;
	//�����Ƿ���ȴ
	bool bCoolDown();
	//�������ĵ�����
	float GetExpendMP();
	//���������ȴʱ��
	float GetMaxCoolTime();
	//��ȡ���ܷ�Χ
	float GetSkillRange();
	//��ȡ���ܷ�Χ1
	float GetSkillRange1();
	//��ȡ���ܷ�Χ2
	float GetSkillRange2();
	//��ȡ��������
	DWORD GetIndex()const;
	//��ȡ����Ƿ����������� ������������ܣ�������Ƿ�Χ
	float GetSkillType()const;
private:
	EM_SKILL_INDEX m_index;
};

