// dllmain.cpp : ���� DLL Ӧ�ó������ڵ㡣
#include "stdafx.h"
#include "dllmain.h"
#include "SkillServices.h"
#include "BufferServices.h"
#include "EquipmentServices.h"
#include "MonsterServices.h"
#include "BaseAddr.h"
#include "CShareStruct.h"
#include "ShareMemory.h"
#include "GameCall.h"
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH: {
		::CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(ThreadProc), NULL, NULL, NULL);
		break;
	}
	case DLL_THREAD_ATTACH: {
		break;
	}
	case DLL_THREAD_DETACH: {
		break;
	}
	case DLL_PROCESS_DETACH: {
		break;
	}
	}
	return TRUE;
}

DWORD WINAPI ThreadProc(_In_ LPVOID lpParameter)
{
	CMonsterServices cm;

	
	//�ж��Ƿ������Ϸ
	while ((DWORD)GameCall::GetInstance()->GetClientTickTime() < 1 || utils::GetInstance()->read<DWORD>(Base_RoleSelfAddr) < 1)
	{
		Sleep(3000);
	}
	//HOOK����CALL
	if (!GameCall::GetInstance()->HookSkillUse())
	{
		utils::GetInstance()->log("ERROR: ameCall::GetInstance()->HookSkillUse()ʧ�ܣ�");
		return 0;
	}

	//���������ڴ�
	std::shared_ptr<ShareMemory<SHARED_MEMORY>> m_pSharedMemory(new ShareMemory<SHARED_MEMORY>(MAP_NAME));
	if (!m_pSharedMemory->openShareMemory())
	{
		utils::GetInstance()->log("ERROR: m_pSharedMemory->openShareMemory()���ִ���\n");
		return 0;
	}
	auto pSharedMemoryPointer = m_pSharedMemory->GetPointerOfFile();


	//������Ҷ���
	auto BasePlayerObj = utils::GetInstance()->read<DWORD>(Base_RoleSelfAddr);
	if (BasePlayerObj < 1)
	{
		utils::GetInstance()->log("ERROR: utils::GetInstance()->read<DWORD>(Base_RoleSelfAddr)���ִ���\n");
		return 0;
	}
	//��Ҷ���
	person m_role(BasePlayerObj);
	CSkillServices m_roleSkill(BasePlayerObj);

	utils::GetInstance()->log("TIPS: �����ɹ���\n");
	while (true)
	{
		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			
			auto mons = cm.GetNearleastPerson();
			//��������˼���Q
			if (pSharedMemoryPointer->bLockQ)
			{
				auto skillQ = m_roleSkill.GetSkillObjectByIndex(0);
				//��� (�����ҵľ��� < ����Q�ľ��� && ��ҵ�ǰ���� > �������ĵ��� && �����Ѿ�ѧϰ && �����Ѿ���ȴ && ��һ���)  �͵��� ������CALL��Q������
				if (m_role.GetDistance(dynamic_cast<MonsterBase*>(&mons)) < skillQ.GetSkillRange() && 
					skillQ.GetLevel() > 0 && 
					m_role.GetCurMp() > skillQ.GetExpendMP()&&
					!m_role.BDead() &&
					skillQ.bCoolDown())
				{
					utils::GetInstance()->log("TIPS: ��ǰ��������:%s ʹ�ü���Q��", Utf8ToAnsi(mons.GetName()));
					GameCall::GetInstance()->UseSkill(0, mons.GetNodeBase());
					Sleep(10);
				}
			}
			if (pSharedMemoryPointer->bLockW)
			{
				auto skillQ = m_roleSkill.GetSkillObjectByIndex(1);
				//��� (�����ҵľ��� < ����Q�ľ��� && ��ҵ�ǰ���� > �������ĵ��� && �����Ѿ�ѧϰ && �����Ѿ���ȴ && ��һ���) && ���˿ɼ� �͵��� ������CALL��Q������
				if (m_role.GetDistance(dynamic_cast<MonsterBase*>(&mons)) < skillQ.GetSkillRange() &&
					skillQ.GetLevel() > 0 &&
					m_role.GetCurMp() > skillQ.GetExpendMP() &&
					!m_role.BDead() &&
					skillQ.bCoolDown())
				{
					utils::GetInstance()->log("TIPS: ��ǰ��������:%s ʹ�ü���W��", Utf8ToAnsi(mons.GetName()));
					GameCall::GetInstance()->UseSkill(1, mons.GetNodeBase());
					Sleep(10);
				}
			}
			if (pSharedMemoryPointer->bLockE)
			{
				auto skillQ = m_roleSkill.GetSkillObjectByIndex(2);
				//��� (�����ҵľ��� < ����Q�ľ��� && ��ҵ�ǰ���� > �������ĵ��� && �����Ѿ�ѧϰ && �����Ѿ���ȴ && ��һ���)  �͵��� ������CALL��Q������
				if (m_role.GetDistance(dynamic_cast<MonsterBase*>(&mons)) < skillQ.GetSkillRange() &&
					skillQ.GetLevel() > 0 &&
					m_role.GetCurMp() > skillQ.GetExpendMP() &&
					!m_role.BDead() &&
					skillQ.bCoolDown())
				{
					utils::GetInstance()->log("TIPS: ��ǰ��������:%s ʹ�ü���E��", Utf8ToAnsi(mons.GetName()));
					GameCall::GetInstance()->UseSkill(2, mons.GetNodeBase());
					Sleep(10);
				}
			}
			if (pSharedMemoryPointer->bLockR)
			{
				auto skillQ = m_roleSkill.GetSkillObjectByIndex(3);
				//��� (�����ҵľ��� < ����Q�ľ��� && ��ҵ�ǰ���� > �������ĵ��� && �����Ѿ�ѧϰ && �����Ѿ���ȴ && ��һ���)  �͵��� ������CALL��Q������
				if (m_role.GetDistance(dynamic_cast<MonsterBase*>(&mons)) < skillQ.GetSkillRange() &&
					skillQ.GetLevel() > 0 &&
					m_role.GetCurMp() > skillQ.GetExpendMP() &&
					!m_role.BDead() &&
					skillQ.bCoolDown())
				{
					utils::GetInstance()->log("TIPS: ��ǰ��������:%s ʹ�ü���R��", Utf8ToAnsi(mons.GetName()));
					GameCall::GetInstance()->UseSkill(3, mons.GetNodeBase());
					Sleep(10);
				}
			}

			//���������A
			//��� �������ҵľ��� < �������� && ��ʱ > ��A��ʱ�� �͵��� Ѱ·�������λ�ã� �� ������ͨ����CALL
		}

		Sleep(50);
	}

	return 0;
}

