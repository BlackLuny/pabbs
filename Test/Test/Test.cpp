// Test.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "Test.h"
#include "TestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: ����� DLL ����� MFC DLL �Ƕ�̬���ӵģ�
//		��Ӵ� DLL �������κε���
//		MFC �ĺ������뽫 AFX_MANAGE_STATE ����ӵ�
//		�ú�������ǰ�档
//
//		����:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// �˴�Ϊ��ͨ������
//		}
//
//		�˺������κ� MFC ����
//		������ÿ��������ʮ����Ҫ������ζ��
//		��������Ϊ�����еĵ�һ�����
//		���֣������������ж������������
//		������Ϊ���ǵĹ��캯���������� MFC
//		DLL ���á�
//
//		�й�������ϸ��Ϣ��
//		����� MFC ����˵�� 33 �� 58��
//

// CTestApp

BEGIN_MESSAGE_MAP(CTestApp, CWinApp)
END_MESSAGE_MAP()


// CTestApp ����

CTestApp::CTestApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CTestApp ����

CTestApp theApp;


// CTestApp ��ʼ��

CTestDlg* dDlgMain = NULL;
DWORD WINAPI CreateClentWindow(void* lpParamater)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	dDlgMain = new CTestDlg;
	theApp.m_pMainWnd = dDlgMain;
	dDlgMain->DoModal();
	delete dDlgMain;
	dDlgMain = NULL;
	FreeLibraryAndExitThread(theApp.m_hInstance, 0);
	return 0;
}

void CreatClent()
{
	HANDLE hThreadID = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)CreateClentWindow, NULL, 0, NULL);
	CloseHandle(hThreadID);
}

BOOL CTestApp::InitInstance()
{
	CWinApp::InitInstance();
	CreatClent();
	return TRUE;
}
