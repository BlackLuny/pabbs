// LogainVierify.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Console.h"
#include "LogainVierify.h"
#include "afxdialogex.h"
#include "ConsoleDlg.h"

// CLogainVierify �Ի���

IMPLEMENT_DYNAMIC(CLogainVierify, CDialogEx)

CLogainVierify::CLogainVierify(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_LOGIN, pParent)
	, m_szAcc(_T(""))
	, m_szPass(_T(""))
{

}

CLogainVierify::~CLogainVierify()
{
}

void CLogainVierify::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_szAcc);
	DDX_Text(pDX, IDC_EDIT2, m_szPass);
}


BEGIN_MESSAGE_MAP(CLogainVierify, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CLogainVierify::OnBnClickedButton1)
END_MESSAGE_MAP()


// CLogainVierify ��Ϣ�������


void CLogainVierify::OnBnClickedButton1()
{
	// TODO: 
	VMProtectBegin("ccc");
	char szAcc[40];
	GetDlgItem(IDC_EDIT1)->GetWindowText(szAcc, sizeof(szAcc));
	char szPwd[40];
	GetDlgItem(IDC_EDIT2)->GetWindowText(szPwd, sizeof(szPwd));

	auto ret = pAuth->UserAuth(_bstr_t(szAcc), _bstr_t(szPwd));

	switch (ret)
	{
	case 0:
		((CLogainVierify*)(theApp.m_pMainWnd))->OnOK();
		break;
	case -1:
		GetDlgItem(IDC_STATIC_LOG)->SetWindowText("ע���벻����");
		break;
	case -2:
		GetDlgItem(IDC_STATIC_LOG)->SetWindowText("ע���뱻����");
		break;
	case -3:
		GetDlgItem(IDC_STATIC_LOG)->SetWindowText("�󶨻�������");
		break;
	case -4:
		GetDlgItem(IDC_STATIC_LOG)->SetWindowText("ע����������");
		break;
	case -5:
		GetDlgItem(IDC_STATIC_LOG)->SetWindowText("�ѹ���");
		break;
	case -6:
		GetDlgItem(IDC_STATIC_LOG)->SetWindowText("�û�����");
		break;
	}
	VMProtectEnd();
}


BOOL CLogainVierify::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CLogainVierify::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
	CDialog::OnOK();

	CConsoleDlg dlg;
	theApp.m_pMainWnd = &dlg;
	dlg.DoModal();
}
