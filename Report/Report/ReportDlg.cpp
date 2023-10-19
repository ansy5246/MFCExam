
// ReportDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "Report.h"
#include "ReportDlg.h"
#include "afxdialogex.h"
#include <iostream>
#include "Process.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CReportDlg ��ȭ ����



CReportDlg::CReportDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_REPORT_DIALOG, pParent)
	, m_radius(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CReportDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_RADIUS, m_radius);
}

BEGIN_MESSAGE_MAP(CReportDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BUTTON_PROCESS, &CReportDlg::OnBnClickedButtonProcess)
	ON_BN_CLICKED(IDC_BUTTON_PATTERN, &CReportDlg::OnBnClickedButtonPattern)
	ON_BN_CLICKED(IDC_BUTTON_PATTERN_CENTER, &CReportDlg::OnBnClickedButtonPatternCenter)
	ON_BN_CLICKED(IDC_BUTTON_CIRCLE, &CReportDlg::OnBnClickedButtonCircle)
	ON_BN_CLICKED(IDC_BUTTON_CIRCLE_CENTER, &CReportDlg::OnBnClickedButtonCircleCenter)
END_MESSAGE_MAP()


// CReportDlg �޽��� ó����

BOOL CReportDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	MoveWindow(0, 0, 1280, 800);
	
	m_pDlgImage = new CDlgImage;
	m_pDlgImage->Create(IDD_IMAGE_DIALOG, this);
	m_pDlgImage->MoveWindow(0, 0, 640, 480);

	m_pDlgResult = new CDlgImage;
	m_pDlgResult->Create(IDD_IMAGE_DIALOG, this);
	m_pDlgResult->MoveWindow(640, 0, 640, 480);

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CReportDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CReportDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CReportDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CReportDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	if(m_pDlgImage)
		delete m_pDlgImage;
	if(m_pDlgResult)
		delete m_pDlgResult;
}


void CReportDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	m_pDlgImage->ShowWindow(SW_SHOW);
	m_pDlgResult->ShowWindow(SW_SHOW);
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}


void CReportDlg::OnBnClickedButtonProcess()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CProcess process;

}


void CReportDlg::OnBnClickedButtonPattern()
{	
	unsigned char* fm = (unsigned char*)m_pDlgImage->m_image.GetBits();
	int nWidth = m_pDlgImage->m_image.GetWidth();
	int nHeight = m_pDlgImage->m_image.GetHeight();
	int nPitch = m_pDlgImage->m_image.GetPitch();
	memset(fm, 0, nWidth * nHeight);

	CRect rect(100, 200, 150, 400);
	for(int y=rect.top; y <rect.bottom; y++)
	{
		for (int x = rect.left; x < rect.right; x++)
		{
			fm[y*nPitch + x] = rand() % 100;
		}
	}
	m_pDlgImage->Invalidate();
}


void CReportDlg::OnBnClickedButtonPatternCenter()
{
	unsigned char* fm = (unsigned char*)m_pDlgImage->m_image.GetBits();
	int nWidth = m_pDlgImage->m_image.GetWidth();
	int nHeight = m_pDlgImage->m_image.GetHeight();
	int nPitch = m_pDlgImage->m_image.GetPitch();

	int nTh = 0x80;
	CRect rect(0, 0, nWidth, nHeight);

	int nSumX = 0;
	int nSumY = 0;
	int nCount = 0;

	for (int y = rect.top; y <rect.bottom; y++)
	{
		for (int x = rect.left; x < rect.right; x++)
		{
			if (fm[y*nPitch+x] > nTh)
			{
				nSumX += x;
				nSumY += y;
				nCount++;
			}
		}
	}

	double dCenterX = (double)nSumX / nCount;
	double dCenterY = (double)nSumY / nCount;

	std::cout << dCenterX << "\t" << dCenterY << std::endl;
}


void CReportDlg::OnBnClickedButtonCircle()
{
	UpdateData();

	if (m_radius == 0)
	{
		AfxMessageBox(_T("Please enter the radius."));
		return;
	}

	m_pDlgImage->SetRadius(m_radius);
	m_pDlgImage->SetWeightCenter(false);

	unsigned char* fm = (unsigned char*)m_pDlgImage->m_image.GetBits();
	int nWidth = m_pDlgImage->m_image.GetWidth();
	int nHeight = m_pDlgImage->m_image.GetHeight();
	int nPitch = m_pDlgImage->m_image.GetPitch();
	memset(fm, 0, nWidth * nHeight);

	CPoint ptCenter(nWidth / 2, nHeight / 2);
	CRect rect(ptCenter, ptCenter);
	rect.InflateRect(m_radius, m_radius, m_radius, m_radius);

	for (int y = rect.top; y <rect.bottom; y++)
	{
		for (int x = rect.left; x < rect.right; x++)
		{
			double dx = ptCenter.x - x;
			double dy = ptCenter.y - y;
			
			if (dx * dx + dy * dy < m_radius * m_radius)
			{
				if(m_pDlgImage->IsValidPos(x, y))
					fm[y*nPitch + x] = rand() % 100;
			}
		}
	}
	m_pDlgImage->Invalidate();
}

void CReportDlg::OnBnClickedButtonCircleCenter()
{
	unsigned char* fm = (unsigned char*)m_pDlgImage->m_image.GetBits();
	int nWidth = m_pDlgImage->m_image.GetWidth();
	int nHeight = m_pDlgImage->m_image.GetHeight();
	int nPitch = m_pDlgImage->m_image.GetPitch();

	int nTh = 50;
	CRect rect(0, 0, nWidth, nHeight);

	int nSumX = 0;
	int nSumY = 0;
	int nCount = 0;

	for (int y = rect.top; y <rect.bottom; y++)
	{
		for (int x = rect.left; x < rect.right; x++)
		{
			if (fm[y*nPitch+x] > nTh)
			{
				nSumX += x;
				nSumY += y;
				nCount++;
			}
		}
	}

	double dCenterX = (double)nSumX / nCount;
	double dCenterY = (double)nSumY / nCount;

	std::cout << dCenterX << "\t" << dCenterY << std::endl;

	m_pDlgImage->SetWeightCenter(true, (int)dCenterX, (int)dCenterY);
	m_pDlgImage->Invalidate();
}
