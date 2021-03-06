
// EditDistanceDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "EditDistance.h"
#include "EditDistanceDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEditDistanceDlg 对话框



CEditDistanceDlg::CEditDistanceDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_EDITDISTANCE_DIALOG, pParent)
	, m_OriginalString(_T("algorithm"))
	, m_TargetString(_T("altruistic"))
	, m_CopyCost(0)
	, m_ReplaceCost(0)
	, m_DeleteCost(0)
	, m_InsertCost(0)
	, m_TwiddleCost(0)
	, m_KillCost(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEditDistanceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ORIGINAL_STRING_EDIT, m_OriginalString);
	DDX_Text(pDX, IDC_TARGET_STRING_EDIT, m_TargetString);
	DDX_Text(pDX, IDC_COPY_COST_EDIT, m_CopyCost);
	DDV_MinMaxDouble(pDX, m_CopyCost, 0, DBL_MAX);
	DDX_Text(pDX, IDC_REPLACE_COST_EDIT, m_ReplaceCost);
	DDV_MinMaxDouble(pDX, m_ReplaceCost, 0, DBL_MAX);
	DDX_Text(pDX, IDC_DELETE_COST_EDIT, m_DeleteCost);
	DDV_MinMaxDouble(pDX, m_DeleteCost, 0, DBL_MAX);
	DDX_Text(pDX, IDC_INSERT_COST_EDIT, m_InsertCost);
	DDV_MinMaxDouble(pDX, m_InsertCost, 0, DBL_MAX);
	DDX_Text(pDX, IDC_TWIDDLE_COST_EDIT, m_TwiddleCost);
	DDV_MinMaxDouble(pDX, m_TwiddleCost, 0, DBL_MAX);
	DDX_Text(pDX, IDC_KILL_COST_EDIT, m_KillCost);
	DDV_MinMaxDouble(pDX, m_KillCost, 0, DBL_MAX);
}

BEGIN_MESSAGE_MAP(CEditDistanceDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_EDIT_DISTANCE, &CEditDistanceDlg::OnEditDistance)
	ON_BN_CLICKED(IDC_CLEAR, &CEditDistanceDlg::OnClear)
END_MESSAGE_MAP()


// CEditDistanceDlg 消息处理程序

BOOL CEditDistanceDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_EditFont.CreateFont(16, 0, 000, 000, FW_NORMAL, 0, 0, 0, ANSI_CHARSET,
							OUT_TT_PRECIS, CLIP_TT_ALWAYS, PROOF_QUALITY,
							VARIABLE_PITCH|FF_ROMAN, CString("Courier New"));
	GetDlgItem(IDC_ORIGINAL_STRING_EDIT)->SetFont(&m_EditFont);
	GetDlgItem(IDC_TARGET_STRING_EDIT)->SetFont(&m_EditFont);

	m_TransferView.SubclassDlgItem(IDC_TRANSFER_EDIT, this);

	double opCost[6] = { 1, 1.5, 0.9, 0.9, 1.5, 5 };
	m_CopyCost    = opCost[0];
	m_ReplaceCost = opCost[1];
	m_DeleteCost  = opCost[2];
	m_InsertCost  = opCost[3];
	m_TwiddleCost = opCost[4];
	m_KillCost    = opCost[5];

	m_EditDistance.GetEditDistance(m_OriginalString.GetBuffer(), m_TargetString.GetBuffer(), opCost);

	m_OriginalString.ReleaseBuffer();
	m_TargetString.ReleaseBuffer();

	UpdateData(FALSE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CEditDistanceDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CEditDistanceDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CEditDistanceDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_ESCAPE)
			return TRUE;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CEditDistanceDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	CRect rect;

	CWnd *pWnd = GetDlgItem(IDC_TRANSFER_EDIT);
	if (pWnd && pWnd->m_hWnd)
	{
		pWnd->GetWindowRect(rect);
		ScreenToClient(rect);
		rect.bottom = cy - 12;
		rect.right = cx - 12;
		pWnd->MoveWindow(rect);
	}

	pWnd = GetDlgItem(IDC_CLEAR);
	int button_left = 0;
	if (pWnd && pWnd->m_hWnd)
	{
		pWnd->GetWindowRect(rect);
		ScreenToClient(rect);
		int r = rect.right;
		rect.right = cx - 12;
		rect.left += (rect.right - r);
		button_left = rect.left;
		pWnd->MoveWindow(rect);
	}

	pWnd = GetDlgItem(IDC_EDIT_DISTANCE);
	if (pWnd && pWnd->m_hWnd)
	{
		pWnd->GetWindowRect(rect);
		ScreenToClient(rect);
		int r = rect.right;
		rect.right = cx - 12;
		rect.left += (rect.right - r);
		button_left = rect.left;
		pWnd->MoveWindow(rect);
	}

	pWnd = GetDlgItem(IDC_ORIGINAL_STRING_EDIT);
	if (pWnd && pWnd->m_hWnd)
	{
		pWnd->GetWindowRect(rect);
		ScreenToClient(rect);
		rect.right = button_left - 9;
		pWnd->MoveWindow(rect);
	}

	pWnd = GetDlgItem(IDC_TARGET_STRING_EDIT);
	if (pWnd && pWnd->m_hWnd)
	{
		pWnd->GetWindowRect(rect);
		ScreenToClient(rect);
		rect.right = button_left - 9;
		pWnd->MoveWindow(rect);
	}

	Invalidate();
}

void CEditDistanceDlg::OnEditDistance()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();

	double opCost[6];
	opCost[0] = m_CopyCost;
	opCost[1] = m_ReplaceCost;
	opCost[2] = m_DeleteCost;
	opCost[3] = m_InsertCost;
	opCost[4] = m_TwiddleCost;
	opCost[5] = m_KillCost;

	m_EditDistance.GetEditDistance(m_OriginalString.GetBuffer(), m_TargetString.GetBuffer(), opCost);
	m_OriginalString.ReleaseBuffer();
	m_TargetString.ReleaseBuffer();
	m_TransferView.ResetScrollRange();

	Invalidate();
}

void CEditDistanceDlg::OnClear()
{
	// TODO: 在此添加控件通知处理程序代码
	m_OriginalString.Empty();
	m_TargetString.Empty();
	UpdateData(FALSE);

	m_EditDistance.Clear();
	m_TransferView.ResetScrollRange();

	Invalidate();
}
