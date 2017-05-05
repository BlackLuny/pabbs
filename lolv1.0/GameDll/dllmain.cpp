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

	//HOOK����CALL
	if (!GameCall::GetInstance()->HookSkillUse())
	{
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
	if (BasePlayerObj == 0)
	{
		return 0;
	}

	//��Ҷ���
	person m_role(BasePlayerObj);
	CSkillServices m_roleSkill(BasePlayerObj);
	while (true)
	{
		//��A�ж�
		//��� �������ҵľ��� < �������� && ��ʱ > ��A��ʱ�� �͵��� Ѱ·�������λ�ã� �� ������ͨ����CALL

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
					GameCall::GetInstance()->UseSkill(0, mons.GetNodeBase());
				}
				else
				{
					utils::GetInstance()->log("TIPS: �����㼼��Qʹ������������Ĭ�ϵļ��ܣ�\n");
				}
			}
			if (pSharedMemoryPointer->bLockW)
			{
				auto skillQ = m_roleSkill.GetSkillObjectByIndex(1);
				//��� (�����ҵľ��� < ����Q�ľ��� && ��ҵ�ǰ���� > �������ĵ��� && �����Ѿ�ѧϰ && �����Ѿ���ȴ && ��һ���)  �͵��� ������CALL��Q������
				if (m_role.GetDistance(dynamic_cast<MonsterBase*>(&mons)) < skillQ.GetSkillRange() &&
					skillQ.GetLevel() > 0 &&
					m_role.GetCurMp() > skillQ.GetExpendMP() &&
					!m_role.BDead() &&
					skillQ.bCoolDown())
				{
					GameCall::GetInstance()->UseSkill(1, mons.GetNodeBase());
				}
				else
				{
					utils::GetInstance()->log("TIPS: �����㼼��Wʹ������������Ĭ�ϵļ��ܣ�\n");
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
					GameCall::GetInstance()->UseSkill(2, mons.GetNodeBase());
				}
				else
				{
					utils::GetInstance()->log("TIPS: �����㼼��Eʹ������������Ĭ�ϵļ��ܣ�\n");
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
					GameCall::GetInstance()->UseSkill(3, mons.GetNodeBase());
				}
				else
				{
					utils::GetInstance()->log("TIPS: �����㼼��Rʹ������������Ĭ�ϵļ��ܣ�\n");
				}
			}

		}

		Sleep(3);
	}

	return 0;
}

