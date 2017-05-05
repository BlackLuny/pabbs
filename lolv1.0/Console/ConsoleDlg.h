
// ConsoleDlg.h : ͷ�ļ�
//

#pragma once
#include "ShareMemory.h"
#include "afxwin.h"
#include<windows.h>
DWORD WINAPI ThreadProcA(_In_ LPVOID lpParameter);
// CConsoleDlg �Ի���
class CConsoleDlg : public CDialogEx
{
// ����
public:
	CConsoleDlg(CWnd* pParent = NULL);	// ��׼���캯��
	~CConsoleDlg();
// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONSOLE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

private:
	CShareMemory m_sharedMemory;
	HANDLE m_ThreadHanle;
// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCheck1();
	CButton m_bLockQ;
	afx_msg void OnBnClickedCheck2();
	CButton m_bLockW;
	CButton m_bLockE;
	CButton m_bLockR;
	CButton m_bLockQAA;
	afx_msg void OnBnClickedCheck3();
	afx_msg void OnBnClickedCheck4();
	afx_msg void OnBnClickedCheck5();
};

