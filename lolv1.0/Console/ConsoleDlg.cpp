
// ConsoleDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Console.h"
#include "ConsoleDlg.h"
#include "afxdialogex.h"
#include "ShareMemory.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "InjectDll.h"
#include "virtualKey.h"
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���


class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

DWORD WINAPI ThreadProcA(_In_ LPVOID lpParameter)
{
	//���Ӵ��ڵĻص�����
	CInjectDll injectClass("GameDll.dll");
	while (true)
	{

		auto hwnd = FindWindow("RiotWindowClass", NULL);
		if (hwnd)
		{
			//���û��ע��
			if (!injectClass.GetInject()) {
				injectClass.injectDll(hwnd);
			}
		}
		else
		{
			//�����Ϸ�˳������ó�û��ע��
			injectClass.SetInject(false);

		}
		Sleep(100);
	}
}

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CConsoleDlg �Ի���



CConsoleDlg::CConsoleDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CONSOLE_DIALOG, pParent)
	, m_radiobtngroup1(1)
	, m_ShowZouAMs(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CConsoleDlg::~CConsoleDlg()
{

}

void CConsoleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK1, m_bLockQ);
	DDX_Control(pDX, IDC_CHECK2, m_bLockW);
	DDX_Control(pDX, IDC_CHECK3, m_bLockE);
	DDX_Control(pDX, IDC_CHECK4, m_bLockR);
	DDX_Control(pDX, IDC_CHECK5, m_bLockQAA);
	//  DDX_Text(pDX, IDC_STATIC_ZOUA, m_showZouAMs);
	DDX_Control(pDX, IDC_SLIDER1, m_ZouAliderCtl);
	DDX_Radio(pDX, IDC_RADIO1, m_radiobtngroup1);
	DDX_Control(pDX, IDC_EDIT1, m_LockQCtl);
	DDX_Control(pDX, IDC_EDIT2, m_lockWCtl);
	DDX_Control(pDX, IDC_EDIT3, m_lockECtl);
	DDX_Control(pDX, IDC_EDIT4, m_lockRCtl);
	DDX_Control(pDX, IDC_EDIT5, m_LockAACtl);
	DDX_Text(pDX, IDC_STATIC_TIPS, m_ShowZouAMs);
	DDX_Control(pDX, IDC_EDIT6, m_clearAACtl);
	DDX_Control(pDX, IDC_CHECK11, m_bOpenClear);
	DDX_Control(pDX, IDC_CHECK6, m_bHuabanAutoE);
	DDX_Control(pDX, IDC_CHECK9, m_autoEToHero);
	DDX_Control(pDX, IDC_CHECK10, m_autoEToMons);
}

BEGIN_MESSAGE_MAP(CConsoleDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CHECK1, &CConsoleDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &CConsoleDlg::OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_CHECK3, &CConsoleDlg::OnBnClickedCheck3)
	ON_BN_CLICKED(IDC_CHECK4, &CConsoleDlg::OnBnClickedCheck4)
	ON_BN_CLICKED(IDC_CHECK5, &CConsoleDlg::OnBnClickedCheck5)
	ON_WM_CLOSE()
ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &CConsoleDlg::OnNMCustomdrawSlider1)
ON_BN_CLICKED(IDC_RADIO1, &CConsoleDlg::OnBnClickedRadio1)
ON_BN_CLICKED(IDC_RADIO2, &CConsoleDlg::OnBnClickedRadio1)
//ON_EN_SETFOCUS(IDC_EDIT1, &CConsoleDlg::OnEnSetfocusEdit1)
//ON_WM_KEYDOWN()
ON_BN_CLICKED(IDC_CHECK11, &CConsoleDlg::OnBnClickedCheck11)
ON_BN_CLICKED(IDC_CHECK6, &CConsoleDlg::OnBnClickedCheck6)
ON_BN_CLICKED(IDC_CHECK9, &CConsoleDlg::OnBnClickedCheck9)
ON_BN_CLICKED(IDC_CHECK10, &CConsoleDlg::OnBnClickedCheck10)
END_MESSAGE_MAP()


// CConsoleDlg ��Ϣ�������

