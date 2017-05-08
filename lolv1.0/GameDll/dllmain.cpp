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
#include "HookToMainThread.h"

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
	//��������
	CMonsterServices cm;
	CHookToMainThread hk;


	//�ж��Ƿ������Ϸ
	while ((DWORD)GameCall::GetInstance()->GetClientTickTime() < 1 || utils::GetInstance()->read<DWORD>(Base_RoleSelfAddr) < 1)
	{
		Sleep(3000);
	}

	if (!hk.Hook())
	{
		utils::GetInstance()->log("ERROR: ���ص���Ϸ���߳�ʧ��Ŷ��\n");
		return false;
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
	CSkillServices m_roleSkill(utils::GetInstance()->read<DWORD>(Base_RoleSelfAddr));

	utils::GetInstance()->log("TIPS: �����ɹ���\n");
	while (true)
	{
		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			person m_role(utils::GetInstance()->read<DWORD>(Base_RoleSelfAddr));
			//��������˼���Q
			if (pSharedMemoryPointer->bLockQ)
			{
				auto skillQ = m_roleSkill.GetSkillObjectByIndex(0);
				auto mons = cm.GetHealthLeastPerson(&m_role, skillQ.GetSkillRange());
				//��� (�����ҵľ��� < ����Q�ľ��� && ��ҵ�ǰ���� > �������ĵ��� && �����Ѿ�ѧϰ && �����Ѿ���ȴ && ��һ���)  �͵��� ������CALL��Q������
				if (m_role.GetDistance(&mons.GetPoint()) < skillQ.GetSkillRange() &&
					m_role.GetDistance(&mons.GetPoint()) >0 &&
					skillQ.GetLevel() > 0 && 
					m_role.GetCurMp() > skillQ.GetExpendMP()&&
					!m_role.BDead() &&
					skillQ.bCoolDown()&&
					mons.GetNodeBase()&&
					!mons.BDead())
				{
					SKILL_TO_MONS temp;
					temp.index = EM_SKILL_INDEX::Q;
					temp.monsObj = mons.GetNodeBase();
					hk.SendMessageToGame(MESSAGE::MSG_SKILLCALL, (LPARAM)(&temp));
				}
			}
			//��������˼���W
			if (pSharedMemoryPointer->bLockW)
			{
				auto skillQ = m_roleSkill.GetSkillObjectByIndex(1);
				auto mons = cm.GetHealthLeastPerson(&m_role, skillQ.GetSkillRange());
				if (m_role.GetDistance(&mons.GetPoint()) < skillQ.GetSkillRange() &&
					skillQ.GetLevel() > 0 &&
					m_role.GetDistance(&mons.GetPoint()) >0 &&
					m_role.GetCurMp() > skillQ.GetExpendMP() &&
					!m_role.BDead() &&
					skillQ.bCoolDown()&&
					mons.GetNodeBase()&&
					!mons.BDead())
				{
					SKILL_TO_MONS temp;
					temp.index = EM_SKILL_INDEX::W;
					temp.monsObj = mons.GetNodeBase();
					hk.SendMessageToGame(MESSAGE::MSG_SKILLCALL, (LPARAM)(&temp));
				}
			}
			if (pSharedMemoryPointer->bLockE)
			{
				auto skillQ = m_roleSkill.GetSkillObjectByIndex(2);
				auto mons = cm.GetHealthLeastPerson(&m_role, skillQ.GetSkillRange());
				if (m_role.GetDistance(&mons.GetPoint()) < skillQ.GetSkillRange() &&
					skillQ.GetLevel() > 0 &&
					m_role.GetDistance(&mons.GetPoint()) >0 &&
					m_role.GetCurMp() > skillQ.GetExpendMP() &&
					!m_role.BDead() &&
					skillQ.bCoolDown()&&
					mons.GetNodeBase()&&
					!mons.BDead())
				{
					SKILL_TO_MONS temp;
					temp.index = EM_SKILL_INDEX::E;
					temp.monsObj = mons.GetNodeBase();
					hk.SendMessageToGame(MESSAGE::MSG_SKILLCALL, (LPARAM)(&temp));
				}
			}
			
			if (pSharedMemoryPointer->bOpenAA)
			{
				//��ȡ����ҹ�����Χ�ڵ�Ѫ����͵Ĺ���
				auto mons = cm.GetHealthLeastPerson(&m_role, m_role.GetAttackRange());
				//�������
				static float timeSec = 0;
				//���������� > ������Ҫ������ && �������  && ��һ���
				if (mons.GetNodeBase() && 
					!m_role.BDead()&&
					!mons.BDead()&&
					m_role.GetDistance(&mons.GetPoint()) < m_role.GetAttackRange())
				{
					SKILL_TO_MONS temp;
					temp.monsObj = mons.GetNodeBase();
					if ((GameCall::GetInstance()->GetClientTickTime() - timeSec) > ((float)(1.1) / m_role.GetAttackSpeed()))
					{
						utils::GetInstance()->log("TIPS:��ǰʱ���Ϊ: %f", (GameCall::GetInstance()->GetClientTickTime() - timeSec));
						hk.SendMessageToGame(MESSAGE::MSG_ATTACKCALL, (LPARAM)(&temp));
						//���¼��㹥�����
						timeSec = GameCall::GetInstance()->GetClientTickTime(); //100
					}

				}
			}

		}

		//���������T & ���Զ��ͷ�R
		if (GetAsyncKeyState(0x54)&0x8000)
		{
			person m_role(utils::GetInstance()->read<DWORD>(Base_RoleSelfAddr));
			if (pSharedMemoryPointer->bLockR)
			{
				//auto mons = cm.GetNearleastPerson(&m_role);
				auto skillQ = m_roleSkill.GetSkillObjectByIndex(3);
				auto mons = cm.GetHealthLeastPerson(&m_role, skillQ.GetSkillRange());
				if (m_role.GetDistance(&mons.GetPoint()) < skillQ.GetSkillRange() &&
					m_role.GetDistance(&mons.GetPoint()) >0 &&
					skillQ.GetLevel() > 0 &&
					m_role.GetCurMp() > skillQ.GetExpendMP() &&
					!m_role.BDead() &&
					skillQ.bCoolDown()&&
					mons.GetNodeBase()&&
					!mons.BDead())
				{
					SKILL_TO_MONS temp;
					temp.index = EM_SKILL_INDEX::R;
					temp.monsObj = mons.GetNodeBase();
					hk.SendMessageToGame(MESSAGE::MSG_SKILLCALL, (LPARAM)(&temp));
				}
			}
		}

		Sleep(1);
	}

	return 0;
}

