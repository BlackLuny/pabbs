#include "stdafx.h"
#include "base.h"
base::base(_In_ DWORD dwNodeBase): m_nodeBase(dwNodeBase)
{
}

base::~base()
{

}

DWORD base::GetNodeBase() const
{
	return m_nodeBase;
}

char* base::GetName() const
{
	//��ȡ�����ֵ�ָ���ַ
	__try {
		auto temp = utils::GetInstance()->read<DWORD>(GetNodeBase() + 0x20);
		return (char*)(temp);
	}
	__except (1)
	{
		utils::GetInstance()->log("ERROR: base::GetName() �쳣��\n");
		return nullptr;
	}
}
