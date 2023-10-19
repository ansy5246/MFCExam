// DlgImage.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Report.h"
#include "DlgImage.h"
#include "afxdialogex.h"


// CDlgImage 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDlgImage, CDialogEx)

CDlgImage::CDlgImage(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_IMAGE_DIALOG, pParent)
	, m_bFoundCenter(false)
{

}

CDlgImage::~CDlgImage()
{
}

void CDlgImage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgImage, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CDlgImage 메시지 처리기입니다.


BOOL CDlgImage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.	
	InitImage(); 
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CDlgImage::InitImage()
{
	int nWidth = 640;
	int nHeight = 480;
	int nBpp = 8;

	if (m_image.IsNull())
		m_image.Create(nWidth, -nHeight, nBpp);

	if (nBpp == 8)
	{
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++)
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		m_image.SetColorTable(0, 256, rgb);
	}

	int nPitch = m_image.GetPitch();
	unsigned char* fm = (unsigned char*)m_image.GetBits();
	memset(fm, 255, nWidth * nHeight);
}

const double pi = 3.1415926;
const int vertex = 365;

void CDlgImage::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.

	if (m_image.IsNull())
		return;

	m_image.Draw(dc, 0, 0);

	if (m_bFoundCenter)
	{
		CPen pen(PS_SOLID, 1, RGB(255, 255, 0));
		CPen* oldPen = dc.SelectObject(&pen);
				
		int x1 = m_centerX - m_radius;
		int y1 = m_centerY - m_radius;
		int x2 = m_centerX + m_radius;
		int y2 = m_centerY + m_radius;

		dc.MoveTo(m_centerX, y1);
		dc.LineTo(m_centerX, y2);
		dc.MoveTo(x1, m_centerY);
		dc.LineTo(x2, m_centerY);
		
		// ellipse		
		double x = m_radius * cos(0.0) + m_centerX;
		double y = m_radius * sin(0.0) + m_centerY;
		dc.MoveTo(x, y);

		for (int i = 0; i <= vertex; i++)
		{
			double radian = i * 2 * pi / vertex;
			double x = m_radius * cos(radian) + m_centerX;
			double y = m_radius * sin(radian) + m_centerY;
			dc.LineTo(x, y);
		}

		dc.SelectObject(oldPen);
	}
}

bool CDlgImage::IsValidPos(int x, int y)
{
	if (m_image.IsNull())
		return false;

	CRect rect(0, 0, m_image.GetWidth(), m_image.GetHeight());

	return rect.PtInRect(CPoint(x, y));
}

void CDlgImage::SetWeightCenter(bool bFoundCenter, int centerX, int centerY)
{
	m_bFoundCenter = bFoundCenter;
	m_centerX = centerX;
	m_centerY = centerY;
}

void CDlgImage::SetRadius(int radius)
{
	m_radius = radius;
}