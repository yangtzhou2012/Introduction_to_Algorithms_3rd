
// ImageSeamDemoDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "ImageSeamDemo.h"
#include "ImageSeamDemoDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImageSeamDemoDlg 对话框



CImageSeamDemoDlg::CImageSeamDemoDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_IMAGESEAMDEMO_DIALOG, pParent)
	, m_ImageWidth(10)
	, m_ImageHeight(10)
	, m_TotalDisruption(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CImageSeamDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_IMAGE_WIDTH, m_ImageWidth);
	DDV_MinMaxInt(pDX, m_ImageWidth, 0, INT_MAX);
	DDX_Text(pDX, IDC_IMAGE_HEIGHT, m_ImageHeight);
	DDV_MinMaxInt(pDX, m_ImageHeight, 0, INT_MAX);
	DDX_Text(pDX, IDC_TOTAL_DISRUPTION_EDIT, m_TotalDisruption);
	DDV_MinMaxInt(pDX, m_TotalDisruption, 0, INT_MAX);
}

BEGIN_MESSAGE_MAP(CImageSeamDemoDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_SET_IMAGE_SIZE, &CImageSeamDemoDlg::OnSetImageSize)
	ON_BN_CLICKED(IDC_RANDOM_DISRUPTION, &CImageSeamDemoDlg::OnRandomDisruption)
	ON_BN_CLICKED(IDC_GET_SEAM, &CImageSeamDemoDlg::OnGetSeam)
END_MESSAGE_MAP()


// CImageSeamDemoDlg 消息处理程序

BOOL CImageSeamDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	GetDlgItem(IDC_DISRUPTION_EDIT)->ShowWindow(SW_HIDE);
	//GetDlgItem(IDC_DISRUPTION_EDIT)->ModifyStyle(ES_LEFT, ES_CENTER);

	m_ImageSeamFigure.SubclassDlgItem(IDC_SEAM_FIGURE, this);

	m_ImageSeam.SetSize(m_ImageWidth, m_ImageHeight);
	m_ImageSeam.GenerateRandomDisruption();
	m_ImageSeam.BuildImageSeam();
	m_TotalDisruption = m_ImageSeam.GetTotalDisruption();
	//m_ImageSeamFigure.ResetScrollRange();

	UpdateData(FALSE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CImageSeamDemoDlg::OnPaint()
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
HCURSOR CImageSeamDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CImageSeamDemoDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_RETURN)
			return TRUE;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CImageSeamDemoDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	CRect rect;

	CWnd *pWnd = GetDlgItem(IDC_SEAM_FIGURE);
	if (pWnd && pWnd->m_hWnd)
	{
		pWnd->GetWindowRect(rect);
		ScreenToClient(rect);
		rect.bottom = cy - 13;
		rect.right = cx - 13;
		pWnd->MoveWindow(rect);
	}
}

void CImageSeamDemoDlg::OnSetImageSize()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	m_ImageSeam.SetSize(m_ImageWidth, m_ImageHeight);
	m_TotalDisruption = m_ImageSeam.GetTotalDisruption();
	m_ImageSeamFigure.ResetScrollRange();
	UpdateData(FALSE);
	Invalidate();
}

void CImageSeamDemoDlg::OnRandomDisruption()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ImageSeam.GenerateRandomDisruption();
	m_TotalDisruption = m_ImageSeam.GetTotalDisruption();
	UpdateData(FALSE);
	Invalidate();
}

void CImageSeamDemoDlg::OnGetSeam()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ImageSeam.BuildImageSeam();
	m_TotalDisruption = m_ImageSeam.GetTotalDisruption();
	UpdateData(FALSE);
	Invalidate();
}
