// DlgImage.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Report.h"
#include "DlgImage.h"
#include "afxdialogex.h"


// CDlgImage ��ȭ �����Դϴ�.

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


// CDlgImage �޽��� ó�����Դϴ�.


BOOL CDlgImage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.	
	InitImage(); 
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
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
					   // TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
					   // �׸��� �޽����� ���ؼ��� CDialogEx::OnPaint()��(��) ȣ������ ���ʽÿ�.

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