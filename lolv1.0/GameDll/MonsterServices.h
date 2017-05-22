#pragma once
#include <vector>
#include "person.h"
#include <memory>
class CMonsterServices
{
public:
	CMonsterServices();
	~CMonsterServices();

	void travse(person& role);
	//��ȡ����Ĺ���
	person GetNearleastPerson(person& role);
	//��ȡѪ����͵Ĺ���
	person GetHealthLeastPerson(person& role, float Distance);

	//��ȡ��ǰ��Χ�������С��
	MonsterBase GetHealthLeastMons(person& role, float Dis);
	//��ȡ����б�
	std::vector<person>& GetPersonList();

	//��ȡС���б�
	std::vector<MonsterBase>& GetMonsList();
private:
	//����б�
	std::vector<person> m_PersonList;
	//С��Ұ���б�
	std::vector<MonsterBase> m_monsList;
};

