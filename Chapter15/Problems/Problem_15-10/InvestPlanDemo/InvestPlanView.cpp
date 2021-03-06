// InvestPlanView.cpp: 实现文件
//

#include "stdafx.h"
#include "InvestPlanDemo.h"
#include "InvestPlanView.h"
#include "InvestPlanDemoDlg.h"


// CInvestPlanView

IMPLEMENT_DYNAMIC(CInvestPlanView, CWnd)

CInvestPlanView::CInvestPlanView()
{

}

CInvestPlanView::~CInvestPlanView()
{
}


BEGIN_MESSAGE_MAP(CInvestPlanView, CWnd)
	ON_WM_SIZE()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_PAINT()
END_MESSAGE_MAP()

void CInvestPlanView::ResetScrollRange()
{
	int paintTotalWidth = 0;
	int paintTotalHeight = 0;

	CInvestPlanDemoDlg *pDlg = (CInvestPlanDemoDlg*)GetParent();

	if (pDlg != NULL)
	{
		paintTotalWidth = (pDlg->GetInvestPlan().GetInvestments() + 1) * blockSideLength + 80;
		paintTotalHeight = (pDlg->GetInvestPlan().GetYears() + 1) * blockSideLength + 20;
	}

	SCROLLINFO scroll_info;
	scroll_info.cbSize = sizeof(SCROLLINFO);

	CRect client;
	GetClientRect(client);
	scroll_info.fMask = SIF_RANGE | SIF_PAGE;
	scroll_info.nMin = 0;
	scroll_info.nMax = paintTotalWidth;
	scroll_info.nPage = client.Width();
	SetScrollInfo(SB_HORZ, &scroll_info);

	GetClientRect(client);
	scroll_info.fMask = SIF_RANGE | SIF_PAGE | SIF_DISABLENOSCROLL;
	scroll_info.nMin = 0;
	scroll_info.nMax = paintTotalHeight;
	scroll_info.nPage = client.Height();
	SetScrollInfo(SB_VERT, &scroll_info);
}

void CInvestPlanView::PaintInvestPlan(CDC &dc)
{
	CRect wndRect;
	GetClientRect(wndRect);

	CRgn rgn;
	rgn.CreateRectRgn(wndRect.left, wndRect.top, wndRect.right, wndRect.bottom);
	dc.SelectClipRgn(&rgn, RGN_COPY);
	dc.FillSolidRect(wndRect, RGB(255, 255, 255));

	CInvestPlanDemoDlg *pDlg = (CInvestPlanDemoDlg*)GetParent();
	if (pDlg == NULL) return;

	int paintTotalWidth = pDlg->GetInvestPlan().GetInvestments() * blockSideLength;
	int paintTotalHeight = pDlg->GetInvestPlan().GetYears() * blockSideLength;
	int dx = GetScrollPos(SB_HORZ);
	int dy = GetScrollPos(SB_VERT);
	int rowBase = blockSideLength + 10 - dy;
	int columnBase = wndRect.Width() > blockSideLength+paintTotalWidth+80 ? (wndRect.Width()+blockSideLength-paintTotalWidth)/2-dx : 40+blockSideLength-dx;

	dc.MoveTo(columnBase, rowBase);
	dc.LineTo(columnBase+paintTotalWidth, rowBase);
	dc.MoveTo(columnBase, rowBase);
	dc.LineTo(columnBase, rowBase+paintTotalHeight);

	int rowCoordinate = rowBase;
	int columnCoordinate = columnBase;

	for (int i = 0; i < pDlg->GetInvestPlan().GetYears(); ++i)
	{
		rowCoordinate += blockSideLength;
		dc.MoveTo(columnBase, rowCoordinate);
		dc.LineTo(columnBase+paintTotalWidth+1, rowCoordinate);
	}

	for (int j = 0; j < pDlg->GetInvestPlan().GetInvestments(); ++j)
	{
		columnCoordinate += blockSideLength;
		dc.MoveTo(columnCoordinate, rowBase);
		dc.LineTo(columnCoordinate, rowBase+paintTotalHeight+1);
	}

	const int *pInvestSelect = pDlg->GetInvestPlan().GetInvestSelect();

	if (pInvestSelect != NULL)
	{
		rowCoordinate = rowBase;
		CBrush brush(RGB(192, 192, 192));

		for (int i = 0; i < pDlg->GetInvestPlan().GetYears(); ++i)
		{
			columnCoordinate = columnBase + pInvestSelect[i]*blockSideLength;
			CRect rect(columnCoordinate+1, rowCoordinate+1, columnCoordinate+blockSideLength, rowCoordinate+blockSideLength);
			dc.FillRect(rect, &brush);
			rowCoordinate += blockSideLength;
		}
	}

	const int *pRatePercent = pDlg->GetInvestPlan().GetRatePercent();

	CFont font;
	font.CreateFont(fontHeight, 0, 000, 000, FW_NORMAL, 0, 0, 0, ANSI_CHARSET,
		OUT_TT_PRECIS, CLIP_TT_ALWAYS, PROOF_QUALITY,
		VARIABLE_PITCH | FF_ROMAN, CString("Courier New"));
	CFont *pOldFont = dc.SelectObject(&font);
	int oldTextAlign = dc.SetTextAlign(TA_TOP|TA_LEFT);
	int oldBkMode = dc.SetBkMode(TRANSPARENT);

	rowCoordinate = rowBase + blockSideLength/2 - fontHeight/2;
	columnCoordinate = columnBase - blockSideLength;
	dc.TextOut(columnCoordinate, rowCoordinate-fontHeight, CString("year"));
	dc.TextOut(columnBase-blockSideLength, rowBase-blockSideLength/2-fontHeight/2, CString("invest"));

	for (int i = 0; i < pDlg->GetInvestPlan().GetYears(); ++i)
	{
		CString str;
		str.Format("%d", i+1);
		dc.TextOut(columnCoordinate, rowCoordinate, str);
		rowCoordinate += blockSideLength;
	}
	
	dc.SetTextAlign(TA_TOP|TA_CENTER);
	rowCoordinate = rowBase - blockSideLength/2 - fontHeight/2;
	columnCoordinate = columnBase + blockSideLength/2;

	for (int i = 0; i < pDlg->GetInvestPlan().GetInvestments(); ++i)
	{
		CString str;
		str.Format("%d", i+1);
		dc.TextOut(columnCoordinate, rowCoordinate, str);
		columnCoordinate += blockSideLength;
	}

	if (pRatePercent != NULL)
	{
		dc.SetTextAlign(TA_TOP|TA_CENTER);
		rowCoordinate = rowBase + blockSideLength/2 - fontHeight/2;

		for (int i = 0; i < pDlg->GetInvestPlan().GetYears(); ++i)
		{
			columnCoordinate = columnBase + blockSideLength/2;

			for (int j = 0; j < pDlg->GetInvestPlan().GetInvestments(); ++j)
			{
				CString str;
				str.Format("%.02f", static_cast<double>(*pRatePercent++)/100);
				dc.TextOut(columnCoordinate, rowCoordinate, str);
				columnCoordinate += blockSideLength;
			}

			rowCoordinate += blockSideLength;
		}
	}

	dc.SelectObject(pOldFont);
	dc.SetTextAlign(oldTextAlign);
	dc.SetBkMode(oldBkMode);
}