void CConsoleDlg::InitGameStruct()
{
	m_sharedMemory.GetPointerOfMapView()->Base_GameStartTime = 0x01AA2768;    //��Ϸ����ʱ��     ƫ��:1    //OD��ַ:0x008DF27E
	m_sharedMemory.GetPointerOfMapView()->Base_RoleSelfAddr = 0x01A9EA20;    //��һ���ַ     ƫ��:2    //OD��ַ:0x005E0482
	m_sharedMemory.GetPointerOfMapView()->Base_BufferAddr = 0x01A9C290;    //buff�������ַ     ƫ��:2    //OD��ַ:0x00BB4BEA
	m_sharedMemory.GetPointerOfMapView()->Base_MonsterArrayAddr = 0x02AC8104;    //�����������ַ     ƫ��:2    //OD��ַ:0x00C688C2
	m_sharedMemory.GetPointerOfMapView()->Base_GameWndHwndAddr = 0x01A9C508;    //��Ϸ���ڻ���ַ     ƫ��:2    //OD��ַ:0x008301D4
	m_sharedMemory.GetPointerOfMapView()->Base_SkillTravseOffset1 = 0x00002948;    //���������һ��ƫ��     ƫ��:1    //OD��ַ:0x0059478D
	m_sharedMemory.GetPointerOfMapView()->Base_SkillTravseOffset2 = 0x00000560;    //��������ڶ���ƫ��     ƫ��:2    //OD��ַ:0x007426C0
	m_sharedMemory.GetPointerOfMapView()->Base_SkillOffset_Object = 0x000000F4;    //���ܶ���ƫ��     ƫ��:2    //OD��ַ:0x005947A4
	m_sharedMemory.GetPointerOfMapView()->Base_SkillCallEcxAddr = 0x01A9D2FC;    //����CALL ECX     ƫ��:2    //OD��ַ:0x00E55E48
	m_sharedMemory.GetPointerOfMapView()->Base_SkillCallAddr = 0x00BDB500;    //����CALL     ƫ��:1    //OD��ַ:0x00E55E6F
	m_sharedMemory.GetPointerOfMapView()->Base_SkillCallHookAddr = 0x00B0236D;    //����CALL Hook     ƫ��:1    //OD��ַ:0x00B0236D
	m_sharedMemory.GetPointerOfMapView()->Base_AttackHeroCallAddr = 0x007E7560;    //�չ�CALL     ƫ��:1    //OD��ַ:0x0076168E
	m_sharedMemory.GetPointerOfMapView()->Base_FindWayCallAddr = 0x007E7560;    //Ѱ·call     ƫ��:1    //OD��ַ:0x0062FC72
	m_sharedMemory.GetPointerOfMapView()->Base_MonsterCurrentMpOffset = 0x000001F4;    //��ǰ����ƫ��     ƫ��:5    //OD��ַ:0x00C5F30F
	m_sharedMemory.GetPointerOfMapView()->Base_MonsterCurrentHpOffset = 0x0000056C;    //��ǰѪ��ƫ��     ƫ��:4    //OD��ַ:0x007C43B7���Ѹ��£�
	m_sharedMemory.GetPointerOfMapView()->Base_MonsterBVisableOffset = 0x00003A58;    //�Ƿ�ɼ�ƫ��     ƫ��:2    //OD��ַ:0x00A5BF03
	m_sharedMemory.GetPointerOfMapView()->Base_equipmentTravseOffset1 = 0x000015D8;    //װ���������ƫ��1     ƫ��:2    //OD��ַ:0x00C2227B
	m_sharedMemory.GetPointerOfMapView()->Base_equipmentTravseOffset2 = 0x00000288;    //װ���������ƫ��2     ƫ��:3    //OD��ַ:0x00C40349
	m_sharedMemory.GetPointerOfMapView()->Base_MousePointAddr = 0x1A9D2FC;            //���λ�û���ַ���Ѹ��£�
	m_sharedMemory.GetPointerOfMapView()->Base_SkillOffset_Range1 = 0x3b0;		 //���ܷ�Χƫ�ƣ��Ѹ��£�
	m_sharedMemory.GetPointerOfMapView()->Base_SkillOffset_MP = 0x000005AC;    //��������ƫ��     ƫ��:5    //OD��ַ:0x0077FBDB���Ѹ��£�
	m_sharedMemory.GetPointerOfMapView()->Base_MonsterOrientationXOffset = 0x312C;  //���X����
	m_sharedMemory.GetPointerOfMapView()->Base_MonsterBMovingOffset = 0x4C54; //����Ƿ��ƶ�
	m_sharedMemory.GetPointerOfMapView()->Base_BufferOffset = 0x2FD0;
	m_sharedMemory.GetPointerOfMapView()->Base_BufferCountOffset = 0x7C;
}

