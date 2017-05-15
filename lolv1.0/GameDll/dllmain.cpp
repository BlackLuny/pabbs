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
#include <ctime>
SHARED_MEMORY* pSharedMemoryPointer = nullptr;
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
	VMProtectBegin("ssss");
	utils::GetInstance()->log("TIPS: Base_GameStartTime");
	//���������ڴ�
	std::shared_ptr<ShareMemory<SHARED_MEMORY>> m_pSharedMemory(new ShareMemory<SHARED_MEMORY>(MAP_NAME));
	if (!m_pSharedMemory->openShareMemory())
	{
		utils::GetInstance()->log("ERROR: m_pSharedMemory->openShareMemory()���ִ���\n");
		return 0;
	}
	pSharedMemoryPointer = m_pSharedMemory->GetPointerOfFile();
	utils::GetInstance()->log("TIPS: Base_GameStartTime = %x", pSharedMemoryPointer->Base_GameStartTime);
	//��������
	CMonsterServices cm;
	CHookToMainThread hk;

	//�ж��Ƿ������Ϸ
	while ((DWORD)GameCall::GetInstance()->GetClientTickTime() < 1 || utils::GetInstance()->read<DWORD>(pSharedMemoryPointer->Base_RoleSelfAddr) < 1)
	{
		utils::GetInstance()->log("TIPS: �ȴ��У� %f %x", GameCall::GetInstance()->GetClientTickTime(), pSharedMemoryPointer->Base_RoleSelfAddr);
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

	VMProtectEnd();
	//������Ҷ���
	CSkillServices m_roleSkill(utils::GetInstance()->read<DWORD>(pSharedMemoryPointer->Base_RoleSelfAddr));
	
	utils::GetInstance()->log("TIPS: �����ɹ���\n");
	while (true)
	{
		
		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			person m_role(utils::GetInstance()->read<DWORD>(pSharedMemoryPointer->Base_RoleSelfAddr));
			
			if (pSharedMemoryPointer->bLockQ)
			{
				auto skillQ = m_roleSkill.GetSkillObjectByIndex(0);
				auto mons = cm.GetHealthLeastPerson(&m_role, skillQ.GetSkillRange());
				utils::GetInstance()->log("TIPS: ��ǰ��Һ͹���ľ��룺 %f ", m_role.GetDistance(&mons.GetPoint()));
				if (m_role.GetDistance(&mons.GetPoint()) <= skillQ.GetSkillRange() &&
					skillQ.GetLevel() > 0 && skillQ.bCoolDown()&&
					m_role.GetCurMp() > skillQ.GetExpendMP()&&
					!m_role.BDead() && !mons.BDead() &&
					mons.GetNodeBase()&& mons.BVisableSee())
				{
					utils::GetInstance()->log("TIPS: ��ʼ����Q��\n");
					SKILL_TO_MONS temp;
					temp.index = EM_SKILL_INDEX::Q;
					temp.monsObj = mons.GetNodeBase();
					hk.SendMessageToGame(MESSAGE::MSG_SKILLCALL, (LPARAM)(&temp));
				}
			}

		    if (pSharedMemoryPointer->bLockW)
			{
				auto skillQ = m_roleSkill.GetSkillObjectByIndex(1);
				auto mons = cm.GetHealthLeastPerson(&m_role, skillQ.GetSkillRange());
				utils::GetInstance()->log("TIPS: ��ǰ��Һ͹���ľ��룺 %f ", m_role.GetDistance(&mons.GetPoint()));
				if (m_role.GetDistance(&mons.GetPoint()) <= skillQ.GetSkillRange() &&
					skillQ.GetLevel() > 0 &&
					m_role.GetCurMp() > skillQ.GetExpendMP() &&
					!m_role.BDead() &&
					skillQ.bCoolDown()&&
					mons.GetNodeBase()&&
					!mons.BDead() && mons.BVisableSee())
				{
					utils::GetInstance()->log("TIPS: ��ʼ����W��\n");
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
				utils::GetInstance()->log("TIPS: ��ǰ��Һ͹���ľ��룺 %f ", m_role.GetDistance(&mons.GetPoint()));
				if (m_role.GetDistance(&mons.GetPoint()) <= skillQ.GetSkillRange() &&
					skillQ.GetLevel() > 0 &&
					m_role.GetCurMp() > skillQ.GetExpendMP() &&
					!m_role.BDead() &&
					skillQ.bCoolDown()&&
					mons.GetNodeBase()&&
					!mons.BDead()&& mons.BVisableSee())
				{
					utils::GetInstance()->log("TIPS: ��ʼ����E��\n");
					SKILL_TO_MONS temp;
					temp.index = EM_SKILL_INDEX::E;
					temp.monsObj = mons.GetNodeBase();
					hk.SendMessageToGame(MESSAGE::MSG_SKILLCALL, (LPARAM)(&temp));
				}
		 }

		 if (pSharedMemoryPointer->bLockR)
		 {
			 auto skillQ = m_roleSkill.GetSkillObjectByIndex(3);
			 auto mons = cm.GetHealthLeastPerson(&m_role, skillQ.GetSkillRange());
			 utils::GetInstance()->log("TIPS: ��ǰ��Һ͹���ľ��룺 %f ", m_role.GetDistance(&mons.GetPoint()));
			 if (m_role.GetDistance(&mons.GetPoint()) < skillQ.GetSkillRange() &&
				 skillQ.GetLevel() > 0 &&
				 m_role.GetCurMp() > skillQ.GetExpendMP() &&
				 !m_role.BDead() &&
				 skillQ.bCoolDown() &&
				 mons.GetNodeBase() &&
				 !mons.BDead()&& mons.BVisableSee())
			 {
				 SKILL_TO_MONS temp;
				 temp.index = EM_SKILL_INDEX::R;
				 temp.monsObj = mons.GetNodeBase();
				 hk.SendMessageToGame(MESSAGE::MSG_SKILLCALL, (LPARAM)(&temp));
			 }
		 }
			

			if (pSharedMemoryPointer->bOpenAA) 
			{
				auto dwZouAms = (DWORD)(((float)(1.0) / m_role.GetAttackSpeed())*220.0);
				m_pSharedMemory->GetPointerOfFile()->dwZouAMs = dwZouAms/* > 360 ? 360 : dwZouAms*/;
				static DWORD m_AttackDisTime = 0;
				static DWORD timeSec = 0;
				auto mons = cm.GetHealthLeastPerson(&m_role, m_role.GetAttackRange());
				utils::GetInstance()->log("TIPS: ��ǰ��Һ͹���ľ��룺 %f �������룺 %f ", m_role.GetDistance(&mons.GetPoint()), m_role.GetAttackRange());
				if (mons.GetNodeBase() && 
					!m_role.BDead()&&
					!mons.BDead()&&
					m_role.GetDistance(&mons.GetPoint()) <= m_role.GetAttackRange()&&
					(float)(GetTickCount() - timeSec) >= ((float)(1.05) / m_role.GetAttackSpeed())*1000.0
					&& mons.BVisableSee())
				{
					utils::GetInstance()->log("TIPS: ��ʼ�չ��߼���\n");
 					SKILL_TO_MONS temp;
 					temp.monsObj = mons.GetNodeBase();
 					hk.SendMessageToGame(MESSAGE::MSG_ATTACKCALL, (LPARAM)(&temp));
 					timeSec = GetTickCount();
 					m_AttackDisTime = GetTickCount();
				}
				else
				{
					utils::GetInstance()->log("TIPS: ����Ѱ·�߼���\n");
					if ((GetTickCount() - m_AttackDisTime) >= m_pSharedMemory->GetPointerOfFile()->dwZouAMs)
					{					
						utils::GetInstance()->log("TIPS: ��ʼѰ·�߼���\n");
						hk.SendMessageToGame(MESSAGE::MSG_FINDWAY, NULL);
					}
				}

			}

		}

		Sleep(3);
	}

	return 0;
}

