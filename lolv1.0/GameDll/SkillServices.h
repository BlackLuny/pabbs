#pragma once
#include <vector>
#include "skill.h"
class CSkillServices
{
public:
	CSkillServices();
	~CSkillServices();

	//��ɶ���ı���
	void travse();
private:
	std::vector<skill> m_skillList;
};

