// TestDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Test.h"
#include "TestDlg.h"
#include "afxdialogex.h"


// CTestDlg �Ի���

IMPLEMENT_DYNAMIC(CTestDlg, CDialogEx)

CTestDlg::CTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTestDlg::IDD, pParent)
{

}

CTestDlg::~CTestDlg()
{
}

void CTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTestDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CTestDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CTestDlg ��Ϣ�������


DWORD g_ObjAddress = NULL;
DWORD g_HookAddress = 0x0064F854;//HOOK�ĵ�ַ
DWORD g_CallAddress = NULL;
VOID WINAPI HookSkill(DWORD dwIndex, PFLOAT Coordinate, PDWORD ObjAddress)
{
	if (g_ObjAddress)
	{
		memcpy(Coordinate, (float*)(g_ObjAddress + 0x54), 0xC);
		*ObjAddress = g_ObjAddress;
		g_ObjAddress = NULL;
		return;
	}
	__asm
	{
		push    ObjAddress
		push    Coordinate
		push    dwIndex
		call    dword ptr[g_CallAddress]
	}
}

VOID UseSkill(DWORD dwIndex, DWORD UnitBase)
{
	g_ObjAddress = UnitBase;
	__asm
	{
		mov     ecx, 0x154B7D0
		mov     ecx, dword ptr [ecx]
		mov     ecx, dword ptr [ecx+0x2C]
		push    0
		push    2
		push    dwIndex
		mov     eax,0x7154B0
		call    eax
	}
}

BOOL CTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	DWORD OldProtect;
	VirtualProtect((DWORD*)g_HookAddress, 5, PAGE_READWRITE, &OldProtect);
	g_CallAddress = *(DWORD*)(g_HookAddress + 1) + g_HookAddress + 5;
	*(DWORD*)(g_HookAddress + 1) = (DWORD)HookSkill - g_HookAddress - 5;
	VirtualProtect((DWORD*)g_HookAddress, 5, OldProtect, &OldProtect);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CTestDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UseSkill(GetDlgItemInt(IDC_EDIT1), GetDlgItemInt(IDC_EDIT2));
}