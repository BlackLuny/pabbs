#pragma once
#include <vector>
#include "person.h"
#include <memory>
class CMonsterServices
{
public:
	CMonsterServices();
	~CMonsterServices();

	void travse();
	void* GetNearleastPerson();
private:
	//����б�
	std::vector<person> m_PersonList;
	std::shared_ptr<person> m_role;
};

