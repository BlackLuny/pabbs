
// Console.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "Console.h"
#include "ConsoleDlg.h"
#include "LogainVierify.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CConsoleApp

BEGIN_MESSAGE_MAP(CConsoleApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CConsoleApp ����

CConsoleApp::CConsoleApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CConsoleApp ����

CConsoleApp theApp;


// CConsoleApp ��ʼ��

BOOL CConsoleApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()��  ���򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ���Windows Native���Ӿ����������Ա��� MFC �ؼ�����������
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	//��ֹ�࿪
	auto handle = ::CreateMutex(NULL, FALSE, ("Mutex2010073"));
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		CloseHandle(handle);
		return FALSE;
	}
	::CoInitialize(NULL);
	pAuth.CreateInstance(__uuidof(CurrencyAuth));

	//������Դ

	HRSRC hRsrc = ::FindResource(NULL, MAKEINTRESOURCE(IDR_VNC2), "vnc");
	if (!hRsrc)
	{
		return FALSE;
	}
	DWORD dwSize = SizeofResource(NULL, hRsrc);
	if (!dwSize)
	{
		return FALSE;
	}
	HGLOBAL hGlobal = LoadResource(NULL, hRsrc);
	if (!hGlobal)
	{
		return FALSE;
	}
	LPVOID pBuffer = LockResource(hGlobal);
	if (NULL == pBuffer)
		return FALSE;
	pAuth->InputVNC((int)pBuffer, dwSize);

	Sleep(100);
	VMProtectBegin("mad");
	auto result  = pAuth->Initialize("{C1E14188-7629-4B10-B2B5-E03B523C90E6}");//��֤�����ʼ��
	VMProtectEnd();
	if (result == -1)
	{
		//������֤���
		pAuth.Release();
		::CoUninitialize();
		return FALSE;
	}



	//CConsoleDlg dlg;
	CLogainVierify dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();

	//������֤���
	pAuth.Release();
	::CoUninitialize();

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

#ifndef _AFXDLL
	ControlBarCleanUp();
#endif

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

