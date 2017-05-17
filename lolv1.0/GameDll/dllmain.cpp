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
void UseSkillByindex(skill& sk, person& mons, person& ps)
{
	if (sk.GetSkillRange() > mons.GetDistance(&ps.GetPoint()) //���ܷ�Χ > ��Ҿ���
		&& sk.GetLevel() //���ܵȼ� > 0
		&& sk.bCoolDown() //�����Ѿ���ȴ
		&& ps.GetCurMp() > sk.GetExpendMP() //��ҵ�ǰMP > �������ĵ�MP
		&& !mons.BDead()  //�������
		&& !ps.BDead()    //��һ���
		&& mons.BVisableSee() //����ɼ�
		)
	{
		utils::GetInstance()->log("TIPS: ��ʼʹ�ü��� %x ���� %x", sk.GetIndex(), mons.GetNodeBase());
		SKILL_TO_MONS temp;
		temp.index = (EM_SKILL_INDEX)sk.GetIndex();
		temp.monsObj = mons.GetNodeBase();
		g_hk.SendMessageToGame(MESSAGE::MSG_SKILLCALL, (LPARAM)(&temp));
		Sleep(3);
	}
}

void UseAttackAA2Mons(person & mons, person& ps)
{
	auto dwZouAms = (DWORD)(((float)(1.0) / ps.GetAttackSpeed())*210.0);
	pSharedMemoryPointer->dwZouAMs = dwZouAms/* > 360 ? 360 : dwZouAms*/;
	static DWORD m_AttackDisTime = 0;
	static DWORD timeSec = 0;
	if (mons.GetNodeBase()
		&&!ps.BDead() 
		&&!mons.BDead() 
		&& ps.GetAttackRange() > ps.GetDistance(&mons.GetPoint()) 
		&&(float)(GetTickCount() - timeSec) >= ((float)(1.05) / ps.GetAttackSpeed())*1000.0
		&& mons.BVisableSee())
	{
		utils::GetInstance()->log("TIPS: ��ʼ�չ��߼���\n");
		SKILL_TO_MONS temp;
		temp.monsObj = mons.GetNodeBase();
		g_hk.SendMessageToGame(MESSAGE::MSG_ATTACKCALL, (LPARAM)(&temp));
		timeSec = GetTickCount();
		m_AttackDisTime = GetTickCount();
	}
	else
	{
		utils::GetInstance()->log("TIPS: ����Ѱ·�߼���\n");
		if ((GetTickCount() - m_AttackDisTime) >= pSharedMemoryPointer->dwZouAMs)
		{
			utils::GetInstance()->log("TIPS: ��ʼѰ·�߼���\n");
			g_hk.SendMessageToGame(MESSAGE::MSG_FINDWAY, NULL);
		}
	}
}

