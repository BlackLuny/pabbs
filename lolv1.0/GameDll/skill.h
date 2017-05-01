#pragma once
#include "base.h"
class skill :
	public base
{
public:
	skill(DWORD _index,DWORD dwNodeBase);
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
	DWORD m_index;
};

