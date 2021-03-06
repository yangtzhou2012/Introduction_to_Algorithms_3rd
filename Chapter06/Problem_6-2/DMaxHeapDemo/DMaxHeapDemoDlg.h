
// DMaxHeapDemoDlg.h: 头文件
//

#pragma once

#include "DHeapView.h"
#include "DMaxHeap.h"


// CDMaxHeapDemoDlg 对话框
class CDMaxHeapDemoDlg : public CDialogEx
{
// 构造
public:
	CDMaxHeapDemoDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DMAXHEAPDEMO_DIALOG };
#endif

	const DMaxHeap<int>& GetDMaxHeap() const { return m_DMaxHeap; }

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	CDHeapView m_DMaxHeapFigure;
	DMaxHeap<int> m_DMaxHeap;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnInsert();
	afx_msg void OnExtractMax();
	afx_msg void OnIncreaseKey();
	afx_msg void OnClear();
	afx_msg void OnSetDAry();
	CString m_InsertElements;
	int m_IncreaseElemIndex;
	int m_IncreaseToElem;
	int m_DAry;
};