void UseSkill(DWORD code)
{

	if (code == pSharedMemoryPointer->VirtualKeyQ && pSharedMemoryPointer->bLockQ)
	{
		//UseSkillByindex(skill(EM_SKILL_INDEX::Q ,g_monsArry[0].skillObj), person(g_monsArry[0].monsObj), person(g_monsArry[0].roleObj));
		SKILL_TO_MONS temp;
		temp.index = EM_SKILL_INDEX::Q;
		temp.monsObj = person(g_monsArry[0].monsObj).GetNodeBase();
		g_hk.SendMessageToGame(MESSAGE::MSG_SKILLCALL, (LPARAM)(&temp));
	}

	if (code == pSharedMemoryPointer->VirtualKeyW && pSharedMemoryPointer->bLockW)
	{
		//UseSkillByindex(skill(EM_SKILL_INDEX::W, g_monsArry[1].skillObj), person(g_monsArry[1].monsObj), person(g_monsArry[1].roleObj));
		SKILL_TO_MONS temp;
		temp.index = EM_SKILL_INDEX::W;
		temp.monsObj = person(g_monsArry[1].monsObj).GetNodeBase();
		g_hk.SendMessageToGame(MESSAGE::MSG_SKILLCALL, (LPARAM)(&temp));
	}

	if (code == pSharedMemoryPointer->VirtualKeyE && pSharedMemoryPointer->bLockE)
	{
		//UseSkillByindex(skill(EM_SKILL_INDEX::E, g_monsArry[2].skillObj), person(g_monsArry[2].monsObj), person(g_monsArry[2].roleObj));
		SKILL_TO_MONS temp;
		temp.index = EM_SKILL_INDEX::E;
		temp.monsObj = person(g_monsArry[2].monsObj).GetNodeBase();
		g_hk.SendMessageToGame(MESSAGE::MSG_SKILLCALL, (LPARAM)(&temp));
	}

	if (code == pSharedMemoryPointer->VirtualKeyR && pSharedMemoryPointer->bLockR)
	{
		//UseSkillByindex(skill(EM_SKILL_INDEX::R, g_monsArry[3].skillObj), person(g_monsArry[3].monsObj), person(g_monsArry[3].roleObj));
		SKILL_TO_MONS temp;
		temp.index = EM_SKILL_INDEX::R;
		temp.monsObj = person(g_monsArry[3].monsObj).GetNodeBase();
		g_hk.SendMessageToGame(MESSAGE::MSG_SKILLCALL, (LPARAM)(&temp));
	}

// 	if (code == pSharedMemoryPointer->VirtualKeyAA && pSharedMemoryPointer->bOpenAA)
// 	{
// 		UseAttackAA2Mons(person(g_monsArry[4].monsObj), person(g_monsArry[3].roleObj));
// 	}
	Sleep(3);
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

	 CSkillServices m_roleSkill(utils::GetInstance()->read<DWORD>(pSharedMemoryPointer->Base_RoleSelfAddr));
	 person m_role(utils::GetInstance()->read<DWORD>(pSharedMemoryPointer->Base_RoleSelfAddr));


	CMonsterServices cm;

	while (true)
	{
		auto skillQ = m_roleSkill.GetSkillObjectByIndex(0);
		g_monsArry[0].skillObj = skillQ.GetNodeBase();
		g_monsArry[0].monsObj = cm.GetHealthLeastPerson(&m_role, skillQ.GetSkillRange()).GetNodeBase();
		g_monsArry[0].roleObj = m_role.GetNodeBase();

		auto skillW = m_roleSkill.GetSkillObjectByIndex(1);
		g_monsArry[1].skillObj = skillW.GetNodeBase();
		g_monsArry[1].monsObj = cm.GetHealthLeastPerson(&m_role, skillW.GetSkillRange()).GetNodeBase();
		g_monsArry[1].roleObj = m_role.GetNodeBase();

		auto skillE= m_roleSkill.GetSkillObjectByIndex(2);
		g_monsArry[2].skillObj = skillE.GetNodeBase();
		g_monsArry[2].monsObj = cm.GetHealthLeastPerson(&m_role, skillE.GetSkillRange()).GetNodeBase();
		g_monsArry[2].roleObj = m_role.GetNodeBase();

		auto skillR = m_roleSkill.GetSkillObjectByIndex(3);
		g_monsArry[3].skillObj = skillR.GetNodeBase();
		g_monsArry[3].monsObj = cm.GetHealthLeastPerson(&m_role, skillR.GetSkillRange()).GetNodeBase();
		g_monsArry[3].roleObj = m_role.GetNodeBase();

		//g_monsArry[4].skillObj = 0;
		//g_monsArry[4].monsObj = cm.GetHealthLeastPerson(&m_role, m_role.GetAttackRange()).GetNodeBase();
		//g_monsArry[4].roleObj = m_role.GetNodeBase();

		if (pSharedMemoryPointer->bOpenAA && GetAsyncKeyState(pSharedMemoryPointer->VirtualKeyAA)& 0x8000)
		{
			auto mons = cm.GetHealthLeastPerson(&m_role, m_role.GetAttackRange());
			UseAttackAA2Mons(mons, m_role);
		}


		Sleep(3);
	}

	return 0;
}