// CInvestPlanView 消息处理程序




BOOL CInvestPlanView::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_LBUTTONDOWN
		|| pMsg->message == WM_RBUTTONDOWN || pMsg->message == WM_RBUTTONDBLCLK)
	{
		return TRUE;
	}

	return CWnd::PreTranslateMessage(pMsg);
}

void CInvestPlanView::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	ResetScrollRange();
}

void CInvestPlanView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int x = GetScrollPos(SB_HORZ);

	switch (nSBCode)
	{
	case SB_LEFT:
		x = 0;
		break;

	case SB_RIGHT:
		x = GetScrollLimit(SB_HORZ) - 1;
		break;

	case SB_LINELEFT:
		x -= 1;
		break;

	case SB_LINERIGHT:
		x += 1;
		break;

	case SB_PAGELEFT:
		x -= 10;
		break;

	case SB_PAGERIGHT:
		x += 10;
		break;

	case SB_THUMBTRACK:
		x = nPos;
		break;

	default:
		break;
	}

	int x_max = GetScrollLimit(SB_HORZ);
	if (x > x_max) x = x_max - 1;
	if (x < 0) x = 0;

	SetScrollPos(SB_HORZ, x);
	Invalidate();

	CWnd::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CInvestPlanView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int y = GetScrollPos(SB_VERT);

	switch (nSBCode)
	{
	case SB_TOP:
		y = 0;
		break;

	case SB_BOTTOM:
		y = GetScrollLimit(SB_VERT) - 1;
		break;

	case SB_LINEUP:
		y -= 1;
		break;

	case SB_LINEDOWN:
		y += 1;
		break;

	case SB_PAGEUP:
		y -= 10;
		break;

	case SB_PAGEDOWN:
		y += 10;
		break;

	case SB_THUMBTRACK:
		y = nPos;
		break;

	default:
		break;
	}

	int y_max = GetScrollLimit(SB_VERT);
	if (y > y_max) y = y_max - 1;
	if (y < 0) y = 0;

	SetScrollPos(SB_VERT, y);
	Invalidate();

	CWnd::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CInvestPlanView::OnPaint()
{
	static bool first_paint = 1;

	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CWnd::OnPaint()

	if (first_paint == 1)
	{
		first_paint = 0;
		ShowScrollBar(SB_BOTH);
		SCROLLINFO scroll_info;
		scroll_info.fMask = SIF_DISABLENOSCROLL;
		SetScrollInfo(SB_HORZ, &scroll_info);
		SetScrollInfo(SB_VERT, &scroll_info);
		//EnableScrollBarCtrl(SB_HORZ);
		//EnableScrollBarCtrl(SB_VERT);

		ResetScrollRange();
	}

	PaintInvestPlan(dc);
}
