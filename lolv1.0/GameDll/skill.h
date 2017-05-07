#pragma once
#include "base.h"

enum EM_SKILL_INDEX
{
	Q,
	W,
	E,
	R,
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
	//��ȡ��������
	DWORD GetIndex()const;
private:
	EM_SKILL_INDEX m_index;
};

