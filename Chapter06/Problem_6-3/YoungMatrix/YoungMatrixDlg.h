
// YoungMatrixDlg.h: 头文件
//

#pragma once

#include "YoungMatrixView.h"
#include "YoungMatrixAlgo.h"


// CYoungMatrixDlg 对话框
class CYoungMatrixDlg : public CDialogEx
{
// 构造
public:
	CYoungMatrixDlg(CWnd* pParent = nullptr);	// 标准构造函数

	const YoungMatrix<int>& GetYoungMatrix() const { return m_YoungMatrix; }

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_YOUNGMATRIX_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	CYoungMatrixView m_YoungMatrixFigure;
	YoungMatrix<int> m_YoungMatrix;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSetSize();
	afx_msg void OnInsert();
	afx_msg void OnExtractMin();
	int m_MatrixHeight;
	int m_MatrixWidth;
	CString m_InsertElements;
	afx_msg void OnClear();
};
