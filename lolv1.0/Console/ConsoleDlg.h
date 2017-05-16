
// ConsoleDlg.h : ͷ�ļ�
//

#pragma once
#include "ShareMemory.h"
#include "afxwin.h"
#include<windows.h>
#include "afxcmn.h"
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

public:
	CShareMemory m_sharedMemory;
	HANDLE m_ThreadHanle;

	void InitGameStruct();
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
	afx_msg void OnClose();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void PreInitDialog();
//	afx_msg void OnTRBNThumbPosChangingSlider1(NMHDR *pNMHDR, LRESULT *pResult);
//	DWORD m_showZouAMs;
	CSliderCtrl m_ZouAliderCtl;
	afx_msg void OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	int m_radiobtngroup1;
	afx_msg void OnBnClickedRadio1();
//	afx_msg void OnEnSetfocusEdit1();
//	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	CEdit m_LockQCtl;
	CEdit m_lockWCtl;
	CEdit m_lockECtl;
	CEdit m_lockRCtl;
	CEdit m_LockAACtl;
};

