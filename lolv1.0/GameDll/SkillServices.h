#pragma once
#include <vector>
#include "skill.h"
class CSkillServices
{
public:
	CSkillServices(DWORD dwObjectBase);
	~CSkillServices();

	//完成对象的遍历
	void travse();
private:
	std::vector<skill> m_skillList;
	DWORD m_dwObjectBase;
};

