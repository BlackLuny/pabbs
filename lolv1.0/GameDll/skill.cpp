#include "stdafx.h"
#include "skill.h"
#include "GameCall.h"
skill::skill(EM_SKILL_INDEX _index, DWORD dwNodeBase) :base(dwNodeBase), m_index(_index)
{

}

skill::~skill()
{
}

char* skill::GetName() const
{
	__try {
		auto temp = utils::GetInstance()->read<DWORD>(GetNodeBase() + pSharedMemoryPointer->Base_SkillOffset_Object);
		if (temp == 0)
		{
			return nullptr;
		}
		//�����ֻ�������ָ��
		if (utils::GetInstance()->read<DWORD>(temp +0x2c) <= 0x10)
		{
			return (char*)(temp + 0x18);
		}
		else
		{
			auto nameptr = utils::GetInstance()->read<DWORD>(temp + 0x18);
			return ((char*)nameptr);
		}
		
	}
	__except (1) {
		utils::GetInstance()->log("ERROR: skill::GetName()�쳣��\n");
		return nullptr;
	}
}

DWORD skill::GetLevel() const
{
	__try
	{
		return utils::GetInstance()->read<DWORD>(GetNodeBase() + 0x10);
	}
	__except(1)
	{
		utils::GetInstance()->log("ERROR: skill::GetLevel() �����쳣��\n");
		return 0;
	}
}

bool skill::bCoolDown()
{
	__try {
		return (GameCall::GetInstance()->GetClientTickTime() >= utils::GetInstance()->read<float>(GetNodeBase() + 0x18));
	}
	__except (1)
	{
		utils::GetInstance()->log("ERROR: skill::bCoolDown() �����쳣��\n");
		return false;
	}
}

//bool skill::bCouldUse()
//{
//	//���ܿ��õ�����Ϊ �ȼ� > 0  && ��ȴ && ��ǰ�� > �������ĵ���
//	return GetLevel() > 0 && bCoolDown();
//}

float skill::GetExpendMP()
{
	__try {
		auto temp = utils::GetInstance()->read<DWORD>(GetNodeBase() + pSharedMemoryPointer->Base_SkillOffset_Object);
		if (temp == 0) {
			utils::GetInstance()->log("ERROR: ��ȡGetExpendMPƫ��1ʧ�ܣ�\n");
			return 0;
		}
		auto temp2 = utils::GetInstance()->read<DWORD>(temp + 0x34);
		if (temp2 == 0)
		{
			utils::GetInstance()->log("ERROR: ��ȡGetExpendMPƫ��2ʧ�ܣ�\n");
			return 0;
		}
		return utils::GetInstance()->read<float>(temp2 + pSharedMemoryPointer->Base_SkillOffset_MP + (GetLevel() - 1) * 4);
	}
	__except (1)
	{
		utils::GetInstance()->log("ERORR: skill::GetExpendMP()�����쳣��\n");
		return 0;
	}
}

float skill::GetMaxCoolTime()
{
	__try {
		return 0;
		//return utils::GetInstance()->read<float>(GetNodeBase() + 0x44);
	}
	__except (1) {
		utils::GetInstance()->log("ERROR: skill::GetMaxCoolTime()!\n");
		return 0;
	}
}

float skill::GetSkillRange()
{
	__try {
		auto temp = utils::GetInstance()->read<DWORD>(GetNodeBase() + pSharedMemoryPointer->Base_SkillOffset_Object);
		if (temp == 0) {
			utils::GetInstance()->log("ERROR: ��ȡGetSkillRangeƫ��1ʧ�ܣ�\n");
			return 0;
		}
		auto temp2 = utils::GetInstance()->read<DWORD>(temp + 0x34);
		if (temp2 == 0)
		{
			utils::GetInstance()->log("ERROR: ��ȡGetSkillRangeƫ��2ʧ�ܣ�\n");
			return 0;
		}
		auto range1= utils::GetInstance()->read<float>(temp2 + pSharedMemoryPointer->Base_SkillOffset_Range1 + 4 * 1);
		auto range2 = utils::GetInstance()->read<float>(temp2 + pSharedMemoryPointer->Base_SkillOffset_Range2 + 1 * 4);
		if (range2 < 1)
		{
			return range1;
		}
		else
		{
			return (range1 < range2 ? range1: range2);
		}
	}
	__except (1) {
		utils::GetInstance()->log("ERROR: skill::GetSkillRange()�����쳣��\n");
		return 0;
	}
}

DWORD skill::GetIndex() const
{
	return m_index;
}
