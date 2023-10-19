
// ReportDlg.h : ��� ����
//

#pragma once

#include "DlgImage.h"

// CReportDlg ��ȭ ����
class CReportDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CReportDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

	CDlgImage* m_pDlgImage;
	CDlgImage* m_pDlgResult;
// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_REPORT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedButtonProcess();
	afx_msg void OnBnClickedButtonPattern();
	afx_msg void OnBnClickedButtonPatternCenter();
	int m_radius;
	afx_msg void OnBnClickedButtonCircle();
	afx_msg void OnBnClickedButtonCircleCenter();
};
