#pragma once


// CDHeapView

#include <sstream>
#include "DMaxHeap.h"

using namespace std;

class CDHeapView : public CWnd
{
	DECLARE_DYNAMIC(CDHeapView)

public:
	CDHeapView();
	virtual ~CDHeapView();

	void ResetScrollRange();

protected:
	DECLARE_MESSAGE_MAP()

private:
	static const int m_TreeNodeWidth = 20; // 48;
	static const int m_TreeNodeHeight = 48;
	static const int m_FontHeight = 16;
	template <typename T> CSize GetPaintSize(const DMaxHeap<T> &queue);
	template <typename T> void Paint(const DMaxHeap<T> &queue, CDC &dc);

public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnPaint();
};

template <typename T>
CSize CDHeapView::GetPaintSize(const DMaxHeap<T> &heap)
{
	int d = heap.branches();
	int h = -1;
	for (int i = 0; i < heap.size(); i = i*d + 1)
		h++;

	int w = 0;
	if (h >= 0)
	{
		w = 1;
		for (int i = 0; i < h; ++i)
			w *= d;
	}

	return CSize(w*m_TreeNodeWidth, (h+1)*m_TreeNodeHeight);
}

template <typename T>
void CDHeapView::Paint(const DMaxHeap<T> &heap, CDC &dc)
{
	CRect wndRect;
	GetClientRect(wndRect);
	CRgn rgn;
	rgn.CreateRectRgn(wndRect.left, wndRect.top, wndRect.right, wndRect.bottom);
	dc.SelectClipRgn(&rgn, RGN_COPY);
	dc.FillSolidRect(wndRect, RGB(255, 255, 255));

	CSize paintSize = GetPaintSize(heap);
	int dx = GetScrollPos(SB_HORZ);
	int dy = GetScrollPos(SB_VERT);

	if (paintSize.cx <= wndRect.Width())
		dx = -(wndRect.Width()-paintSize.cx)/2;

	CFont font;
	font.CreateFont(m_FontHeight, 0, 000, 000, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_TT_PRECIS, CLIP_TT_ALWAYS, PROOF_QUALITY, VARIABLE_PITCH|FF_ROMAN, CString("Courier New"));
	CFont *pOldFont = dc.SelectObject(&font);
	int oldTextAlign = dc.SetTextAlign(TA_BOTTOM|TA_CENTER);

	int d = heap.branches();
	int floorStart = 1;
	int paintIntervalX = paintSize.cx;
	int nextIntervalX = paintIntervalX/d;
	int paintBaseX = paintIntervalX/2 - dx;
	int paintBaseY = (m_TreeNodeHeight+m_FontHeight)/2 - dy;
	int paintNodeX = paintBaseX;

	for (int i = 0; i < heap.size(); ++i)
	{
		ostringstream is;
		is << heap[i];
		CString str(is.str().c_str());
		dc.TextOut(paintNodeX, paintBaseY, str);

		int child = i*d + 1;
		int childX = paintNodeX - nextIntervalX*(d-1)/2;
		for (int k = 0; k < d && child < heap.size(); ++k, ++child)
		{
			dc.MoveTo(paintNodeX, paintBaseY);
			dc.LineTo(childX, paintBaseY+m_TreeNodeHeight-m_FontHeight-2);
			childX += nextIntervalX;
		}

		paintNodeX += paintIntervalX;

		if (i == floorStart - 1)
		{
			floorStart = floorStart*d + 1;
			paintIntervalX = nextIntervalX;
			nextIntervalX /= d;
			paintBaseX = paintIntervalX/2 - dx;
			paintBaseY += m_TreeNodeHeight;
			paintNodeX = paintBaseX;
		}
	}

	dc.SetTextAlign(oldTextAlign);
	dc.SelectObject(pOldFont);
}


