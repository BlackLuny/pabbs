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
	//��ȡ����Ĺ���
	person GetNearleastPerson(person* role);
	//��ȡѪ����͵Ĺ���
	person GetHealthLeastPerson(person* role, float Distance);
private:
	//����б�
	std::vector<person> m_PersonList;
};

