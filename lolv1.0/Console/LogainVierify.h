#pragma once


// CLogainVierify �Ի���

class CLogainVierify : public CDialogEx
{
	DECLARE_DYNAMIC(CLogainVierify)

public:
	CLogainVierify(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLogainVierify();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOGIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	void Onshow();
	CString m_szAcc;
	CString m_szPass;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
