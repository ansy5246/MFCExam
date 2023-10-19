
// ReportDlg.cpp : 구현 파일
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

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CReportDlg 대화 상자



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


// CReportDlg 메시지 처리기

BOOL CReportDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	MoveWindow(0, 0, 1280, 800);
	
	m_pDlgImage = new CDlgImage;
	m_pDlgImage->Create(IDD_IMAGE_DIALOG, this);
	m_pDlgImage->MoveWindow(0, 0, 640, 480);

	m_pDlgResult = new CDlgImage;
	m_pDlgResult->Create(IDD_IMAGE_DIALOG, this);
	m_pDlgResult->MoveWindow(640, 0, 640, 480);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CReportDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CReportDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CReportDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
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
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


void CReportDlg::OnBnClickedButtonProcess()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
