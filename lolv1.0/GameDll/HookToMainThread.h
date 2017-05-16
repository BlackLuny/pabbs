#pragma once
#include "skill.h"
//��Ϸ�Զ�����Ϣ
enum MESSAGE
{
	MSG_SKILLCALL = 100, //����CALL
	MSG_ATTACKCALL, //�չ�CALL
	MSG_FINDWAY, //Ѱ·CALL
};


//ʹ�ü��ܽṹ��
struct SKILL_TO_MONS
{
	EM_SKILL_INDEX index;
	DWORD monsObj;
};

class CHookToMainThread
{
public:
	CHookToMainThread();
	~CHookToMainThread();

	//���ص����߳�
	bool Hook();
	//ж�����߳�
	bool UnHook();
	//������Ϣ
	void SendMessageToGame(MESSAGE msg, LPARAM lparam);

	static DWORD m_msgCode;
public:
	static HHOOK m_hHook;
	static LONG m_hWndHook;
private:
	HWND GetGameHwnd()const;
};

LRESULT CALLBACK CallWndProc(
	_In_ int    nCode,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
);


LRESULT CALLBACK WindowProc(
	_In_ HWND   hwnd,
	_In_ UINT   uMsg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
);
