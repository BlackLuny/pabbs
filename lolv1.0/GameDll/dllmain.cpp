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
//��������
EM_SKILL_TO_MONS g_monsArry[5] = { 0 };
CHookToMainThread g_hk;
DWORD g_code = 0;
void UseSkillByindex(skill& sk, person& mons, person& ps)
{
	static bool BUseSkill = false;
	if (sk.GetSkillRange() > mons.GetDistance(&ps.GetPoint()) //���ܷ�Χ > ��Ҿ���
		&& sk.GetLevel() //���ܵȼ� > 0
		&& sk.bCoolDown() //�����Ѿ���ȴ
		&& ps.GetCurMp() > sk.GetExpendMP() //��ҵ�ǰMP > �������ĵ�MP
		&& !mons.BDead()  //�������
		&& !ps.BDead()    //��һ���
		&& mons.BVisableSee() //����ɼ�
		&& !BUseSkill
		)
	{
		utils::GetInstance()->log("TIPS: ��ʼʹ�ü��� %x ���� %x", sk.GetIndex(), mons.GetNodeBase());
		SKILL_TO_MONS temp;
		temp.index = (EM_SKILL_INDEX)sk.GetIndex();
		temp.monsObj = mons.GetNodeBase();
		g_hk.SendMessageToGame(MESSAGE::MSG_SKILLCALL, (LPARAM)(&temp));
		BUseSkill = true;
	}
	else
	{
		BUseSkill = false;
	}
}

void UseAttackAA2Mons(MonsterBase & mons, person& ps)
{
	auto dwZouAms = (DWORD)(((float)(1.5) / ps.GetAttackSpeed() )* ((float)(1.5) / ps.GetAttackSpeed()) * (float)1.5 *pSharedMemoryPointer->dwZouAMs);
	static DWORD timeSec = 0;
	static bool bAA = false;
	if (mons.GetNodeBase()
		&&!ps.BDead() 
		&&!mons.BDead() 
		&& ps.GetAttackRange() > ps.GetDistance(&mons.GetPoint()) 
		&&(float)(GetTickCount() - timeSec) >= ((float)(1.0) / ps.GetAttackSpeed())*1000.0
		&& mons.BVisableSee()
		&& !bAA)
	{
		utils::GetInstance()->log("TIPS: ��ʼ�չ��߼���\n");
		SKILL_TO_MONS temp;
		temp.monsObj = mons.GetNodeBase();
		g_hk.SendMessageToGame(MESSAGE::MSG_ATTACKCALL, (LPARAM)(&temp));
		timeSec = GetTickCount();
		Sleep(dwZouAms);
		bAA = true;
	}
	else
	{
		g_hk.SendMessageToGame(MESSAGE::MSG_FINDWAY, NULL);
		bAA = false;
	}
}

bool UseSkill(DWORD code)
{
	if ('Q' == code && pSharedMemoryPointer->bLockQ && pSharedMemoryPointer->VirtualKeyQ == code)
	{
		UseSkillByindex(skill(EM_SKILL_INDEX::Q, g_monsArry[0].skillObj), person(g_monsArry[0].monsObj), person(g_monsArry[0].roleObj));
		return true;
	}

	if ('W' == code && pSharedMemoryPointer->bLockW && pSharedMemoryPointer->VirtualKeyW == code)
	{
		UseSkillByindex(skill(EM_SKILL_INDEX::W, g_monsArry[1].skillObj), person(g_monsArry[1].monsObj), person(g_monsArry[1].roleObj));
		return true;
	}

	if ('E' == code && pSharedMemoryPointer->bLockE && pSharedMemoryPointer->VirtualKeyE == code)
	{
		UseSkillByindex(skill(EM_SKILL_INDEX::E, g_monsArry[2].skillObj), person(g_monsArry[2].monsObj), person(g_monsArry[2].roleObj));
		return true;
	}

	if ('R' == code && pSharedMemoryPointer->bLockR && pSharedMemoryPointer->VirtualKeyR == code)
	{
		UseSkillByindex(skill(EM_SKILL_INDEX::R, g_monsArry[3].skillObj), person(g_monsArry[3].monsObj), person(g_monsArry[3].roleObj));
		return true;
	}
	return false;
}

