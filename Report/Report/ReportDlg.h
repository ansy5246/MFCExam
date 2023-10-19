
// ReportDlg.h : 헤더 파일
//

#pragma once

#include "DlgImage.h"

// CReportDlg 대화 상자
class CReportDlg : public CDialogEx
{
// 생성입니다.
public:
	CReportDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

	CDlgImage* m_pDlgImage;
	CDlgImage* m_pDlgResult;
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_REPORT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
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
