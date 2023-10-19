#pragma once


// CDlgImage ��ȭ �����Դϴ�.

class CDlgImage : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgImage)

public:
	CDlgImage(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDlgImage();

	CImage m_image;
	
	void SetRadius(int radius);
	void SetWeightCenter(bool bFoundCenter , int centerX = 0, int centerY = 0);

	bool IsValidPos(int x, int y);

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_IMAGE_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();

private:
	void InitImage();
	
	bool m_bFoundCenter;
	int m_radius;
	int m_centerX;
	int m_centerY;
};