BOOL CConsoleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_ZouAliderCtl.SetRange(0, 50);

	SetDlgItemText(IDC_STATIC_LOG, pAuth->GetValidity());

	//���������ڴ�
	if (!m_sharedMemory.CreateSharedMemory())
	{
		AfxMessageBox("����δ֪������رճ���");
		exit(1);
		return FALSE;
	}
	m_sharedMemory.GetPointerOfMapView()->dwZouAMs = 50;
	m_ZouAliderCtl.SetPos(50);

	//����Ĭ�ϵı༭��
	m_LockQCtl.SetWindowTextA(KeyNames[VK_SPACE].text);
	m_lockWCtl.SetWindowTextA(KeyNames[VK_SPACE].text);
	m_lockECtl.SetWindowTextA(KeyNames[VK_SPACE].text);
	m_lockRCtl.SetWindowTextA(KeyNames[VK_SPACE].text);
	m_LockAACtl.SetWindowTextA(KeyNames[VK_SPACE].text);
	m_clearAACtl.SetWindowTextA(KeyNames['C'].text);
	m_sharedMemory.GetPointerOfMapView()->VirtualKeyQ = VK_SPACE;
	m_sharedMemory.GetPointerOfMapView()->VirtualKeyW = VK_SPACE;
	m_sharedMemory.GetPointerOfMapView()->VirtualKeyE = VK_SPACE;
	m_sharedMemory.GetPointerOfMapView()->VirtualKeyR = VK_SPACE;
	m_sharedMemory.GetPointerOfMapView()->VirtualKeyAA = VK_SPACE;
	m_sharedMemory.GetPointerOfMapView()->VirtualKeyOpenClear = 'C';


	VMProtectBegin("InitGameStruct");
	InitGameStruct();
	VMProtectEnd();
	//����ע���߳�
	m_ThreadHanle = ::CreateThread(NULL, NULL,LPTHREAD_START_ROUTINE(ThreadProcA) , this, NULL, NULL);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CConsoleDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CConsoleDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CConsoleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CConsoleDlg::OnBnClickedCheck1()
{
	m_sharedMemory.GetPointerOfMapView()->bLockQ = m_bLockQ.GetCheck() == BST_CHECKED ? true : false;
	m_LockQCtl.EnableWindow( !(m_bLockQ.GetCheck() == BST_CHECKED) );
}

void CConsoleDlg::OnBnClickedCheck2()
{
	m_sharedMemory.GetPointerOfMapView()->bLockW = m_bLockW.GetCheck() == BST_CHECKED ? true : false;
	m_lockWCtl.EnableWindow(!(m_bLockW.GetCheck() == BST_CHECKED));
}


void CConsoleDlg::OnBnClickedCheck3()
{
	m_sharedMemory.GetPointerOfMapView()->bLockE = m_bLockE.GetCheck() == BST_CHECKED ? true : false;
	m_lockECtl.EnableWindow(!(m_bLockE.GetCheck() == BST_CHECKED));
}


void CConsoleDlg::OnBnClickedCheck4()
{
	m_sharedMemory.GetPointerOfMapView()->bLockR = m_bLockR.GetCheck() == BST_CHECKED ? true : false;
	m_lockRCtl.EnableWindow(!(m_bLockR.GetCheck() == BST_CHECKED));
}


void CConsoleDlg::OnBnClickedCheck5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_sharedMemory.GetPointerOfMapView()->bOpenAA = m_bLockQAA.GetCheck() == BST_CHECKED ? true : false;
	m_LockAACtl.EnableWindow(!(m_bLockQAA.GetCheck() == BST_CHECKED));
}




void CConsoleDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	//���ε�ԭ����WM_CLOSE
	CDialogEx::OnClose();
}


