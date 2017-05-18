#include "stdafx.h"
#include "HookToMainThread.h"
#include "utils.h"
#include "BaseAddr.h"
#include "GameCall.h"
#include "dllmain.h"
//�Զ�����Ϣ����
DWORD CHookToMainThread::m_msgCode = RegisterWindowMessage("MyMsgCodeEx");
HHOOK CHookToMainThread::m_hHook = { 0 };
LONG CHookToMainThread::m_hWndHook = { 0 };
HWND CHookToMainThread::GetGameHwnd() const
{
	__try
	{
		return  (HWND)utils::GetInstance()->read<DWORD>(pSharedMemoryPointer->Base_GameWndHwndAddr);
	}
	__except (1)
	{
		return 0;
	}
}

CHookToMainThread::CHookToMainThread()
{

}


CHookToMainThread::~CHookToMainThread()
{
	UnHook();
}

bool CHookToMainThread::Hook()
{
	auto hwnd = GetGameHwnd();
	if (!hwnd)
	{
		utils::GetInstance()->log("ERROR: ��Ϸ���ھ����ȡ����\n");
		return false;
	}


	auto threadID = GetWindowThreadProcessId((HWND)hwnd, NULL);
	if (!threadID)
	{
		utils::GetInstance()->log("ERROR: GetCurrentProcessId()ʧ��");
		return false;
	}

	//���ص����߳�
	m_hHook = SetWindowsHookEx(WH_CALLWNDPROC, CallWndProc, NULL, threadID);
	m_hWndHook = SetWindowLong(hwnd, GWL_WNDPROC, (long)WindowProc);
	if (!m_hHook)
	{
		utils::GetInstance()->log("ERROR: CHookToMainThread::Hook() ERROR , CODE = %x", GetLastError());
		return false;
	}
	return true;
}

bool CHookToMainThread::UnHook()
{
	return (bool)UnhookWindowsHookEx(m_hHook);
}

void CHookToMainThread::SendMessageToGame(MESSAGE msg, LPARAM lparam)
{
	::SendMessage(GetGameHwnd(), m_msgCode, msg, lparam);
}

LRESULT CALLBACK CallWndProc(_In_ int nCode, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
	//��ȡ�����ṹ��
	CWPSTRUCT *pArg = (CWPSTRUCT*)lParam;

	if (nCode == HC_ACTION)
	{
		//������Զ�����Ϣ
		if (pArg->message == CHookToMainThread::m_msgCode)
		{
			//������ϢID��������Ϣ
			switch (pArg->wParam)
			{
			case MESSAGE::MSG_SKILLCALL: {
				SKILL_TO_MONS p = *(SKILL_TO_MONS*)pArg->lParam;
				GameCall::GetInstance()->UseSkill(p.index, p.monsObj);
				break;
			}
			case MESSAGE::MSG_ATTACKCALL:
			{
				SKILL_TO_MONS p = *(SKILL_TO_MONS*)pArg->lParam;
				person temp(p.monsObj);
				GameCall::GetInstance()->HeroAttack(p.monsObj);
				break;
			}
			case MESSAGE::MSG_FINDWAY:
			{
				auto pnt = GameCall::GetInstance()->GetMousePnt();
				GameCall::GetInstance()->FindWay(pnt);
				break;
			}
			}//switch ����

			return 1;
		}//�Զ�����Ϣ��������������Ϣ

	}

	//���ݸ�ϵͳĬ����Ϣ
	return CallNextHookEx(CHookToMainThread::m_hHook, nCode, wParam, lParam);
}

LRESULT CALLBACK WindowProc(_In_ HWND hwnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
	if (uMsg == WM_KEYDOWN)
	{
		if (wParam == 'Q' || wParam == 'W' || wParam == 'E' || wParam == 'R')
		{
			if (UseSkill(wParam)) 
				return 1;
		}

	}
	return CallWindowProc((WNDPROC)CHookToMainThread::m_hWndHook, hwnd, uMsg, wParam, lParam);
}
