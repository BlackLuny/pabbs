#include "stdafx.h"
#include "MonsterBase.h"
#include "BaseAddr.h"

MonsterBase::MonsterBase(DWORD dwNodeBase): base(dwNodeBase)
{

}


MonsterBase::~MonsterBase()
{
}

char* MonsterBase::GetName() const
{
	__try
	{
		auto stringSize = utils::GetInstance()->read<DWORD>(GetNodeBase() + 0x30);
		auto maxSize = utils::GetInstance()->read<DWORD>(GetNodeBase() + 0x34);
		if (stringSize < 0x10)
		{
			return (char*)(GetNodeBase() + 0x20);
		}
		else
		{
			return (char*)(utils::GetInstance()->read<DWORD>(GetNodeBase() + 0x20));
		}
	}
	__except (1) {
		return nullptr;
	}
}

float MonsterBase::GetCurHp() const
{
	__try {
		return utils::GetInstance()->read<float>(GetNodeBase() + Base_MonsterCurrentHpOffset);
	}
	__except (1)
	{
		utils::GetInstance()->log("ERROR: MonsterBase::GetCurHp() �����쳣��\n");
		return 0;
	}
}

float MonsterBase::GetMaxHp() const
{
	__try {
		return utils::GetInstance()->read<float>(GetNodeBase() + Base_MonsterCurrentHpOffset+0x10);
	}
	__except (1)
	{
		utils::GetInstance()->log("ERROR: MonsterBase::GetMaxHp() �����쳣��\n");
		return 0;
	}
}

float MonsterBase::GetCurMp() const
{
	__try {
		return utils::GetInstance()->read<float>(GetNodeBase() + Base_MonsterCurrentMpOffset);
	}
	__except (1)
	{
		utils::GetInstance()->log("ERROR: MonsterBase::GetCurMp() �����쳣��\n");
		return 0;
	}
}

float MonsterBase::GetMaxMp() const
{
	__try {
		return utils::GetInstance()->read<float>(GetNodeBase() + Base_MonsterCurrentMpOffset+0x10);
	}
	__except (1)
	{
		utils::GetInstance()->log("ERROR: MonsterBase::GetMaxMp() �����쳣��\n");
		return 0;
	}

}

EM_POINT_3D MonsterBase::GetPoint() const
{
	EM_POINT_3D temp = { 0 };
	__try
	{
		//��ȡ����
		temp.x = utils::GetInstance()->read<float>(GetNodeBase() + 0x50);
		temp.z = utils::GetInstance()->read<float>(GetNodeBase() + 0x54);
		temp.y = utils::GetInstance()->read<float>(GetNodeBase() + 0x58);
	}
	__except (1)
	{
		utils::GetInstance()->log("ERROR: MonsterBase::GetPoint() �����쳣��\n");
	}
	return temp;
}

EM_CAMP MonsterBase::GetCamp() const
{
	__try {
		return (EM_CAMP)utils::GetInstance()->read<DWORD>(GetNodeBase() + 0x14);
	}
	__except (1) {
		utils::GetInstance()->log("ERROR: MonsterBase::GetCamp()�����쳣��\n");
		return EM_CAMP::CAM_UNKNOW;
	}
}

DWORD MonsterBase::GetType() const
{
	__try {
		return utils::GetInstance()->read<DWORD>(GetNodeBase() + 0x18);
	}
	__except (1) {
		utils::GetInstance()->log("ERROR: MonsterBase::GetType()�����쳣��\n");
		return 0;
	}
}

bool MonsterBase::BInShowInFag() const
{
	return false;
}

bool MonsterBase::BDead() const
{
	__try {
		return utils::GetInstance()->read<bool>(GetNodeBase() + 0x10c);
	}
	__except (1)
	{
		utils::GetInstance()->log("ERROR: MonsterBase::BDead()�����쳣��\n");
		return false;
	}
}

float MonsterBase::GetDistance(EM_POINT_3D* mon)
{
	return sqrt((GetPoint().x - mon->x)*(GetPoint().x - mon->x) + (GetPoint().y - mon->y)*(GetPoint().y - mon->y));
}