BOOL CConsoleDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ����ESC
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
	{
		return TRUE;
	}

	//����Q
	if (::GetFocus() == m_LockQCtl.GetSafeHwnd()&& pMsg->message == WM_KEYDOWN)
	{
		m_LockQCtl.SetWindowTextA(KeyNames[pMsg->wParam].text);
		m_sharedMemory.GetPointerOfMapView()->VirtualKeyQ = pMsg->wParam;
	}
	//����W
	if (::GetFocus() == m_lockWCtl.GetSafeHwnd() && pMsg->message == WM_KEYDOWN)
	{
		m_lockWCtl.SetWindowTextA(KeyNames[pMsg->wParam].text);
		m_sharedMemory.GetPointerOfMapView()->VirtualKeyW = pMsg->wParam;
	}
	//����E
	if (::GetFocus() == m_lockECtl.GetSafeHwnd() && pMsg->message == WM_KEYDOWN)
	{
		m_lockECtl.SetWindowTextA(KeyNames[pMsg->wParam].text);
		m_sharedMemory.GetPointerOfMapView()->VirtualKeyE = pMsg->wParam;
	}
	//����R
	if (::GetFocus() == m_lockRCtl.GetSafeHwnd() && pMsg->message == WM_KEYDOWN)
	{
		m_lockRCtl.SetWindowTextA(KeyNames[pMsg->wParam].text);
		m_sharedMemory.GetPointerOfMapView()->VirtualKeyR = pMsg->wParam;
	}

	//������A
	if (::GetFocus() == m_LockAACtl.GetSafeHwnd() && pMsg->message == WM_KEYDOWN)
	{
		m_LockAACtl.SetWindowTextA(KeyNames[pMsg->wParam].text);
		m_sharedMemory.GetPointerOfMapView()->VirtualKeyAA = pMsg->wParam;
	}

	//������A�����ȼ�
	if (::GetFocus() == m_clearAACtl.GetSafeHwnd() && pMsg->message == WM_KEYDOWN)
	{
		m_clearAACtl.SetWindowTextA(KeyNames[pMsg->wParam].text);
		m_sharedMemory.GetPointerOfMapView()->VirtualKeyOpenClear = pMsg->wParam;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CConsoleDlg::PreInitDialog()
{
	// TODO: �ڴ����ר�ô����/����û���
	//
	CDialogEx::PreInitDialog();
}


void CConsoleDlg::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	UpdateData(TRUE);
	m_sharedMemory.GetPointerOfMapView()->dwZouAMs = m_ZouAliderCtl.GetPos();
	m_ShowZouAMs = m_ZouAliderCtl.GetPos();
	UpdateData(FALSE);
	*pResult = 0;
}


void CConsoleDlg::OnBnClickedRadio1()
{
	// TODO: ��ѡ���¼�����

	UpdateData(TRUE);

	switch (m_radiobtngroup1)
	{
	case 0:
	{
		m_sharedMemory.GetPointerOfMapView()->dwTargetSelecter = 0;
		break;
	}
	case 1:
	{
		m_sharedMemory.GetPointerOfMapView()->dwTargetSelecter = 1;
		break;
	}
	default:
		AfxMessageBox("ѡ��Ŀ�����");
		break;
	}
}





void CConsoleDlg::OnBnClickedCheck11()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_sharedMemory.GetPointerOfMapView()->bOpenClearAA = m_bOpenClear.GetCheck() == BST_CHECKED ? true : false;
	m_clearAACtl.EnableWindow(!(m_bOpenClear.GetCheck() == BST_CHECKED));
}


void CConsoleDlg::OnBnClickedCheck6()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_sharedMemory.GetPointerOfMapView()->bAutoHuabanE = m_bHuabanAutoE.GetCheck() == BST_CHECKED ? true : false;
}


void CConsoleDlg::OnBnClickedCheck9()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_sharedMemory.GetPointerOfMapView()->bAutoEToHero = m_autoEToHero.GetCheck() == BST_CHECKED ? true : false;
}


void CConsoleDlg::OnBnClickedCheck10()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_sharedMemory.GetPointerOfMapView()->bAutoEToMons = m_autoEToMons.GetCheck() == BST_CHECKED ? true : false;
}
