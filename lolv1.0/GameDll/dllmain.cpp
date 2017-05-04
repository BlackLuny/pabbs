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
	//CSkillServices cs(utils::GetInstance()->read<DWORD>(Base_RoleSelfAddr));
	//CBufferServices bf;
	//CEquipmentServices eq(utils::GetInstance()->read<DWORD>(Base_RoleSelfAddr));
	//CMonsterServices cm;

	//���������ڴ�
	std::shared_ptr<ShareMemory<SHARED_MEMORY>> m_pSharedMemory(new ShareMemory<SHARED_MEMORY>(MAP_NAME));
	if (!m_pSharedMemory->openShareMemory())
	{
		utils::GetInstance()->log("ERROR: m_pSharedMemory->openShareMemory()���ִ���\n");
		return 0;
	}
	auto pSharedMemoryPointer = m_pSharedMemory->GetPointerOfFile();

	while (true)
	{
		//��A�ж�
		//��� �������ҵľ��� < �������� && ��ʱ > ��A��ʱ�� �͵��� Ѱ·�������λ�ã� �� ������ͨ����CALL
		//�����ж�
		//��� (�����ҵľ��� < ����Q�ľ��� && ��ҵ�ǰ���� > �������ĵ��� && �����Ѿ�ѧϰ && �����Ѿ���ȴ) �͵��� ������CALL��Q������
		//��������ͬ��

		utils::GetInstance()->log("TIPS: q = %d w = %d e = %d r = %d",
			pSharedMemoryPointer->bLockQ,
			pSharedMemoryPointer->bLockW,
			pSharedMemoryPointer->bLockE, 
			pSharedMemoryPointer->bLockR);

		//�жϰ����Ƿ񱻰���
		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			
		}

		Sleep(3);
	}

	return 0;
}