BOOL APIENTRY DllMain(HMODULE hModule,
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
	VMProtectBegin("ThreadProc");
	std::shared_ptr<ShareMemory<SHARED_MEMORY>> m_pSharedMemory(new ShareMemory<SHARED_MEMORY>(MAP_NAME));
	if (!m_pSharedMemory->openShareMemory())
	{
		return 0;
	}
	pSharedMemoryPointer = m_pSharedMemory->GetPointerOfFile();
	//�ж��Ƿ������Ϸ
	while ((DWORD)GameCall::GetInstance()->GetClientTickTime() < 1 || utils::GetInstance()->read<DWORD>(pSharedMemoryPointer->Base_RoleSelfAddr) < 1)
	{
		Sleep(3000);
	}
	
	if (!g_hk.Hook())
	{
		return false;
	}

	if (!GameCall::GetInstance()->HookSkillUse())
	{
		return 0;
	}
	VMProtectEnd();
	//������Ҷ���

	utils::GetInstance()->log("TIPS: �����ɹ���\n");


	 person m_role(utils::GetInstance()->read<DWORD>(pSharedMemoryPointer->Base_RoleSelfAddr));
	 CSkillServices m_roleSkill(m_role.GetNodeBase());
	 CBufferServices m_roleBuff(m_role.GetNodeBase());
	CMonsterServices cm;
	while (true)
	{
 		//����Q
		cm.travse(m_role);
 		if (pSharedMemoryPointer->bLockQ)
 		{
			auto skillQ = m_roleSkill.GetSkillObjectByIndex(0);
 			if (pSharedMemoryPointer->VirtualKeyQ == 'Q')
			{
 				g_monsArry[0].skillObj = skillQ.GetNodeBase();
 				g_monsArry[0].monsObj = cm.GetHealthLeastPerson(m_role, skillQ.GetSkillRange()).GetNodeBase();
 				g_monsArry[0].roleObj = m_role.GetNodeBase();
 			}
 			else
 			{
 				if (GetAsyncKeyState(pSharedMemoryPointer->VirtualKeyQ) & 0x8000)
 				{
					auto mons = cm.GetHealthLeastPerson(m_role, skillQ.GetSkillRange());
 					UseSkillByindex(skillQ, mons, m_role);
 				}
 			}
 		}
 		//����W
 		if ( pSharedMemoryPointer->bLockW)
		{
			auto skillQ = m_roleSkill.GetSkillObjectByIndex(1);
 			if (pSharedMemoryPointer->VirtualKeyW == 'W')
 			{
 				g_monsArry[1].skillObj = skillQ.GetNodeBase();
 				g_monsArry[1].monsObj = cm.GetHealthLeastPerson(m_role, skillQ.GetSkillRange()).GetNodeBase();
 				g_monsArry[1].roleObj = m_role.GetNodeBase();
 			}
 			else
 			{
 				if (GetAsyncKeyState(pSharedMemoryPointer->VirtualKeyW) & 0x8000)
 				{
					auto mons = cm.GetHealthLeastPerson(m_role, skillQ.GetSkillRange());
 					UseSkillByindex(skillQ, mons, m_role);
 				}
 			}
 		}
 		//����E
 		if (pSharedMemoryPointer->bLockE)
 		{
			auto skillQ = m_roleSkill.GetSkillObjectByIndex(2);
 			if (pSharedMemoryPointer->VirtualKeyE == 'E')
			{
 				g_monsArry[2].skillObj = skillQ.GetNodeBase();
 				g_monsArry[2].monsObj = cm.GetHealthLeastPerson(m_role, skillQ.GetSkillRange()).GetNodeBase();
 				g_monsArry[2].roleObj = m_role.GetNodeBase();
 			}
 			else
 			{
 				if (GetAsyncKeyState(pSharedMemoryPointer->VirtualKeyE) & 0x8000)
 				{
					auto mons = cm.GetHealthLeastPerson(m_role, skillQ.GetSkillRange());
 					UseSkillByindex(skillQ, mons, m_role);
 				}
 			}
 		}
 		//����R
 		if (pSharedMemoryPointer->bLockR)
 		{
			auto skillQ = m_roleSkill.GetSkillObjectByIndex(3);
 			if (pSharedMemoryPointer->VirtualKeyR == 'R')
 			{
 				g_monsArry[3].skillObj = skillQ.GetNodeBase();
 				g_monsArry[3].monsObj = cm.GetHealthLeastPerson(m_role , skillQ.GetSkillRange()).GetNodeBase();
 				g_monsArry[3].roleObj = m_role.GetNodeBase();
 			}
 			else
 			{
 				if (GetAsyncKeyState(pSharedMemoryPointer->VirtualKeyR) & 0x8000)
 				{
					auto mons = cm.GetHealthLeastPerson(m_role, m_role.GetAttackRange());
 					UseSkillByindex(skillQ, mons, m_role);
 				}
 			}
 		}
		//��A
		if (pSharedMemoryPointer->bOpenAA && GetAsyncKeyState(pSharedMemoryPointer->VirtualKeyAA)& 0x8000)
		{
			auto mons = cm.GetHealthLeastPerson(m_role, m_role.GetAttackRange());
			UseAttackAA2Mons(mons, m_role);
		}


		//����
		if (pSharedMemoryPointer->bOpenClearAA && GetAsyncKeyState(pSharedMemoryPointer->VirtualKeyOpenClear) & 0x8000)
		{
			//��ȡ��Χ�������С��
			auto mons = cm.GetHealthLeastMons(m_role, m_role.GetAttackRange());
			UseAttackAA2Mons(mons, m_role);

		}

 		//��ο����Զ� ���� ����
 		if (true)
 		{
 			//������Χ��Һ͹���
 			auto perList = cm.GetPersonList();
 			for (auto temp : perList)
 			{
 				utils::GetInstance()->log("TIPS: MONS OBJ = %x", temp.GetNodeBase());
 				//����������ϵ�buff
 				CBufferServices cbf(temp.GetNodeBase());
 				cbf.travse();
 
 				//���buff���� == ����Ь��E  && �����ܻ����˺� + ��ҹ�����* ���ܼӳɱ����� > ��ǰ�����Ѫ��  ʹ�� E
 			}
 
 			//�����Χ��� ���߹������� ì������ * �����˺� >  ���ﵱǰѪ��  ʹ�� ����E �ձ� 
 		}


		Sleep(20);
	}

	return 0;
}

